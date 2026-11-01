# vial-qmk (Keychron Edition)

[vial-kb/vial-qmk](https://github.com/vial-kb/vial-qmk) merged with [Keychron's QMK firmware](https://github.com/Keychron/qmk_firmware), so Keychron and Lemokey keyboards can run [Vial](https://get.vial.today/).

This is the firmware part of the [Keychron Vial project](https://github.com/tymon3310/keychron-vial), which has the list of supported keyboards, the configurators, and setup instructions.

## Branches

| Branch | Keychron base | Status | Notes |
|--------|---------------|--------|-------|
| [`vial-updated-keychron`](https://github.com/tymon3310/vial-qmk/tree/vial-updated-keychron) | [2025q3](https://github.com/Keychron/qmk_firmware/tree/2025q3) | **Active** | All Keychron features in the configurators work |
| [`vial-keychron`](https://github.com/tymon3310/vial-qmk/tree/vial-keychron) | [wls_2025q1](https://github.com/keychron/qmk_firmware/tree/wls_2025q1) | Legacy | Some Keychron features in the configurators don't work |

Keyboards that are only on `vial-keychron` are marked in the [supported keyboards list](https://github.com/tymon3310/keychron-vial#supported-keyboards).

## Features

- **Vial:** live keymap editing, macros, tap dance, combos, key overrides
- **Keychron settings:** debounce, NKRO, report rate, wireless sleep timeouts
- **Keychron RGB:** per-key colours, mixed mode, OS indicator colours
- **Snap Click (SOCD)** on keyboards without Hall Effect switches
- **Hall Effect:** actuation point, Rapid Trigger, DKS, gamepad mode, calibration, profiles
- **Wireless:** Keychron's Bluetooth and 2.4 GHz firmware, plus Vial over the Keychron Link 2.4 GHz receiver
- **Encoders** through Vial's encoder map

The Keychron settings, RGB, Snap Click, Hall Effect and 2.4 GHz editing need [Pipette](https://github.com/tymon3310/pipette-desktop) ([web](https://pipette.tymon3310.dev)), or [vial-gui](https://github.com/tymon3310/vial-gui) ([web](https://vial.tymon3310.dev)). Upstream Vial only shows the standard Vial features.

## Building

Set up the QMK CLI with this repo, then build or flash the `vial` keymap of your keyboard:

```bash
pipx install qmk
qmk setup https://github.com/tymon3310/vial-qmk.git -b vial-updated-keychron
qmk compile -kb keychron/v5_max/ansi_encoder -km vial
qmk flash -kb keychron/v5_max/ansi_encoder -km vial
```

Boards are in [`keyboards/keychron/`](keyboards/keychron/) and [`keyboards/lemokey/`](keyboards/lemokey/). Each board folder has a `readme.md` with its build targets and how to enter the bootloader. See the [QMK build guide](https://docs.qmk.fm/#/getting_started_build_tools) if you are new to QMK.

## Keychron protocol

Besides the Vial protocol, the firmware answers Keychron's raw HID commands (`keyboards/keychron/common/keychron_raw_hid.h`):

| Command | Feature |
|---------|---------|
| `0xA0`–`0xA3` | Protocol version, firmware version, supported features, default layer |
| `0xA7` | Misc: debounce, Snap Click, NKRO, report rate, wireless sleep |
| `0xA8` | Keychron RGB: per-key colours, mixed mode, effects |
| `0xA9` | Analog matrix (Hall Effect): profiles, calibration, Rapid Trigger, DKS, gamepad |
| `0xAA` | Wireless DFU |
| `0xAC` | Battery level |

### Vial over 2.4 GHz

Vial works through the Keychron Link receiver (`3434:D030` and `3434:D031`). The keyboard's wireless module (LKBT51) crashes on some byte values in raw HID packets (the `0xF0`–`0xFF` range), so the configurator and firmware XOR every byte of a Vial packet with `0x28` when it goes over the receiver. See `WIRELESS_RAW_HID_XOR_KEY` in `keyboards/keychron/common/wireless/wireless.h`.

The full protocol notes are in the [keychron-vial docs](https://github.com/tymon3310/keychron-vial/tree/main/docs).

## Hardware

Keychron publishes PCB files and schematics in [Keychron-Keyboards-Hardware-Design](https://github.com/Keychron/Keychron-Keyboards-Hardware-Design).

## Testing

Changes are tested on a **V5 Max ANSI Encoder**. If something doesn't work on another keyboard, please [open an issue](https://github.com/tymon3310/vial-qmk/issues).

## Contributing

Pull requests are welcome: new ports, fixes and documentation. See [`docs/contributing.md`](docs/contributing.md) and the [porting notes](https://github.com/tymon3310/keychron-vial#contributing).

## Links

- [Keychron Discord](https://discord.com/invite/HAYbRrTsjN), [r/Keychron](https://www.reddit.com/r/Keychron/)
- [QMK Discord](https://discord.gg/qmk), [QMK documentation](https://docs.qmk.fm)
- [Vial Discord](https://discord.gg/zNKEUXTKwF), [Vial documentation](https://get.vial.today/)

## Credits

- [vial-kb/vial-qmk](https://github.com/vial-kb/vial-qmk)
- [Keychron/qmk_firmware](https://github.com/Keychron/qmk_firmware)
- [QMK Firmware](https://github.com/qmk/qmk_firmware)

## License

[GNU General Public License v2.0](LICENSE).
