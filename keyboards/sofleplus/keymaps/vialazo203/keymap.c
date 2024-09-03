 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 

#include QMK_KEYBOARD_H



#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_user(uint8_t index, bool active) { 
    switch (index) {
        case 0:
            if(active) { //If switch is pressed
                register_code(KC_BTN1); 
            } else { //If switch is not pressed
                unregister_code(KC_BTN1);
            }
            break;
        case 1:
            if(active) {
                register_code(KC_DOWN); //not working
            } else {
                unregister_code(KC_DOWN);
            }
            break;
        case 2:
            if(active) {
                register_code(KC_RGHT);
            } else {
                unregister_code(KC_RGHT);
            }
            break;
        case 3:
            if(active) {
                register_code(KC_UP); //not working
            } else {
                unregister_code(KC_UP);
            }
            break;
        case 4:
            if(active) {
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
            }
            break;
    }
    return true;
}
#endif




/* Haptic Bzzz */
#ifdef HAPTIC_ENABLE
	#include "drivers/haptic/DRV2605L.h"
	
	bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
		case LCTL_T(KC_TAB):
            if (record->event.pressed) {
					drv2605l_pulse(69);		//transition_hum_10
                }
            break;
    }
    return false;
}	
	
#endif

#ifdef SUPER_ALT_TAB_ENABLE
	bool is_alt_tab_active = false; // Super Alt Tab Code
	uint16_t alt_tab_timer = 0;
#endif

void matrix_scan_user(void) {

	//sentence_case_task();
	#ifdef SUPER_ALT_TAB_ENABLE
		if (is_alt_tab_active) {	//Allows for use of super alt tab.
			if (timer_elapsed(alt_tab_timer) > 1000) {
				unregister_code(KC_LALT);
				is_alt_tab_active = false;
			}
		}
	#endif

}

// Variables for custom keycodes

#ifdef VIA_ENABLE
	enum custom_keycodes { // Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
    CK_ATABF = QK_KB_0,
    CK_ATABR,
	CK_ATMWU,	//Alt mouse wheel up 
	CK_ATMWD,	//Alt mouse wheel down
    CK_PO,		//Power options
	SCROLL_DIR_V, //滾輪上下
	//SCROLL_DIR_H, //滾輪左右
    CURSOR_SPEED_UP, // Increase cursor speed
    CURSOR_SPEED_DN, // Increase cursor speed
    CURSOR_SPEED_RESET, // Reset cursor speed to default
	};
#else
	enum custom_keycodes { // Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	CK_ATABF = SAFE_RANGE,
	CK_ATABR,
	CK_ATMWU,	//Alt mouse wheel up 
	CK_ATMWD,	//Alt mouse wheel down
    CK_PO,
	SCROLL_DIR_V,
	//SCROLL_DIR_H,
    CURSOR_SPEED_UP, // Increase cursor speed
    CURSOR_SPEED_DN, // Increase cursor speed
    CURSOR_SPEED_RESET, // Reset cursor speed to default
	};
#endif


//trackball led and haptic not working for layer indicator, thanks Drashna for pointing out
void housekeeping_task_user(void) {
    static layer_state_t state = 0;
    if (layer_state != state) {
        state = layer_state_set_user(layer_state);
    }
}

//RGB matrix layer indicator, using HSV allows the brightness to be limited

