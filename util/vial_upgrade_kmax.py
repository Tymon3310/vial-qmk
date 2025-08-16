#!/usr/bin/env python3
import json
import math
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GLOB = "keyboards/keychron/k*_max/**/keymaps/vial/vial.json"

CKC_OBJECTS = [
    {"name": "BT_HST1", "title": "Bluetooth Host 1", "shortName": "BT1"},
    {"name": "BT_HST2", "title": "Bluetooth Host 2", "shortName": "BT2"},
    {"name": "BT_HST3", "title": "Bluetooth Host 3", "shortName": "BT3"},
    {"name": "P2P4G",  "title": "2.4G Wireless",     "shortName": "2.4G"},
    {"name": "BAT_LVL", "title": "Battery Level",      "shortName": "BAT"},
    {"name": "NK_TOGG", "title": "NKRO Toggle",        "shortName": "NKRO"},
]

FLOAT_EPS = 1e-6


def nearest_layout_key(layouts: dict, variant: str) -> str | None:
    keys = list(layouts.keys())
    # Prefer exact contains with variant token
    variant = variant.lower()
    def score(k: str) -> tuple:
        s = k.lower()
        return (
            0 if variant in s else 1,
            0 if "_ansi_" in s or "_iso_" in s or "_jis_" in s else 1,
            len(s),
        )
    if not keys:
        return None
    keys.sort(key=score)
    return keys[0]


def group_by_y(items):
    rows = {}
    for it in items:
        y = float(it.get("y", 0))
        rows.setdefault(y, []).append(it)
    ys = sorted(rows.keys())
    return [(y, sorted(rows[y], key=lambda a: float(a.get("x", 0)))) for y in ys]


def build_vial_keymap(layout_items: list[dict]) -> list[list]:
    # Convert info.json layout items into Vial JSON keymap format
    keymap = []
    rows = group_by_y(layout_items)
    prev_y = None
    for y, items in rows:
        row = []
        if prev_y is not None:
            dy = y - prev_y
            if abs(dy) > FLOAT_EPS:
                row.append({"y": round(dy, 3)})
        prev_y = y

        prev_x_end = 0.0
        for it in items:
            x = float(it.get("x", 0))
            w = float(it.get("w", 1))
            h = float(it.get("h", 1))
            r, c = it["matrix"]
            gap = x - prev_x_end
            if gap > FLOAT_EPS:
                row.append({"x": round(gap, 3)})
            wh = {}
            if abs(w - 1.0) > FLOAT_EPS:
                wh["w"] = round(w, 3)
            if abs(h - 1.0) > FLOAT_EPS:
                wh["h"] = round(h, 3)
            if wh:
                row.append(wh)
            row.append(f"{r},{c}")
            prev_x_end = x + w
        keymap.append(row)
    return keymap


def ensure_matrix(meta: dict, info: dict) -> None:
    if "matrix" not in meta or not isinstance(meta["matrix"], dict):
        rows = len(info.get("matrix_pins", {}).get("rows", []))
        cols = len(info.get("matrix_pins", {}).get("cols", []))
        if rows and cols:
            meta["matrix"] = {"rows": rows, "cols": cols}


def normalize_lighting(meta: dict, path: Path) -> None:
    p = str(path)
    if "/rgb/" in p:
        meta["lighting"] = "vialrgb"
    elif "/white/" in p:
        meta["lighting"] = "qmk_backlight"


def normalize_custom_keycodes(meta: dict) -> None:
    ckc = meta.get("customKeycodes")
    # Always set to our canonical list
    meta["customKeycodes"] = CKC_OBJECTS


def find_variant_info_file(vial_path: Path, kb_root: Path) -> Path | None:
    # Walk up from vial.json directory towards kb_root to find a keyboard.json
    for parent in vial_path.parents:
        if parent == kb_root.parent:
            break
        candidate = parent / "keyboard.json"
        if candidate.exists():
            return candidate
    return None


def update_vial_json(vial_path: Path) -> bool:
    kb_root = None
    # find k*_max directory root
    for parent in vial_path.parents:
        if parent.name.endswith("_max") and parent.parent.name == "keychron":
            kb_root = parent
            break
    if kb_root is None:
        return False

    # Resolve variant-level and root metadata files
    variant_info_path = find_variant_info_file(vial_path, kb_root)
    root_info_path = kb_root / "info.json"
    if not root_info_path.exists() and not (variant_info_path and variant_info_path.exists()):
        return False

    variant_info = None
    root_info = None
    if variant_info_path and variant_info_path.exists():
        try:
            variant_info = json.loads(variant_info_path.read_text())
        except Exception:
            variant_info = None
    if root_info_path.exists():
        try:
            root_info = json.loads(root_info_path.read_text())
        except Exception:
            root_info = None

    # Choose info source for layouts: prefer variant if it actually provides layouts, else root
    layout_info = None
    if variant_info and isinstance(variant_info.get("layouts"), dict) and variant_info.get("layouts"):
        layout_info = variant_info
    elif root_info and isinstance(root_info.get("layouts"), dict) and root_info.get("layouts"):
        layout_info = root_info

    if not layout_info:
        return False

    layouts = layout_info.get("layouts", {})

    # Variant from path: ansi/iso/jis
    m = re.search(r"/(ansi|iso|jis)(?:_|/)", str(vial_path))
    variant = m.group(1) if m else "ansi"

    layout_key = nearest_layout_key(layouts, variant)
    if not layout_key:
        return False

    # Build keymap from selected layout
    layout_items = layouts[layout_key].get("layout", [])
    keymap = build_vial_keymap(layout_items)

    meta = json.loads(vial_path.read_text())

    # Choose info source for matrix: prefer variant if it declares matrix_pins, else root
    matrix_info = variant_info if (variant_info and isinstance(variant_info.get("matrix_pins"), dict)) else root_info
    if not matrix_info:
        return False

    ensure_matrix(meta, matrix_info)
    normalize_lighting(meta, vial_path)
    meta.setdefault("layouts", {})["keymap"] = keymap
    normalize_custom_keycodes(meta)

    vial_path.write_text(json.dumps(meta, indent=2) + "\n")
    return True


def ensure_vialrgb_rules(vial_path: Path) -> None:
    # Add VIALRGB_ENABLE = yes for rgb keymaps; ensure not present for white
    rules = vial_path.parent / "rules.mk"
    if not rules.exists():
        # Only create for RGB
        if "/rgb/" in str(vial_path):
            rules.write_text("VIALRGB_ENABLE = yes\n")
        return
    content = rules.read_text()
    if "/rgb/" in str(vial_path):
        if "VIALRGB_ENABLE" not in content:
            content = content.rstrip() + "\nVIALRGB_ENABLE = yes\n"
        else:
            content = re.sub(r"^VIALRGB_ENABLE\s*=.*$", "VIALRGB_ENABLE = yes", content, flags=re.M)
        rules.write_text(content)
    else:
        # For white variants, remove the line to avoid confusion
        new_content = re.sub(r"^VIALRGB_ENABLE\s*=.*$\n?", "", content, flags=re.M)
        if new_content != content:
            rules.write_text(new_content)


def main():
    changed = 0
    total = 0
    for path in ROOT.glob(GLOB):
        total += 1
        try:
            ok = update_vial_json(path)
            ensure_vialrgb_rules(path)
            if ok:
                changed += 1
                print(f"Updated: {path}")
            else:
                print(f"Skipped (no layout/info): {path}")
        except Exception as e:
            print(f"ERROR {path}: {e}")
    print(f"Done. Updated {changed}/{total} vial.json files.")


if __name__ == "__main__":
    main()
