
#pragma once

#include "config_common.h"
#define brightnessMax 8

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4D47 // MG for Monstargear
#define PRODUCT_ID      0x5344 // SD for Soldered
#define DEVICE_VER      0x0001
#define MANUFACTURER    Monstargear
#define PRODUCT         XO87 Soldered

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define BACKLIGHT_PIN F5
#define MATRIX_ROW_PINS { E6,E7, E3, B0, B1 ,A2}
#define MATRIX_COL_PINS { C5,C3,C1,E1,D6,D2,B7,B3,F6,F7,F3,A5,A1,E2,C7,A6 }
#define UNUSED_PINS
#define DIODE_DIRECTION ROW2COL
#define RGB_DI_PIN D7
#define DRIVER_LED_TOTAL 21
#define DRIVER_COUNT 2
#define RGBLED_NUM 21
#define RGBLIGHT_ANIMATIONS

#define DEBOUNCE 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
