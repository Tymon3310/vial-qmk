# Keychron K8 Pro

![Keychron K8 Pro](https://github.com/Keychron/ProductImage/blob/main/K_Pro/k8_pro.jpg?raw=true)

A customizable 87 keys TKL keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron K8 Pro
* Hardware Availability: [Keychron K8 Pro QMK/VIA Wireless Mechanical Keyboard](https://www.keychron.com/products/keychron-k8-pro-qmk-via-wireless-mechanical-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/k8_pro/ansi/rgb:keychron
    make keychron/k8_pro/ansi/white:keychron
    make keychron/k8_pro/iso/rgb:keychron
    make keychron/k8_pro/iso/white:keychron
    make keychron/k8_pro/jis/rgb:keychron
    make keychron/k8_pro/jis/white:keychron

Flashing example for this keyboard:

    make keychron/k8_pro/ansi/rgb:keychron:flash
    make keychron/k8_pro/ansi/white:keychron:flash
    make keychron/k8_pro/iso/rgb:keychron:flash
    make keychron/k8_pro/iso/white:keychron:flash
    make keychron/k8_pro/jis/rgb:keychron:flash
    make keychron/k8_pro/jis/white:keychron:flash

**Reset Key**: Connect the USB cable, toggle mode switch to "Off", hold down the *Esc* key or reset button underneath space bar, then toggle then switch to "Cable".

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

