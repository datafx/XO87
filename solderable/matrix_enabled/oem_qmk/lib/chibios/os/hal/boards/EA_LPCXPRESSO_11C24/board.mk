# List of all the board related files.
BOARDSRC = ${CHIBIOS}/os/hal/boards/EA_LPCXPRESSO_11C24/board.c

# Required include directories
BOARDINC = ${CHIBIOS}/os/hal/boards/EA_LPCXPRESSO_11C24

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
