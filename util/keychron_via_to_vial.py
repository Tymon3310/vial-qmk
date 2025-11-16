#!/usr/bin/env python3
"""Convert every Keychron VIA keymap to Vial.

The script walks ``keyboards/keychron`` (override with ``--keyboard-root``),
finds ``keymaps/via`` directories, and mirrors them into ``keymaps/vial`` with
fresh ``config.h``, ``rules.mk``, and ``vial.json`` files. It prefers
``via_json`` definitions for layout/metadata but can synthesize a reasonable
``vial.json`` straight from ``info.json``/``keyboard.json`` when those files
are missing.

Examples
--------
$ python util/keychron_via_to_vial.py
$ python util/keychron_via_to_vial.py --keyboard-root keyboards/keychron --dry-run
"""

from __future__ import annotations

import argparse
import json
import secrets
import shutil
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence

import hjson

DEFAULT_KEYCODES = [
    {"name": "Left Option", "title": "Left Option", "shortName": "LOpt"},
    {"name": "Right Option", "title": "Right Option", "shortName": "ROpt"},
    {"name": "Left Cmd", "title": "Left Command", "shortName": "LCmd"},
    {"name": "Right Cmd", "title": "Right Command", "shortName": "RCmd"},
    {"name": "Task View", "title": "Task View in Windows", "shortName": "Task"},
    {"name": "File Explorer", "title": "File Explorer in Windows", "shortName": "File"},
    {"name": "Screen shot", "title": "Screenshot in macOS", "shortName": "SShot"},
    {"name": "Cortana", "title": "Cortana in Windows", "shortName": "Cortana"},
    {"name": "Siri", "title": "Siri in macOS", "shortName": "Siri"},
    {"name": "Bluetooth Host 1", "title": "Bluetooth Host 1", "shortName": "BTH1"},
    {"name": "Bluetooth Host 2", "title": "Bluetooth Host 2", "shortName": "BTH2"},
    {"name": "Bluetooth Host 3", "title": "Bluetooth Host 3", "shortName": "BTH3"},
    {"name": "Battery Level", "title": "Show battery level", "shortName": "Batt"},
]


@dataclass
class KeyboardMetadata:
    board_dir: Path
    variant_dir: Path
    variant_tokens: Sequence[str]
    layout_data: List[dict]
    rows: int
    cols: int
    pid: str
    vid: str
    has_rgb: bool
    has_encoder: bool
    min_matrix: Sequence[int]
    max_matrix: Sequence[int]


