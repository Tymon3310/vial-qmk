# Keychron C1 Pro

![Keychron C1 Pro](https://i.imgur.com/Svdm4lph.jpg)

A customizable 80% TKL keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron C1 Pro
* Hardware Availability: [Keychron](https://www.keychron.com)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/c1/ansi/rgb:default
    make keychron/c1/ansi/white:default

Flashing example for this keyboard:

    make keychron/c1/ansi/rgb:default:flash
    make keychron/c1/ansi/white:default:flash

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, tune Hall Effect settings, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, adjust lighting, and fine-tune HE sensitivity - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, and supports features beyond VIA such as Hall Effect actuation point tuning and rapid trigger configuration. Safari and other non-Chromium browsers will not work with Keychron Launcher.
