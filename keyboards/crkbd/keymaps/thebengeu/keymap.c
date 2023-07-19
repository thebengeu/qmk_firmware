#include QMK_KEYBOARD_H
#include "ps2_mouse.h"

uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    debug_enable=true;
}
#endif

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
bool auto_mouse_activation(report_mouse_t mouse_report) {
    return mouse_report.x || mouse_report.y || (mouse_report.buttons & PS2_MOUSE_BTN_MASK);
}

void ps2_mouse_init_user(void) {
    set_auto_mouse_enable(true);
}
#endif
