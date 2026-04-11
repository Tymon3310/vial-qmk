# vial-qmk (Keychron Edition)

Fork of [vial-kb/vial-qmk](https://github.com/vial-kb/vial-qmk) merged with [Keychron's QMK firmware](https://github.com/keychron/qmk_firmware) to bring full Vial support to Keychron keyboards.

This is part of the [Keychron Vial ecosystem](https://github.com/tymon3310/keychron-vial) — see the central repo for an overview of all projects, supported keyboards, and documentation.

[![Star this repo](https://img.shields.io/github/stars/Tymon3310/vial_qmk?style=social&label=Star%20this%20repo)](https://github.com/Tymon3310/vial_qmk)

## Why Open Source?

Keychron is the first major keyboard brand to fully open-source both its [firmware](https://github.com/Keychron/qmk_firmware) and [hardware design](https://github.com/Keychron/Keychron-Keyboards-Hardware-Design). We believe you should be able to see, verify, and modify every line of code that runs on your keyboard. Open source means full transparency — no black boxes between you and your hardware.

This fork builds on that philosophy by adding full [Vial](https://get.vial.today/) support to the Keychron QMK firmware, giving you real-time keyboard configuration through a GUI — no firmware rebuild required for keymap changes.

## Branches

| Branch | QMK Base | Status | Description |
|--------|----------|--------|-------------|
| [`vial-keychron`](https://github.com/tymon3310/vial-qmk/tree/vial-keychron) | [wls_2025q1](https://github.com/keychron/qmk_firmware/tree/wls_2025q1) | Legacy | Older QMK base. Does not fully support the custom GUI features. |
| [`vial-updated-keychron`](https://github.com/tymon3310/vial-qmk/tree/vial-updated-keychron) | [2025q3](https://github.com/Keychron/qmk_firmware/tree/2025q3) | **Active** | Newer QMK base (merged with Keychron 2025 Q3). Fully supports all custom GUI features. |

> **Note:** Not all keyboards have been ported to `vial-updated-keychron` yet. Keyboards still only available on `vial-keychron` are marked in the [supported keyboards list](https://github.com/tymon3310/keychron-vial#supported-keyboards).

## Features

- **Full Vial protocol support** — real-time keymap editing, macros, tap dance, combos, key overrides
- **Hall Effect magnetic switch support** — adjustable actuation, rapid trigger, DKS, gamepad mode on HE boards (via custom GUI)
- **Keychron RGB** — per-key RGB, mixed mode, OS indicator customization (via custom GUI)
- **Keychron Settings** — debounce, NKRO, report rate, wireless low power mode (via custom GUI)
- **Snap Click (SOCD)** — simultaneous opposite cardinal direction resolution for non-HE keyboards (via custom GUI)
- **Wireless connectivity** — Bluetooth 5.1 and 2.4 GHz firmware for wireless models
- **Wireless (Bridged) Vial** — full Vial support over Keychron Link 2.4 GHz dongle (via custom GUI)
- **RGB Matrix lighting** — per-key RGB effects and customization
- **Multiple layout variants** — ANSI, ISO, and JIS for every supported board
- **Full QMK feature set** — layers, tap-dance, combos, macros, encoders, OLED, and more

## Getting Started

### Option A: Use Vial Web (no code required)

If you want to use Vial for real-time keymap editing and Keychron-specific configuration:

1. Open [vial.tymon3310.dev](https://vial.tymon3310.dev) in a Chromium-based browser
2. Connect your Keychron keyboard via USB
3. Configure keymaps, Keychron settings, RGB, and HE options — changes apply instantly

Alternatively, use [Pipette Desktop](https://github.com/tymon3310/pipette-desktop) (recommended) or [vial-gui](https://github.com/tymon3310/vial-gui) for the full desktop experience.

### Option B: Use Keychron Launcher (no Vial)

If you just want to remap keys, tune Hall Effect settings, or change lighting without Vial:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, adjust lighting, and fine-tune HE sensitivity — changes apply instantly

### Option C: Build from source

Set up your build environment and compile custom firmware:

```bash
python3 -m pip install qmk
qmk setup Keychron/qmk_firmware
qmk compile -kb keychron/q1_he/ansi_encoder -km keychron
qmk flash -kb keychron/q1_he/ansi_encoder -km keychron
```

More build examples:

```bash
make keychron/q1_he/ansi_encoder:keychron
make keychron/k8_pro/ansi/rgb:keychron
make keychron/v1_max/ansi_encoder:keychron:flash
```

See the [QMK build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and [make guide](https://docs.qmk.fm/#/getting_started_make_guide) for details. New to QMK? Start with the [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Supported Keyboards

100+ Keychron keyboards across Q, V, K, C, and Lemokey series:

| Series | Boards | Type |
|--------|--------|------|
| **Q HE** | Q1 HE, Q2 HE, Q3 HE, Q4 HE, Q5 HE, Q6 HE, Q12 HE | Hall Effect, wireless |
| **Q / Q Pro / Q Max** | Q0–Q12, Q60, Q65, Q1–Q14 PRO, Q0–Q15 MAX | Mechanical, various |
| **K HE** | K2 HE, K4 HE, K6 HE, K8 HE, K10 HE | Hall Effect, wireless |
| **K Pro / K Max** | K1–K17 PRO, K1–K17 MAX | Mechanical, wireless |
| **V / V Max** | V1–V10, V1–V10 MAX, V1 8K | Mechanical, wired/wireless |
| **C Pro** | C1–C3 PRO, C1–C2 PRO V2, C1–C3 PRO 8K | Mechanical, wired |
| **S / X** | S1, X0 | Mechanical |
| **Lemokey** | L1 HE, P1 HE, P2 HE | Hall Effect gaming |

See [keychron-vial](https://github.com/tymon3310/keychron-vial#supported-keyboards) for the full list with layout variants.

All board definitions live under [`keyboards/keychron/`](keyboards/keychron/) and [`keyboards/lemokey/`](keyboards/lemokey/). Each board folder contains its own `readme.md` with exact build targets, product links, and reset instructions.

## Keychron-Specific Protocol

This firmware implements Keychron's proprietary HID commands alongside the standard Vial protocol:

| Command Range | Feature |
|---------------|---------|
| `0xA0`–`0xA3` | Core commands (protocol version, firmware version, feature flags, default layer) |
| `0xA7` | Misc commands (debounce, snap click, NKRO, report rate, wireless LPM) |
| `0xA8` | Keychron RGB (per-key RGB, mixed mode, effect selection) |
| `0xA9` | Analog Matrix (Hall Effect — profiles, calibration, rapid trigger, DKS, gamepad mode) |
| `0xAA` | Wireless DFU |
| `0xB1`–`0xBA` | Bridge/dongle protocol (2.4 GHz wireless tunneling) |

### Wireless (Bridged) Vial

Full Vial support over Keychron's 2.4 GHz wireless dongle (Keychron Link, VID:PID `3434:D030` USB-A / `3434:D031` USB-C). Requires the wireless XOR encoding patch to work around a hardware limitation in the LKBT51 wireless module.

## Hardware Design

For PCB files, schematics, and hardware design resources, see the companion repository:

[Keychron-Keyboards-Hardware-Design](https://github.com/Keychron/Keychron-Keyboards-Hardware-Design)

## Community and Support

- **Join the community**
  Join the [Keychron Discord](https://discord.com/invite/HAYbRrTsjN) to share builds, ask questions, and help grow the hardware modding community.
- [Keychron Website](https://www.keychron.com)
- [Keychron on Reddit](https://www.reddit.com/r/Keychron/)
- [QMK Discord](https://discord.gg/qmk)
- [QMK Documentation](https://docs.qmk.fm)
- [Vial Discord](https://discord.gg/zNKEUXTKwF)
- [Vial Documentation](https://get.vial.today/)

## Contributing

Contributions are welcome — whether it's a new keymap, a bug fix, or documentation improvement. See [`docs/contributing.md`](docs/contributing.md) for guidelines on submitting pull requests.

## Note

> **Note:** I only have a **V5 Max ANSI Encoder** for physical testing. If you encounter issues with any other keyboard, please [open an issue](https://github.com/tymon3310/vial-qmk/issues) and let me know.

## Protocol Documentation

Detailed protocol documentation (reverse-engineered from Keychron's Launcher and implemented in this firmware) is available in the [keychron-vial](https://github.com/tymon3310/keychron-vial) repository under `docs/`.

## Credits

- [vial-kb/vial-qmk](https://github.com/vial-kb/vial-qmk) — Original Vial QMK fork
- [Keychron/qmk_firmware](https://github.com/keychron/qmk_firmware) — Keychron's QMK base
- [QMK Firmware](https://github.com/qmk/qmk_firmware) — The QMK project

## License

This project is licensed under the [GNU General Public License v2.0](LICENSE).

This repository tracks the [upstream QMK firmware](https://github.com/qmk/qmk_firmware) with Keychron-specific board definitions and firmware additions.
