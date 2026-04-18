# Keychron V2 Max

![Keychron V2 Max](https://cdn.shopify.com/s/files/1/0059/0630/1017/files/Keychron-V2-Max-wireless-mechanical-keyboard-1.jpg)

A customizable 65% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron V2 Max
* Hardware Availability: [Keychron V2 Max QMK/VIA Wireless Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-v2-max-qmk-via-wireless-custom-mechanical-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make keychron/v2_max/ansi_encoder:keychron
    make keychron/v2_max/iso_encoder:keychron
    make keychron/v2_max/jis_encoder:keychron
    
Flashing example for this keyboard:

    make keychron/v2_max/ansi_encoder:keychron:flash
    make keychron/v2_max/iso_encoder:keychron:flash
    make keychron/v2_max/jis_encoder:keychron:flash
    
**Reset Key**: Disconnect the USB cable, toggle mode switch to "Cable", hold down the *Esc* key or reset button underneath space bar, then connect the USB cable.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, configure layers, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, and adjust lighting - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, providing a simpler browser-based setup flow for supported boards. Safari and other non-Chromium browsers will not work with Keychron Launcher.

