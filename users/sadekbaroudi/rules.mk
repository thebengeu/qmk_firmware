SRC += sadekbaroudi.c \
       process_records.c

COMMAND_ENABLE   = no  # Commands for debug and configuration
CONSOLE_ENABLE   = yes  # Console for debug
UNICODE_ENABLE   = no  # Unicode
SWAP_HANDS_ENABLE= no  # Allow swapping hands of keyboard
BACKLIGHT_ENABLE = no
NKRO_ENABLE      = no
CASEMODES_ENABLE = yes
COMBO_ENABLE     = yes
LTO_ENABLE       = no

# UNCOMMENT TO DISABLE MACROS
#EXTRAFLAGS     += -flto
# UNCOMMENT TO DISABLE MACROS

SPACE_CADET_ENABLE    = no
GRAVE_ESC_ENABLE      = no

RGB_MATRIX_REACTIVE_LAYERS := no
ifeq ($(strip $(RGB_MATRIX_REACTIVE_LAYERS)), yes)
    OPT_DEFS += -DRGB_MATRIX_REACTIVE_LAYERS
endif

RGBLIGHT_SNAKE_LAYERS := no
ifeq ($(strip $(RGBLIGHT_SNAKE_LAYERS)), yes)
    OPT_DEFS += -DRGBLIGHT_SNAKE_LAYERS
endif

RGBLIGHT_TWINKLE_LAYERS := no
ifeq ($(strip $(RGBLIGHT_TWINKLE_LAYERS)), yes)
    OPT_DEFS += -DRGBLIGHT_TWINKLE_LAYERS
endif

RGB_LED_RING := no
ifeq ($(strip $(RGB_LED_RING)), yes)
    OPT_DEFS += -DRGB_LED_RING
endif

RGB_MATRIX_BAND_VAL_LAYERS := no
ifeq ($(strip $(RGB_MATRIX_BAND_VAL_LAYERS)), yes)
    OPT_DEFS += -DRGB_MATRIX_BAND_VAL_LAYERS
endif

CIRQUE_CURVED_OVERLAY_ENABLE := no
ifeq ($(strip $(CIRQUE_CURVED_OVERLAY_ENABLE)), yes)
    OPT_DEFS += -DCIRQUE_CURVED_OVERLAY_ENABLE
endif

ifeq ($(strip $(CASEMODES_ENABLE)), yes)
    SRC += casemodes.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
    # https://github.com/qmk/qmk_firmware/issues/21137#issuecomment-1577898767 - workaround, but not to be promoted
    # SRC += combos.c # as of QMK 2023-08-27 release, this is no longer the way
    INTROSPECTION_KEYMAP_C = combos.c
endif

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += audio_userspace.c
endif

