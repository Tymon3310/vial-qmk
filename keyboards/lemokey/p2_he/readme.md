# Lemokey P2 HE

![Lemokey P2 HE](https://cdn.shopify.com/s/files/1/0059/0630/1017/files/Lemokey-P2-HE-Wireless-Magnetic-Switch-Custom-Gaming-Keyboard-Shine-Through-Keycap-Black-Frame-Version-13.jpg)

A customizable 65% hall effect keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Lemokey P2 HE
* Hardware Availability: [Lemokey P2 HE QMK/VIA Wireless Custom Mechanical Keyboard](https://www.lemokey.com/products/lemokey-p2-he-wireless-magnetic-switch-custom-gaming-keyboard)

## Option A: Build And Flash Firmware

Make example for this keyboard (after setting up your build environment):

    make lemokey/p2_he/ansi:lemokey

Flashing example for this keyboard:

    make lemokey/p2_he/ansi:lemokey:flash

**Reset Key**: Disconnect the USB cable, toggle mode switch to "Cable", hold down the *Esc* key or reset button underneath space bar, then connect the USB cable.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Option B: Use Keychron Launcher (no code required)

If you just want to remap keys, tune Hall Effect settings, or change lighting, you don't need to build firmware:

1. Open [Keychron Launcher](https://launcher.keychron.com/) in a Chromium-based browser such as Google Chrome, Microsoft Edge, Brave, Opera, or Vivaldi
2. Connect your Keychron keyboard via USB
3. Remap keys, configure layers, adjust lighting, and fine-tune HE sensitivity - changes apply instantly

Keychron Launcher works out of the box with no JSON import required, and supports features beyond VIA such as Hall Effect actuation point tuning and rapid trigger configuration. Safari and other non-Chromium browsers will not work with Keychron Launcher.

