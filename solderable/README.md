# XO87 Solderable Beta

Until the LED matrix can be figured out, there are three options for the firmware for this board.
  * underglow_only (underglow enabled, but no backlighting - caps/scroll/num lock work as expected)
  * backlight_only (underglow and backlight enabled and bright, but caps/scroll/num lock are always on and adjust with the rest of the backlight leds)
  * matrix_enabled (a hacky version of a fully working firmware but LEDs are a bit dim due to pwm)
 

***WARNING***

These firmwares are beta builds and may contain bugs or cause issues with your keyboard.  Use these builds at your own risk

The "matrix_enabed" directory contains an old version of the OEM firmware that has uses a modified version of QMK, but has been changed to allow VIA to work.  The original software will no longer work.  The backighting and indicator LEDs are working, but may appear dim.

The "underglow_only" directory contains a custom firmware that was built with an unmodified version of QMK and supports VIA.  The underglow and indicator LEDs work and are at full brightness, but the individual key backlighting is disabled.
