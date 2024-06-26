# stront

![stront](https://i.imgur.com/Tu0XLeeh.jpg)

Split modular keyboard with 38 or 40 keys, LCD display and Cirque/Azoteq touchpads.

-   Keyboard Maintainer: [zzeneg](https://github.com/zzeneg)
-   Hardware Supported: Stront PCBs, Waveshare RP2040 Zero
-   Hardware Availability: [GitHub](https://github.com/zzeneg/stront)

Make examples for this keyboard (after setting up your build environment):

    make stront/38keys:default
    make stront/40keys:default

Flashing examples for this keyboard:

    make stront/38keys:default:flash
    make stront/40keys:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Hardware versions

There are two versions - `stront/38keys` (default) and `stront/40keys`. Make sure to use the correct version for your hardware.

## Module configuration

**stront** is a modular keyboard with a lot of supported modules out of the box and potentially any VIK module. It's not possible to pre-compile a firmware for any possible hardware permutation, so it's the responsibility of the end user to configure it properly. Please see main `config.h` and `rules.mk` for available options and comments. You can easily set up your own pointing device and display.

## Keymaps

-   `default` - sample keymap with home row mods. Not recommended for longer use - create your own.
-   `hid` - default keymap with HID support. Requires additional software running on computer, see https://github.com/zzeneg/qmk-hid-host.

Keymaps have [EE_HANDS](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) enabled, so any side can be master (though using side with touchpad as master is recommended). You have to specify left/right side by flashing with different commands:

`qmk flash -kb stront/38keys -km default -bl uf2-split-left` or `qmk flash -kb stront/40keys -km default -bl uf2-split-left`

and

`qmk flash -kb stront/38keys -km default -bl uf2-split-right` or `qmk flash -kb stront/40keys -km default -bl uf2-split-right`

If your keyboard is flashed already (or you use WSL), you can specify the correct side by pressing key combinations - hold inner thumb key, then hold outer thumb key to activate SYSTEM layer. Now press outer bottom pinky key for left side or inner bottom index key for right side. See [keymap](./keymaps/default/keymap.c) or build guide for better understanding. Reconnect the keyboard to apply changes.

## Bootloader

Enter the bootloader in 2 ways:

-   **Bootmagic reset**: Hold down top outer pinky key and plug in the keyboard
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` - by default you need to hold inner thumb key, then hold outer thumb key and press middle thumb key (see [keymap.c](./keymaps/default/keymap.c) for details). It's a complicated combination to avoid accidental activations.

RP2040 Zero has physical boot/reset buttons but they are not accessible after the keyboards is assembled, so always keep a `QK_BOOT` key and/or bootmagic feature in your keymaps.
