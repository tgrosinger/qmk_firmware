#----------------------------------------------------------------------------
# make gboards/gergoplex:default:flash
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------

#Debug options
VERBOSE                = no
DEBUG_MATRIX_SCAN_RATE = no
DEBUG_MATRIX           = no
CONSOLE_ENABLE         = no

#Combos!
VPATH                  +=  keyboards/gboards/

TAP_DANCE_ENABLE       = yes

ifeq ($(strip $(DEBUG_MATRIX)), yes)
    OPT_DEFS += -DDEBUG_MATRIX
endif
