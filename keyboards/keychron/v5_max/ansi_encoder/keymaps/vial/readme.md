# Vial support for Keychron V5 Max ANSI Encoder (Knob)

This keymap adds [Vial](https://get.vial.today/) support to the Keychron V5 Max ANSI keyboard with encoder (knob).

## Building

To build the firmware:

```shell
make keychron/v5_max/ansi_encoder:vial
```

The compiled firmware will be located in `keychron_v5_max_ansi_encoder_vial.bin` in the QMK root directory.

## Flashing

1. Enter bootloader mode by either pressing the reset button on the back of the PCB or using the key combination if defined in your keymap.
2. Use a QMK compatible flashing tool to flash the firmware file.

## Features

- Full compatibility with Vial GUI
- Supports encoder (knob) remapping
- Preserves all the Keychron V5 Max features including RGB and wireless functionality