/*
Host LED status (capslock) and layer from 1 to 8 only. layer 0 and layer 9 for preset rgb effect
the indicator for rgb underglow only 
*/

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i <= 6; i++) {
            rgb_matrix_set_color(i, 128, 0, 0); // Set color to dim red for Caps Lock
        }
        for (uint8_t i = 36; i <= 42; i++) {
            rgb_matrix_set_color(i, 128, 0, 0); // Set color to dim red for Caps Lock
        }
    }

    switch (get_highest_layer(layer_state)) {
        case 1:
            for (uint8_t i = 0; i <= 6; i++) {
                rgb_matrix_set_color(i, 128, 0, 128); // Dim purple for Layer 1
            }
            for (uint8_t i = 36; i <= 42; i++) {
                rgb_matrix_set_color(i, 128, 0, 128); // Dim purple for Layer 1
            }
            break;
        case 2:
            for (uint8_t i = 0; i <= 6; i++) {
                rgb_matrix_set_color(i, 255, 128, 0); // Dim orange for Layer 2
            }
            for (uint8_t i = 36; i <= 42; i++) {
                rgb_matrix_set_color(i, 255, 128, 0); // Dim orange for Layer 2
            }
            break;
        case 3:
            for (uint8_t i = 0; i <= 6; i++) {
                rgb_matrix_set_color(i, 0, 128, 128); // Dim cyan for Layer 3
            }
            for (uint8_t i = 36; i <= 42; i++) {
                rgb_matrix_set_color(i, 0, 128, 128); // Dim cyan for Layer 3
            }
            break;
        case 4:
            for (uint8_t i = 0; i <= 6; i++) {
                rgb_matrix_set_color(i, 0, 255, 127); // Dim spring green for Layer 4
            }
            for (uint8_t i = 36; i <= 42; i++) {
                rgb_matrix_set_color(i, 0, 255, 127); // Dim spring green for Layer 4
            }
            break;
        case 5:
            for (uint8_t i = 0; i <= 6; i++) {
                rgb_matrix_set_color(i, 0, 0, 128); // Dim blue for Layer 5
            }
            for (uint8_t i = 36; i <= 42; i++) {
                rgb_matrix_set_color(i, 0, 0, 128); // Dim blue for Layer 5
            }
            break;
        case 6:
            for (uint8_t i = 0; i <= 6; i++) {
                rgb_matrix_set_color(i, 128, 0, 128); // Dim magenta for Layer 6
            }
            for (uint8_t i = 36; i <= 42; i++) {
                rgb_matrix_set_color(i, 128, 0, 128); // Dim magenta for Layer 6
            }
            break;
        case 7:
            for (uint8_t i = 0; i <= 6; i++) {
                rgb_matrix_set_color(i, 255, 192, 203); // Dim pink for Layer 7
            }
            for (uint8_t i = 36; i <= 42; i++) {
                rgb_matrix_set_color(i, 255, 192, 203); // Dim pink for Layer 7
            }
            break;
        case 8:
            for (uint8_t i = 0; i <= 6; i++) {
                rgb_matrix_set_color(i, 255, 215, 0); // Dim gold for Layer 8
            }
            for (uint8_t i = 36; i <= 42; i++) {
                rgb_matrix_set_color(i, 255, 215, 0); // Dim gold for Layer 8
            }
            break;
        default:
            break;
    }

    return false; // Allow RGB matrix to handle colors when no indicators are active
}



/* AZOTEQ cofig to tame the scroll*/  //Dasky https://discord.com/channels/440868230475677696/867530303261114398/1169658779864940554
/* 20240609 - change from 6 to 8, make scrolling even slower */



#define DEFAULT_CURSOR_SPEED 1
static int16_t cursor_speed = DEFAULT_CURSOR_SPEED; // Default cursor speed
static bool scroll_dir_v = false; // Vertical scroll direction
static bool scroll_dir_h = false; // Horizontal scroll direction

void keyboard_post_init_user(void) {
    uint32_t eeprom_data = eeconfig_read_user();
    cursor_speed = eeprom_data & 0xFFFF;
    scroll_dir_v = (eeprom_data >> 16) & 1;
    scroll_dir_h = (eeprom_data >> 17) & 1;
}


