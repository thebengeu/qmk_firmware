/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "util.h"

#ifdef JOYSTICK_ENABLE
#    include "joystick.h"
#endif

#ifdef DIGITIZER_ENABLE
#    include "digitizer_driver.h"
#endif

// clang-format off

/* HID report IDs */
enum hid_report_ids { 
    REPORT_ID_ALL = 0,
    REPORT_ID_KEYBOARD = 1,
    REPORT_ID_MOUSE,
    REPORT_ID_SYSTEM,
    REPORT_ID_CONSUMER,
    REPORT_ID_PROGRAMMABLE_BUTTON,
    REPORT_ID_NKRO,
    REPORT_ID_JOYSTICK,
    REPORT_ID_DIGITIZER,
    REPORT_ID_DIGITIZER_STYLUS,
    REPORT_ID_DIGITIZER_CONFIGURATION,
    REPORT_ID_DIGITIZER_GET_FEATURE,
    REPORT_ID_DIGITIZER_FUNCTION_SWITCH,
    REPORT_ID_DIGITIZER_CERTIFICATE,
    REPORT_ID_COUNT = REPORT_ID_DIGITIZER_CERTIFICATE
};

#define IS_VALID_REPORT_ID(id) ((id) >= REPORT_ID_ALL && (id) <= REPORT_ID_COUNT)

/* Mouse buttons */
#define MOUSE_BTN_MASK(n) (1 << (n))
enum mouse_buttons {
    MOUSE_BTN1 = MOUSE_BTN_MASK(0),
    MOUSE_BTN2 = MOUSE_BTN_MASK(1),
    MOUSE_BTN3 = MOUSE_BTN_MASK(2),
    MOUSE_BTN4 = MOUSE_BTN_MASK(3),
    MOUSE_BTN5 = MOUSE_BTN_MASK(4),
    MOUSE_BTN6 = MOUSE_BTN_MASK(5),
    MOUSE_BTN7 = MOUSE_BTN_MASK(6),
    MOUSE_BTN8 = MOUSE_BTN_MASK(7)
};

/* Consumer Page (0x0C)
 *
 * See https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf#page=75
 */
enum consumer_usages {
    // 15.5 Display Controls
    SNAPSHOT        = 0x065,
    BRIGHTNESS_UP   = 0x06F, // https://www.usb.org/sites/default/files/hutrr41_0.pdf
    BRIGHTNESS_DOWN = 0x070,
    // 15.7 Transport Controls
    TRANSPORT_RECORD       = 0x0B2,
    TRANSPORT_FAST_FORWARD = 0x0B3,
    TRANSPORT_REWIND       = 0x0B4,
    TRANSPORT_NEXT_TRACK   = 0x0B5,
    TRANSPORT_PREV_TRACK   = 0x0B6,
    TRANSPORT_STOP         = 0x0B7,
    TRANSPORT_EJECT        = 0x0B8,
    TRANSPORT_RANDOM_PLAY  = 0x0B9,
    TRANSPORT_STOP_EJECT   = 0x0CC,
    TRANSPORT_PLAY_PAUSE   = 0x0CD,
    // 15.9.1 Audio Controls - Volume
    AUDIO_MUTE     = 0x0E2,
    AUDIO_VOL_UP   = 0x0E9,
    AUDIO_VOL_DOWN = 0x0EA,
    // 15.15 Application Launch Buttons
    AL_CC_CONFIG       = 0x183,
    AL_EMAIL           = 0x18A,
    AL_CALCULATOR      = 0x192,
    AL_LOCAL_BROWSER   = 0x194,
    AL_LOCK            = 0x19E,
    AL_CONTROL_PANEL   = 0x19F,
    AL_ASSISTANT       = 0x1CB,
    AL_KEYBOARD_LAYOUT = 0x1AE,
    // 15.16 Generic GUI Application Controls
    AC_NEW                         = 0x201,
    AC_OPEN                        = 0x202,
    AC_CLOSE                       = 0x203,
    AC_EXIT                        = 0x204,
    AC_MAXIMIZE                    = 0x205,
    AC_MINIMIZE                    = 0x206,
    AC_SAVE                        = 0x207,
    AC_PRINT                       = 0x208,
    AC_PROPERTIES                  = 0x209,
    AC_UNDO                        = 0x21A,
    AC_COPY                        = 0x21B,
    AC_CUT                         = 0x21C,
    AC_PASTE                       = 0x21D,
    AC_SELECT_ALL                  = 0x21E,
    AC_FIND                        = 0x21F,
    AC_SEARCH                      = 0x221,
    AC_HOME                        = 0x223,
    AC_BACK                        = 0x224,
    AC_FORWARD                     = 0x225,
    AC_STOP                        = 0x226,
    AC_REFRESH                     = 0x227,
    AC_BOOKMARKS                   = 0x22A,
    AC_NEXT_KEYBOARD_LAYOUT_SELECT = 0x29D,
    AC_DESKTOP_SHOW_ALL_WINDOWS    = 0x29F,
    AC_SOFT_KEY_LEFT               = 0x2A0
};

