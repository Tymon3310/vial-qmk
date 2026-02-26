# Keychron V1

![Keychron v1](https://www.keychron.com/cdn/shop/products/Keychron-V1-Custom-Mechanical-Keyboard-frosted-black-K-Pro-red.jpg)

A customizable 75% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron V1
* Hardware Availability: [Keychron V1 QMK Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-v1-qmk-via-custom-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make keychron/v1/ansi:keychron
    make keychron/v1/ansi_encoder:keychron
    make keychron/v1/iso:keychron
    make keychron/v1/iso_encoder:keychron
    make keychron/v1/jis:keychron
    make keychron/v1/jis_encoder:keychron

Flashing example for this keyboard:

    make keychron/v1/ansi:keychron:flash
    make keychron/v1/ansi_encoder:keychron:flash
    make keychron/v1/iso:keychron:flash
    make keychron/v1/iso_encoder:keychron:flash
    make keychron/v1/jis:keychron:flash
    make keychron/v1/jis_encoder:keychron:flash

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
