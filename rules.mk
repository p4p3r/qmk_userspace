# Disable unused features
MAGIC_ENABLE = no
CONSOLE_ENABLE = no
UNICODE_ENABLE = no
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no
SWAP_HANDS_ENABLE = no
BOOTMAGIC_ENABLE = no

# Enable common features
LTO_ENABLE = yes
COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = no

VPATH += $(USER_PATH)/oled $(USER_PATH)/rgb
INTROSPECTION_KEYMAP_C = p4p3r.c

# Autocorrect
ifeq ($(strip $(AC_ENABLE)), yes)
  OPT_DEFS += -DAC_ENABLE
  VPATH += $(USER_PATH)/autocorrect
  SRC += autocorrect.c
endif

ifeq ($(strip $(MCU)), atmega32u4)
    BOOTLOADER = atmel-dfu
endif

# NanoBoot boards
ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), crkbd/rev1 splitkb/aurora/sweep/rev1 splitkb/kyria/rev1))
	BOOTLOADER = qmk-hid
	BOOTLOADER_SIZE = 512
endif

ifneq ($(strip $(CONVERT_TO)),)
    MAKECMDGOALS = uf2-split-$(SPLIT)
    ifeq ($(strip $(CONVERT_TO)), kb2040)
        RGB_MATRIX_ENABLE = yes
        RGB_MATRIX_CUSTOM_USER = yes
        SRC += rgb-matrix.c
    endif
endif

# OLED
ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), crkbd/rev1 splitkb/aurora/sweep/rev1 splitkb/kyria/rev1))
    OLED_ENABLE = yes
    ifneq ($(strip $(OLED)),)
        OPT_DEFS += -D$(OLED)
        SRC += oled-icons.c oled-luna.c
    else
        SRC += oled-icons.c oled-bongocat.c
    endif
endif

# RGB Matrix
ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), crkbd/rev1 splitkb/aurora/sweep/rev1))
	RGB_MATRIX_ENABLE = yes
	RGB_MATRIX_CUSTOM_USER = no
	SRC += rgb-matrix.c
endif

# Kyria
ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), splitkb/kyria/rev1))
	WPM_ENABLE=yes
    RGB_MATRIX_ENABLE = no
	RGBLIGHT_ENABLE = yes
endif