class KeychronVialConverter:
    def __init__(self, keyboard_root: Path, dry_run: bool = False) -> None:
        self.keyboard_root = keyboard_root
        self.dry_run = dry_run
        self.pid_cache: Dict[str, List[tuple[Path, dict]]] = {}

    def run(self) -> None:
        via_dirs = sorted(self.keyboard_root.rglob("keymaps/via"))
        if not via_dirs:
            print(f"No VIA keymaps found under {self.keyboard_root}.")
            return

        converted = 0
        for via_dir in via_dirs:
            variant_dir = via_dir.parent.parent
            vial_dir = variant_dir / "keymaps" / "vial"
            if (vial_dir / "vial.json").exists():
                continue
            rel_parts = variant_dir.relative_to(self.keyboard_root).parts
            if not rel_parts:
                continue
            metadata = self._collect_metadata(via_dir, variant_dir)
            via_def = self._load_via_definition(metadata, rel_parts)
            if self.dry_run:
                print(f"[dry-run] Would convert {variant_dir}")
                converted += 1
                continue
            self._materialize_vial_keymap(via_dir, metadata, via_def)
            converted += 1
        print(f"Converted {converted} VIA keymaps to Vial (dry_run={self.dry_run}).")

    def _collect_metadata(self, via_dir: Path, variant_dir: Path) -> KeyboardMetadata:
        rel_parts = variant_dir.relative_to(self.keyboard_root).parts
        board_dir = self.keyboard_root / rel_parts[0]
        variant_tokens = rel_parts[1:]

        def load_json(path: Path) -> dict:
            with path.open() as fp:
                return hjson.load(fp)

        def first_existing(paths: Iterable[Path]) -> Path:
            for path in paths:
                if path.is_file():
                    return path
            raise FileNotFoundError(f"No metadata JSON for {variant_dir}")

        variant_info_path = first_existing(
            [
                variant_dir / "keyboard.json",
                board_dir / "keyboard.json",
                board_dir / "info.json",
            ]
        )
        variant_info = load_json(variant_info_path)
        board_info_path = board_dir / "info.json"
        board_info = load_json(board_info_path) if board_info_path.is_file() else {}

        layout_info = variant_info if variant_info.get("layouts") else None
        if layout_info is None:
            for parent in self._walk_to_board(variant_dir, board_dir):
                for filename in ("keyboard.json", "info.json"):
                    candidate = parent / filename
                    if candidate.is_file():
                        data = load_json(candidate)
                        if data.get("layouts"):
                            layout_info = data
                            break
                if layout_info:
                    break
        if layout_info is None and board_info.get("layouts"):
            layout_info = board_info
        if layout_info is None or "layouts" not in layout_info:
            raise RuntimeError(f"Missing layout data for {variant_dir}")
        layout_data = next(iter(layout_info["layouts"].values()))["layout"]

        matrix_positions = [item["matrix"] for item in layout_data if "matrix" in item]
        rows = max(pos[0] for pos in matrix_positions) + 1
        cols = max(pos[1] for pos in matrix_positions) + 1
        matrix_size = (
            variant_info.get("matrix_size")
            or layout_info.get("matrix_size")
            or board_info.get("matrix_size")
            or {}
        )
        rows = matrix_size.get("rows", rows)
        cols = matrix_size.get("cols", cols)

        usb = variant_info.get("usb", {}) or board_info.get("usb", {})
        pid = usb.get("pid")
        vid = usb.get("vid") or "0x3434"
        if not pid:
            raise RuntimeError(f"Missing USB PID for {variant_dir}")

        features = (
            variant_info.get("features")
            or layout_info.get("features")
            or board_info.get("features")
            or {}
        )
        has_rgb = bool(features.get("rgb_matrix"))
        has_encoder = bool(
            variant_info.get("encoder")
            or layout_info.get("encoder")
            or board_info.get("encoder")
        )

        return KeyboardMetadata(
            board_dir=board_dir,
            variant_dir=variant_dir,
            variant_tokens=variant_tokens,
            layout_data=layout_data,
            rows=rows,
            cols=cols,
            pid=pid,
            vid=vid,
            has_rgb=has_rgb,
            has_encoder=has_encoder,
            min_matrix=min(matrix_positions),
            max_matrix=max(matrix_positions),
        )

    def _walk_to_board(self, variant_dir: Path, board_dir: Path) -> Iterable[Path]:
        current = variant_dir
        while True:
            yield current
            if current == board_dir:
                break
            if current == current.parent:
                break
            current = current.parent

    def _load_via_definition(self, metadata: KeyboardMetadata, rel_parts: Sequence[str]) -> dict:
        try:
            via_def = self._resolve_via_json(metadata)
        except ValueError:
            via_def = None
        if via_def is None:
            via_def = {
                "name": f"{' '.join(self._format_part(p) for p in ('Keychron', *rel_parts))} (Vial)",
                "vendorId": metadata.vid,
                "productId": metadata.pid,
                "matrix": {"rows": metadata.rows, "cols": metadata.cols},
                "layouts": {"keymap": self._build_layout(metadata.layout_data)},
                "customKeycodes": DEFAULT_KEYCODES,
            }
        else:
            name = via_def.get("name", "")
            if "(Vial)" not in name:
                via_def["name"] = (name or rel_parts[0]) + " (Vial)"
            via_def.setdefault("vendorId", metadata.vid)
            via_def.setdefault("productId", metadata.pid)
            via_def.setdefault("matrix", {"rows": metadata.rows, "cols": metadata.cols})
            via_def.setdefault("customKeycodes", DEFAULT_KEYCODES)
        if metadata.has_rgb:
            via_def["lighting"] = "vialrgb"
        return via_def

    def _materialize_vial_keymap(self, via_dir: Path, metadata: KeyboardMetadata, via_def: dict) -> None:
        vial_dir = metadata.variant_dir / "keymaps" / "vial"
        if vial_dir.exists():
            shutil.rmtree(vial_dir)
        shutil.copytree(via_dir, vial_dir)

        rules_path = vial_dir / "rules.mk"
        lines = rules_path.read_text().splitlines() if rules_path.exists() else []
        for line in ("VIA_ENABLE = yes", "VIAL_ENABLE = yes"):
            if line not in lines:
                lines.append(line)
        if metadata.has_rgb and "VIALRGB_ENABLE = yes" not in lines:
            lines.append("VIALRGB_ENABLE = yes")
        if metadata.has_encoder and "ENCODER_MAP_ENABLE = yes" not in lines:
            lines.append("ENCODER_MAP_ENABLE = yes")
        rules_path.write_text("\n".join(lines) + "\n")

        uid = ', '.join(f"0x{byte:02X}" for byte in secrets.token_bytes(8))
        config_path = vial_dir / "config.h"
        config_path.write_text(
            "\n".join(
                [
                    "#pragma once",
                    "",
                    f"#define VIAL_KEYBOARD_UID {{{uid}}}",
                    f"#define VIAL_UNLOCK_COMBO_ROWS {{ {metadata.min_matrix[0]}, {metadata.max_matrix[0]} }}",
                    f"#define VIAL_UNLOCK_COMBO_COLS {{ {metadata.min_matrix[1]}, {metadata.max_matrix[1]} }}",
                    "",
                ]
            )
            + "\n"
        )

        vial_json = vial_dir / "vial.json"
        vial_json.write_text(json.dumps(via_def, indent=2) + "\n")

    def _resolve_via_json(self, metadata: KeyboardMetadata) -> Optional[dict]:
        pid = metadata.pid.lower()
        if pid in self.pid_cache:
            return json.loads(json.dumps(self.pid_cache[pid][0][1]))
        via_dir = metadata.board_dir / "via_json"
        if not via_dir.is_dir():
            raise ValueError
        tokens: List[str] = []
        if metadata.variant_tokens:
            parts = list(metadata.variant_tokens)
            while parts:
                tokens.append('_'.join(parts))
                parts = parts[:-1]
        for token in tokens:
            for path in sorted(via_dir.glob('*.json')):
                if token and token in path.stem:
                    with path.open() as fp:
                        data = json.load(fp)
                    self.pid_cache.setdefault(pid, []).append((path, data))
                    return json.loads(json.dumps(data))
        files = sorted(via_dir.glob('*.json'))
        if not files:
            raise ValueError
        with files[0].open() as fp:
            data = json.load(fp)
        self.pid_cache.setdefault(pid, []).append((files[0], data))
        return json.loads(json.dumps(data))

    def _build_layout(self, layout_data: List[dict]) -> List[List[object]]:
        rows: Dict[float, List[dict]] = {}
        last_y = 0.0
        for key in layout_data:
            y = key.get('y', last_y)
            last_y = y
            rows.setdefault(y, []).append(key)
        ordered_rows: List[List[object]] = []
        for y in sorted(rows.keys()):
            current_x = 0.0
            row: List[object] = []
            for key in sorted(rows[y], key=lambda item: item.get('x', 0.0)):
                x = key.get('x', current_x)
                delta = round(x - current_x, 4)
                if delta > 0:
                    row.append({'x': delta})
                    current_x += delta
                modifiers = {field: key[field] for field in ('w', 'h', 'w2', 'h2', 'x2', 'y2') if field in key}
                if modifiers:
                    row.append(modifiers)
                matrix = key['matrix']
                row.append(f"{matrix[0]},{matrix[1]}")
                current_x += key.get('w', 1)
            ordered_rows.append(row)
        return ordered_rows

    @staticmethod
    def _format_part(part: str) -> str:
        tokens = part.replace('_', ' ').split()
        return ' '.join(tok.upper() if tok.isalpha() and len(tok) <= 3 else tok.capitalize() for tok in tokens)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        '--keyboard-root',
        default='keyboards/keychron',
        type=Path,
        help='Path that contains the Keychron keyboard folders.',
    )
    parser.add_argument('--dry-run', action='store_true', help='Print actions without writing any files.')
    args = parser.parse_args()

    converter = KeychronVialConverter(args.keyboard_root, dry_run=args.dry_run)
    converter.run()


if __name__ == '__main__':
    main()
