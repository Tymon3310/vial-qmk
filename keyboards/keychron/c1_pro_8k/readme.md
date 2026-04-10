# Keychron C1 Pro 8K

![Keychron C1 Pro 8K](https://cdn.shopify.com/s/files/1/0059/0630/1017/files/Keychron-C1-Pro-8K-QMK-VIA-Wired-Mechanical-Keyboard---1.jpg)

A customizable TLK keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron C1 Pro 8K
* Hardware Availability: [Keychron](https://www.keychron.com/products/keychron-c1-pro-8k-qmk-wired-mechanical-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/c1_pro_8k/ansi/rgb:keychron
    make keychron/c1_pro_8k/ansi/white:keychron
    make keychron/c1_pro_8k/ansi/lightless:keychron
    make keychron/c1_pro_8k/iso:keychron
    make keychron/c1_pro_8k/jis:keychron

Flashing example for this keyboard:

    make keychron/c1_pro_8k/ansi:keychron:flash
    make keychron/c1_pro_8k/ansi/white:keychron:flash
    make keychron/c1_pro_8k/ansi/lightless:keychron:flash
    make keychron/c1_pro_8k/iso:keychron:flash
    make keychron/c1_pro_8k/jis:keychron:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

