# Disable unused features
MAGIC_ENABLE = no
CONSOLE_ENABLE = no
UNICODE_ENABLE = no
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no

# Enable common features
LTO_ENABLE = yes
COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
BOOTMAGIC_ENABLE = yes
SWAP_HANDS_ENABLE = yes

VPATH += $(USER_PATH)/autocorrect $(USER_PATH)/oled $(USER_PATH)/rgb
INTROSPECTION_KEYMAP_C = filterpaper.c
SRC += autocorrect.c

ifneq ($(strip $(CONVERT_TO)),)
    MAKECMDGOALS = uf2-split-$(SPLIT)
    ifeq ($(strip $(CONVERT_TO)), kb2040)
        RGB_MATRIX_ENABLE = yes
        RGB_MATRIX_CUSTOM_USER = yes
        SRC += rgb-matrix.c
    endif
endif

ifeq ($(strip $(KEYBOARD)), crkbd/rev1)
    RGB_MATRIX_ENABLE = yes
    RGB_MATRIX_CUSTOM_USER = yes
    SRC += rgb-matrix.c
    OLED_ENABLE = yes
    ifneq ($(strip $(OLED)),)
        OPT_DEFS += -D$(OLED)
        SRC += oled-icons.c oled-luna.c
    else
        SRC += oled-icons.c oled-bongocat.c
    endif
endif