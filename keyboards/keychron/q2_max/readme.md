# Keychron Q2 Max

![Keychron Q2 Max](https://cdn.shopify.com/s/files/1/0059/0630/1017/files/Keychron-Q2-Max-65_-Layout-Wireless-Custom-Mechanical-Keyboard-Carbon-Black.jpg)

A customizable wireless 65% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron Q2 Max
* Hardware Availability: [Keychron Q2 Max QMK/VIA Wireless Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-q2-max-qmk-via-wireless-custom-mechanical-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/q2_max/ansi_encoder:keychron
    make keychron/q2_max/iso_encoder:keychron

Flashing example for this keyboard:

    make keychron/q2_max/ansi_encoder:keychron:flash
    make keychron/q2_max/iso_encoder:keychron:flash

**Reset Key**: Disconnect the USB cable, toggle mode switch to "Cable", hold down the *Esc* key or reset button underneath space bar, then connect the USB cable.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

