# Keychron C2 Pro

![Keychron C2 Pro](https://i.imgur.com/BQE1tFOh.jpg)

A customizable 100% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron C2 Pro
* Hardware Availability: [Keychron](https://www.keychron.com)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/c2/ansi/rgb:default
    make keychron/c2/ansi/white:default

Flashing example for this keyboard:

    make keychron/c2/ansi/rgb:default:flash
    make keychron/c2/ansi/white:default:flash

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