/* Generic Desktop Page (0x01)
 *
 * See https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf#page=26
 */
enum desktop_usages {
    // 4.5.1 System Controls - Power Controls
    SYSTEM_POWER_DOWN             = 0x81,
    SYSTEM_SLEEP                  = 0x82,
    SYSTEM_WAKE_UP                = 0x83,
    SYSTEM_RESTART                = 0x8F,
    // 4.10 System Display Controls
    SYSTEM_DISPLAY_TOGGLE_INT_EXT = 0xB5
};

// clang-format on

#define NKRO_REPORT_BITS 30

#ifdef KEYBOARD_SHARED_EP
#    define KEYBOARD_REPORT_SIZE 9
#else
#    define KEYBOARD_REPORT_SIZE 8
#endif

#define KEYBOARD_REPORT_KEYS 6

#ifdef __cplusplus
extern "C" {
#endif

/*
 * keyboard report is 8-byte array retains state of 8 modifiers and 6 keys.
 *
 * byte |0       |1       |2       |3       |4       |5       |6       |7
 * -----+--------+--------+--------+--------+--------+--------+--------+--------
 * desc |mods    |reserved|keys[0] |keys[1] |keys[2] |keys[3] |keys[4] |keys[5]
 *
 * It is exended to 16 bytes to retain 120keys+8mods when NKRO mode.
 *
 * byte |0       |1       |2       |3       |4       |5       |6       |7        ... |15
 * -----+--------+--------+--------+--------+--------+--------+--------+--------     +--------
 * desc |mods    |bits[0] |bits[1] |bits[2] |bits[3] |bits[4] |bits[5] |bits[6]  ... |bit[14]
 *
 * mods retains state of 8 modifiers.
 *
 *  bit |0       |1       |2       |3       |4       |5       |6       |7
 * -----+--------+--------+--------+--------+--------+--------+--------+--------
 * desc |Lcontrol|Lshift  |Lalt    |Lgui    |Rcontrol|Rshift  |Ralt    |Rgui
 *
 */
typedef struct {
#ifdef KEYBOARD_SHARED_EP
    uint8_t report_id;
#endif
    uint8_t mods;
    uint8_t reserved;
    uint8_t keys[KEYBOARD_REPORT_KEYS];
} PACKED report_keyboard_t;

typedef struct {
    uint8_t report_id;
    uint8_t mods;
    uint8_t bits[NKRO_REPORT_BITS];
} PACKED report_nkro_t;

typedef struct {
    uint8_t  report_id;
    uint16_t usage;
} PACKED report_extra_t;

typedef struct {
    uint8_t  report_id;
    uint32_t usage;
} PACKED report_programmable_button_t;

#ifdef MOUSE_EXTENDED_REPORT
typedef int16_t mouse_xy_report_t;
#else
typedef int8_t mouse_xy_report_t;
#endif

#ifdef WHEEL_EXTENDED_REPORT
typedef int16_t mouse_hv_report_t;
#else
typedef int8_t mouse_hv_report_t;
#endif

typedef struct {
#ifdef MOUSE_SHARED_EP
    uint8_t report_id;
#endif
    uint8_t buttons;
#ifdef MOUSE_EXTENDED_REPORT
    int8_t boot_x;
    int8_t boot_y;
#endif
    mouse_xy_report_t x;
    mouse_xy_report_t y;
    mouse_hv_report_t v;
    mouse_hv_report_t h;
} PACKED report_mouse_t;

typedef struct {
    uint8_t  report_id;
    uint8_t  in_range : 1;
    uint8_t  tip : 1;
    uint8_t  barrel : 1;
    uint8_t  reserved : 5;
    uint16_t x;
    uint16_t y;
} PACKED report_digitizer_stylus_t;

typedef struct {
    uint8_t  confidence : 1;
    uint8_t  tip : 1;
    uint8_t  reserved : 6;
    uint8_t  contact_id : 3;
    uint8_t  reserved2 : 5;
    uint16_t x;
    uint16_t y;
} PACKED digitizer_finger_report_t;

typedef struct {
    uint8_t report_id;
#ifdef DIGITIZER_FINGER_COUNT
    digitizer_finger_report_t fingers[DIGITIZER_FINGER_COUNT];
#endif
    uint16_t scan_time;
    uint8_t  contact_count : 4;
    uint8_t  button1 : 1;
    uint8_t  button2 : 1;
    uint8_t  button3 : 1;
    uint8_t  reserved2 : 1;
} PACKED report_digitizer_t;

#if JOYSTICK_AXIS_RESOLUTION > 8
typedef int16_t joystick_axis_t;
#else
typedef int8_t joystick_axis_t;
#endif

typedef struct {
#ifdef JOYSTICK_SHARED_EP
    uint8_t report_id;
#endif
#if JOYSTICK_AXIS_COUNT > 0
    joystick_axis_t axes[JOYSTICK_AXIS_COUNT];
#endif

#ifdef JOYSTICK_HAS_HAT
    int8_t  hat : 4;
    uint8_t reserved : 4;
#endif

#if JOYSTICK_BUTTON_COUNT > 0
    uint8_t buttons[(JOYSTICK_BUTTON_COUNT - 1) / 8 + 1];
#endif
} PACKED report_joystick_t;

/* keycode to system usage */
static inline uint16_t KEYCODE2SYSTEM(uint8_t key) {
    switch (key) {
        case KC_SYSTEM_POWER:
            return SYSTEM_POWER_DOWN;
        case KC_SYSTEM_SLEEP:
            return SYSTEM_SLEEP;
        case KC_SYSTEM_WAKE:
            return SYSTEM_WAKE_UP;
        default:
            return 0;
    }
}

/* keycode to consumer usage */
static inline uint16_t KEYCODE2CONSUMER(uint8_t key) {
    switch (key) {
        case KC_AUDIO_MUTE:
            return AUDIO_MUTE;
        case KC_AUDIO_VOL_UP:
            return AUDIO_VOL_UP;
        case KC_AUDIO_VOL_DOWN:
            return AUDIO_VOL_DOWN;
        case KC_MEDIA_NEXT_TRACK:
            return TRANSPORT_NEXT_TRACK;
        case KC_MEDIA_PREV_TRACK:
            return TRANSPORT_PREV_TRACK;
        case KC_MEDIA_FAST_FORWARD:
            return TRANSPORT_FAST_FORWARD;
        case KC_MEDIA_REWIND:
            return TRANSPORT_REWIND;
        case KC_MEDIA_STOP:
            return TRANSPORT_STOP;
        case KC_MEDIA_EJECT:
            return TRANSPORT_STOP_EJECT;
        case KC_MEDIA_PLAY_PAUSE:
            return TRANSPORT_PLAY_PAUSE;
        case KC_MEDIA_SELECT:
            return AL_CC_CONFIG;
        case KC_MAIL:
            return AL_EMAIL;
        case KC_CALCULATOR:
            return AL_CALCULATOR;
        case KC_MY_COMPUTER:
            return AL_LOCAL_BROWSER;
        case KC_CONTROL_PANEL:
            return AL_CONTROL_PANEL;
        case KC_ASSISTANT:
            return AL_ASSISTANT;
        case KC_WWW_SEARCH:
            return AC_SEARCH;
        case KC_WWW_HOME:
            return AC_HOME;
        case KC_WWW_BACK:
            return AC_BACK;
        case KC_WWW_FORWARD:
            return AC_FORWARD;
        case KC_WWW_STOP:
            return AC_STOP;
        case KC_WWW_REFRESH:
            return AC_REFRESH;
        case KC_BRIGHTNESS_UP:
            return BRIGHTNESS_UP;
        case KC_BRIGHTNESS_DOWN:
            return BRIGHTNESS_DOWN;
        case KC_WWW_FAVORITES:
            return AC_BOOKMARKS;
        case KC_MISSION_CONTROL:
            return AC_DESKTOP_SHOW_ALL_WINDOWS;
        case KC_LAUNCHPAD:
            return AC_SOFT_KEY_LEFT;
        default:
            return 0;
    }
}

uint8_t has_anykey(void);
uint8_t get_first_key(void);
bool    is_key_pressed(uint8_t key);

void add_key_byte(report_keyboard_t* keyboard_report, uint8_t code);
void del_key_byte(report_keyboard_t* keyboard_report, uint8_t code);
#ifdef NKRO_ENABLE
void add_key_bit(report_nkro_t* nkro_report, uint8_t code);
void del_key_bit(report_nkro_t* nkro_report, uint8_t code);
#endif

void add_key_to_report(uint8_t key);
void del_key_from_report(uint8_t key);
void clear_keys_from_report(void);

#ifdef MOUSE_ENABLE
bool has_mouse_report_changed(report_mouse_t* new_report, report_mouse_t* old_report);
#endif

#ifdef __cplusplus
}
#endif
