# Keychron K13 Max

![Keychron K13 Max](https://cdn.shopify.com/s/files/1/0059/0630/1017/files/K13-Max-4.jpg)

A customizable 80% keyboard with a numpad
* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron K13 Max
* Hardware Availability: [Keychron K13 Max QMK/VIA Wireless Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-k13-max-qmk-via-wireless-custom-mechanical-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/k13_max/ansi/rgb:keychron
    make keychron/k13_max/ansi/white:keychron
    make keychron/k13_max/iso/rgb:keychron
    make keychron/k13_max/iso/white:keychron
    make keychron/k13_max/jis/rgb:keychron
    make keychron/k13_max/jis/white:keychron

Flashing example for this keyboard:

    make keychron/k13_max/ansi/rgb:keychron:flash
    make keychron/k13_max/ansi/white:keychron:flash
    make keychron/k13_max/iso/rgb:keychron:flash
    make keychron/k13_max/iso/white:keychron:flash
    make keychron/k13_max/jis/rgb:keychron:flash
    make keychron/k13_max/jis/white:keychron:flash

**Reset Key**: Toggle mode switch to "Cable", hold down the *Esc* key or reset button underneath space bar while connecting the USB cable,

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

