# Keychron QMK Firmware

[![Star this repo](https://img.shields.io/github/stars/Keychron/qmk_firmware?style=social&label=Star%20this%20repo)](https://github.com/Keychron/qmk_firmware)

![Keychron Keyboards](https://raw.githubusercontent.com/Keychron/Keychron-Keyboards-Hardware-Design/main/docs/assets/hero-keychron-hardware-design.jpg)

Official QMK firmware for Keychron and Lemokey keyboards. This repository contains the firmware source, build configurations, and keymaps for 63+ boards across the Q, Q HE, Q Max, K HE, K Max, K Pro, V, V Max, C Pro, S, X, and Lemokey series.

## Why Open Source?

Keychron is the first major keyboard brand to fully open-source both its [firmware](https://github.com/Keychron/qmk_firmware) and [hardware design](https://github.com/Keychron/Keychron-Keyboards-Hardware-Design). We believe you should be able to see, verify, and modify every line of code that runs on your keyboard. Open source means full transparency — no black boxes between you and your hardware.

We also want to build something bigger than what any single company can do alone. By opening our firmware to the community, developers and enthusiasts can push what keyboards are capable of — custom keymaps, new features, creative workflows — and those contributions make every Keychron keyboard better for everyone.

## Features

- **Hall Effect magnetic switch support** — adjustable actuation and rapid trigger on HE boards
- **Wireless connectivity** — Bluetooth 5.1 and 2.4 GHz firmware for wireless models
- **[Keychron Launcher](https://launcher.keychron.com/)** — remap keys, tune HE settings, and configure lighting from your browser with no setup
- **RGB Matrix lighting** — per-key RGB effects and customization
- **Multiple layout variants** — ANSI, ISO, and JIS for every supported board
- **Full QMK feature set** — layers, tap-dance, combos, macros, encoders, OLED, and more

## Getting Started

### Option A: Use Keychron Launcher (no code required)

If you just want to remap keys, tune Hall Effect settings, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, adjust lighting, and fine-tune HE sensitivity — changes apply instantly

Keychron Launcher works out of the box with no JSON import required, and supports features beyond VIA such as Hall Effect actuation point tuning and rapid trigger configuration. Safari and other non-Chromium browsers will not work with Keychron Launcher.

### Option B: Build from source

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

All board definitions live under [`keyboards/keychron/`](keyboards/keychron/) and [`keyboards/lemokey/`](keyboards/lemokey/).

| Series | Boards | Type |
|--------|--------|------|
| **Q HE** | Q1 HE, Q2 HE, Q3 HE, Q4 HE, Q5 HE, Q6 HE, Q12 HE | Hall Effect, wireless |
| **Q / Q Max** | Q0, Q1 v1/v2, Q1 Max, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q9 Plus, Q10, Q11, Q12, Q60, Q65 | Mechanical, various |
| **K HE** | K2 HE, K4 HE, K6 HE, K8 HE, K10 HE | Hall Effect, wireless |
| **K Max / K Pro** | K4 Max, K8 Max, K8 Pro, K9 Max | Mechanical, wireless |
| **V / V Max** | V1, V1 8K, V1 Max, V2, V3, V4, V5, V5 Max, V6, V6 v2, V6 Max, V7, V8, V10 | Mechanical, wired/wireless |
| **C Pro** | C1 Pro, C1 Pro v2, C1 Pro 8K, C2 Pro, C2 Pro v2, C2 Pro 8K, C3 Pro, C3 Pro 8K | Mechanical, wired |
| **S / X** | S1, X0 | Mechanical |
| **Lemokey** | L1 HE, P1 HE, P2 HE | Hall Effect gaming |

Each board folder contains its own `readme.md` with exact build targets, product links, and reset instructions.

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

## Contributing

Contributions are welcome — whether it's a new keymap, a bug fix, or documentation improvement. See [`docs/contributing.md`](docs/contributing.md) for guidelines on submitting pull requests.

## License

This project is licensed under the [GNU General Public License v2.0](LICENSE).

This repository tracks the [upstream QMK firmware](https://github.com/qmk/qmk_firmware) with Keychron-specific board definitions and firmware additions.