#define SCROLL_AVERAGE 8
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    static int16_t h       = 0;
    static uint8_t h_count = 0;
    static int16_t v       = 0;
    static uint8_t v_count = 0;

    if (mouse_report.h != 0) {
        h_count++;
        h += scroll_dir_h ? -mouse_report.h : mouse_report.h; // Change direction based on scroll_dir_h
        mouse_report.h = 0;
        if (h_count == SCROLL_AVERAGE) {
            h_count = 0;
            if (h < 0) {
                mouse_report.h = -1;
            } else {
                mouse_report.h = 1;
            }
            h = 0;
        }
    } else {
        if (h_count) {
            if (h < 0) {
                mouse_report.h = -1;
            } else {
                mouse_report.h = 1;
            }
        }
        h_count = 0;
        h       = 0;
    }

    if (mouse_report.v != 0) {
        v_count++;
        v += scroll_dir_v ? -mouse_report.v : mouse_report.v; // Change direction based on scroll_dir_v
        mouse_report.v = 0;
        if (v_count == SCROLL_AVERAGE) {
            v_count = 0;
            if (v < 0) {
                mouse_report.v = -1;
            } else {
                mouse_report.v = 1;
            }
            v = 0;
        }
    } else {
        if (v_count) {
            if (v < 0) {
                mouse_report.v = -1;
            } else {
                mouse_report.v = 1;
            }
        }
        v_count = 0;
        v       = 0;
    }

    // Modify mouse_report.x and mouse_report.y based on cursor_speed
    mouse_report.x *= cursor_speed;
    mouse_report.y *= cursor_speed;

    return mouse_report;
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {


	switch (keycode) {
		#ifdef SUPER_ALT_TAB_ENABLE
		    case CK_ATABF:
		    	if (record->event.pressed) {
		    		if (!is_alt_tab_active) {
		    			is_alt_tab_active = true;
		    			register_code(KC_LALT);
		    		}
		    			alt_tab_timer = timer_read();
		    			register_code(KC_TAB);
		    		} else {
		    			unregister_code(KC_TAB);
		    		}
                break;

		    case CK_ATABR:
		    	if (record->event.pressed) {
		    		if (!is_alt_tab_active) {
		    			is_alt_tab_active = true;
		    			register_code(KC_LALT);
		    		}
		    			alt_tab_timer = timer_read();
		    			register_code(KC_LSFT);
		    			register_code(KC_TAB);
		    		} else {
		    			unregister_code(KC_LSFT);
		    			unregister_code(KC_TAB);
		    		}
                break;
				
		case CK_ATMWU:	//Alt mouse wheel up 
			if (record->event.pressed) {
				if (!is_alt_tab_active) {
					is_alt_tab_active = true;
					register_code(KC_LALT);
				}
					alt_tab_timer = timer_read();
					register_code(KC_MS_WH_UP);
				} else {
					unregister_code(KC_MS_WH_UP);
				}
			break;
			
		case CK_ATMWD:	//Alt mouse wheel down 
			if (record->event.pressed) {
				if (!is_alt_tab_active) {
					is_alt_tab_active = true;
					register_code(KC_LALT);
				}
					alt_tab_timer = timer_read();
					register_code(KC_MS_WH_DOWN);
				} else {
					unregister_code(KC_MS_WH_DOWN);
				}
			break;
		#endif

        case CK_PO:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_D);
                unregister_code(KC_D);
                unregister_code(KC_LGUI);
                
                wait_ms(500);

                register_code(KC_LALT);
                register_code(KC_F4);
                unregister_code(KC_F4);
                unregister_code(KC_LALT);
            }
            break;

		
		case SCROLL_DIR_V:
            if (record->event.pressed) {
                scroll_dir_v = !scroll_dir_v;
                eeconfig_update_user((cursor_speed & 0xFFFF) | (scroll_dir_v << 16) | (scroll_dir_h << 17));
            }
			break;
		/*
        case SCROLL_DIR_H:
            if (record->event.pressed) {
                scroll_dir_h = !scroll_dir_h;
                eeconfig_update_user((cursor_speed & 0xFFFF) | (scroll_dir_v << 16) | (scroll_dir_h << 17));
            }
            return false;		
		*/
		case CURSOR_SPEED_UP:
			if (record->event.pressed) {
				if (cursor_speed < 9) {
					cursor_speed++; // Increment if below 9
				}
				eeconfig_update_user((cursor_speed & 0xFFFF) | (scroll_dir_v << 16) | (scroll_dir_h << 17));
			}
			break;

		case CURSOR_SPEED_DN:
			if (record->event.pressed) {
				if (cursor_speed > 1) {
					cursor_speed--; // Decrement if above 1
				}
				eeconfig_update_user((cursor_speed & 0xFFFF) | (scroll_dir_v << 16) | (scroll_dir_h << 17));
			}
			break;

		case CURSOR_SPEED_RESET:
			if (record->event.pressed) {
				cursor_speed = DEFAULT_CURSOR_SPEED;
				eeconfig_update_user((cursor_speed & 0xFFFF) | (scroll_dir_v << 16) | (scroll_dir_h << 17));
			}
			break;


    }
	    return true;  // Add this line
}

/* OLED customisation */
#ifdef OLED_ENABLE
	#include "oled.c" //Stock OLED code

    void suspend_power_down_user(void) {
        oled_off();
		
    }

#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  CURSOR_SPEED_RESET,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    RGB_TOG,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                 KC_LGUI,KC_LALT,KC_LCTL, MO(2), KC_ENT,      KC_SPC,  MO(3), KC_RCTL, KC_RALT, KC_RGUI
),

[1] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______

),
[2] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
),
[3] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
),
[4] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
),
[5] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
),
[6] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
),
[7] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
),
[8] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
),
[9] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
)
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [0] = { ENCODER_CCW_CW(CK_ATABF, CK_ATABR), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(C(KC_MINS), C(KC_EQL)) },
        [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_F3, C(KC_F3)) },
        [3] = { ENCODER_CCW_CW(G(KC_LEFT), G(KC_RGHT)), ENCODER_CCW_CW(A(KC_RGHT), A(KC_LEFT)) },
        [4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [5] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [6] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [7] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [8] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
        [9] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
    };
#endif
