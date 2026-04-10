# Keychron Q2

![Keychron Q2](https://i.imgur.com/9bJ6Moh.jpg)

A customizable 65% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron Q2
* Hardware Availability: [Keychron Q2 QMK Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-q2-qmk-custom-mechanical-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/q2/ansi:keychron
    make keychron/q2/ansi_encoder:keychron
    make keychron/q2/iso:keychron
    make keychron/q2/iso_encoder:keychron
    make keychron/q2/jis:keychron
    make keychron/q2/jis_encoder:keychron

Flashing example for this keyboard:

    make keychron/q2/ansi:keychron:flash
    make keychron/q2/ansi_encoder:keychron:flash
    make keychron/q2/iso:keychron:flash
    make keychron/q2/iso_encoder:keychron:flash
    make keychron/q2/jis:keychron:flash
    make keychron/q2/jis_encoder:keychron:flash

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

