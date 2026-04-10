# Keychron Q11

![Keychron Q11](https://i.imgur.com/FPTNqKj.jpg)

A customizable 75% split keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron Q11
* Hardware Availability: [Keychron Q11 QMK Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-q11-qmk-custom-mechanical-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/q11/ansi_encoder:default
    make keychron/q11/iso_encoder:default

Flashing example for this keyboard:

    make keychron/q11/ansi_encoder:default:flash
    make keychron/q11/iso_encoder:default:flash

**Reset Key**: The master and slave side should be flashed individually, to enter flashing mode, hold down the key located at *K01*, which programmed as *Esc* while plugging in the keyboard for the master side and hold down the key located at *K67*, which programmed as *Del* while plugging in the keyboard for the slave side.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

