/* Copyright 2019
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
#include "process_rgb.h"
#include "rgb.h"

extern backlight_config_t backlight_config;
typedef void (*rgb_func_pointer)(void);

/**
 * Wrapper for inc/dec rgb keycode
 *
 * noinline to optimise for firmware size not speed (not in hot path)
 */
static void __attribute__((noinline)) handleKeycodeRGB(const uint8_t is_shifted, const rgb_func_pointer inc_func, const rgb_func_pointer dec_func) {
    if (is_shifted) {
        dec_func();
    } else {
        inc_func();
    }
}

/**
 * Wrapper for animation mode
 *   - if not in animation family -> jump to that animation
 *   - otherwise -> wrap round animation speed
 *
 * noinline to optimise for firmware size not speed (not in hot path)
 */
static void __attribute__((noinline, unused)) handleKeycodeRGBMode(const uint8_t start, const uint8_t end) {
    if ((start <= rgblight_get_mode()) && (rgblight_get_mode() < end)) {
        rgblight_step();
    } else {
        rgblight_mode(start);
    }
}

/**
 * Handle keycodes for both rgblight and rgbmatrix
 */
bool process_rgb(const uint16_t keycode, const keyrecord_t *record) {
#ifndef SPLIT_KEYBOARD
    if (record->event.pressed) {
#else
    // Split keyboards need to trigger on key-up for edge-case issue
    if (!record->event.pressed) {
#endif
        uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
        switch (keycode) {
            case RGB_TOG:
                rgblight_toggle();
                return false;
            case RGB_MODE_FORWARD:
                handleKeycodeRGB(shifted, rgblight_step, rgblight_step_reverse);
                return false;
            case RGB_MODE_REVERSE:
                handleKeycodeRGB(shifted, rgblight_step_reverse, rgblight_step);
                return false;
            case RGB_HUI:
                handleKeycodeRGB(shifted, rgblight_increase_hue, rgblight_decrease_hue);
                return false;
            case RGB_HUD:
                handleKeycodeRGB(shifted, rgblight_decrease_hue, rgblight_increase_hue);
                return false;
            case RGB_SAI:
                handleKeycodeRGB(shifted, rgblight_increase_sat, rgblight_decrease_sat);
                return false;
            case RGB_SAD:
                handleKeycodeRGB(shifted, rgblight_decrease_sat, rgblight_increase_sat);
                return false;
            case RGB_VAI:
                handleKeycodeRGB(shifted, rgblight_increase_val, rgblight_decrease_val);
                return false;
            case RGB_VAD:
                handleKeycodeRGB(shifted, rgblight_decrease_val, rgblight_increase_val);
                return false;
            case RGB_SPI:
                handleKeycodeRGB(shifted, rgblight_increase_speed, rgblight_decrease_speed);
                return false;
            case RGB_SPD:
                handleKeycodeRGB(shifted, rgblight_decrease_speed, rgblight_increase_speed);
                return false;
            case RGB_MODE_PLAIN:
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                updateRgbBackLight();
                return false;
            case RGB_MODE_BREATHE:
#ifdef RGBLIGHT_EFFECT_BREATHING
                handleKeycodeRGBMode(RGBLIGHT_MODE_BREATHING, RGBLIGHT_MODE_BREATHING_end);
#endif
                return false;
            case RGB_MODE_RAINBOW:
#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
                handleKeycodeRGBMode(RGBLIGHT_MODE_RAINBOW_MOOD, RGBLIGHT_MODE_RAINBOW_MOOD_end);
#endif
                return false;
            case RGB_MODE_SWIRL:
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
                handleKeycodeRGBMode(RGBLIGHT_MODE_RAINBOW_SWIRL, RGBLIGHT_MODE_RAINBOW_SWIRL_end);
#endif
                return false;
            case RGB_MODE_SNAKE:
#ifdef RGBLIGHT_EFFECT_SNAKE
                handleKeycodeRGBMode(RGBLIGHT_MODE_SNAKE, RGBLIGHT_MODE_SNAKE_end);
#endif
                return false;
            case RGB_MODE_KNIGHT:
#ifdef RGBLIGHT_EFFECT_KNIGHT
                handleKeycodeRGBMode(RGBLIGHT_MODE_KNIGHT, RGBLIGHT_MODE_KNIGHT_end);
#endif
                return false;
            case RGB_MODE_XMAS:
#ifdef RGBLIGHT_EFFECT_CHRISTMAS
                rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
#endif
                return false;
            case RGB_MODE_GRADIENT:
#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
                handleKeycodeRGBMode(RGBLIGHT_MODE_STATIC_GRADIENT, RGBLIGHT_MODE_STATIC_GRADIENT_end);
#endif
                return false;
            case RGB_MODE_RGBTEST:
#ifdef RGBLIGHT_EFFECT_RGB_TEST
                rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
#endif
                return false;
        }
    }

    return true;
}


extern rgblight_config_t rgblight_config;

#define RGB_TOG1 1
#define RGB_MODE_FORWARD1 2
#define RGB_HUI1 3
#define RGB_SAI1 4
#define RGB_VAI1 5
#define RGB_MODE_PLAIN1 6//静态
#define RGB_MODE_BREATHE1 7//呼吸
#define RGB_MODE_RAINBOW1 8
#define RGB_MODE_SWIRL1 9
#define RGB_MODE_SNAKE1 10
#define RGB_MODE_KNIGHT1 11
#define RGB_MODE_XMAS1 12
#define RGB_MODE_GRADIENT1 13
#define RGB_MODE_RGBTEST1 14
extern bool pcSetting(uint8_t item,uint8_t value)
{
     uint8_t shifted =0;// get_mods() & MOD_MASK_SHIFT;
     bool write_to_eeprom=true;
     uint8_t i;
     uint8_t sat;
     uint8_t val;
     uint8_t hue;

        switch (item) {
            case RGB_TOG1://打开或关闭RGB照明                                      |
                //rgblight_toggle();
                if (value) {
                    rgblight_enable();

                } else {
                    rgblight_disable();
                }

                return false;
            case RGB_MODE_FORWARD1://循环切换模式 前 `RGB_MOD`
               // handleKeycodeRGB(shifted, rgblight_step, rgblight_step_reverse);
                // rgblight_config.mode=value;
                // if (rgblight_config.mode < 1) {
                //     rgblight_config.mode = RGBLIGHT_MODES;
                // }
                // rgblight_mode_eeprom_helper(rgblight_config.mode, write_to_eeprom);
                if (value > 10) value=10;
                rgblight_config.speed=value;
                eeconfig_update_rgblight(rgblight_config.raw);  // EECONFIG needs to be increased to support this
                return false;
            case RGB_MODE_REVERSE://循环切换模式 后 `RGB_RMOD`
                //handleKeycodeRGB(shifted, rgblight_step_reverse, rgblight_step);
                return false;
            case RGB_HUI1://加色调
            //uint8_t hue = rgblight_config.hue + RGBLIGHT_HUE_STEP;
                //handleKeycodeRGB(shifted, rgblight_increase_hue, rgblight_decrease_hue);
                hue=value;
                hue/=RGBLIGHT_HUE_STEP;//较正为RGBLIGHT_HUE_STEP的倍数
                hue*=RGBLIGHT_HUE_STEP;
                rgblight_config.hue =hue;
                rgblight_sethsv_eeprom_helper(hue, rgblight_config.sat, rgblight_config.val, write_to_eeprom);

                return false;
            case RGB_HUD://降低色调
           // uint8_t hue = rgblight_config.hue - RGBLIGHT_HUE_STEP;
               // handleKeycodeRGB(shifted, rgblight_decrease_hue, rgblight_increase_hue);
                return false;
            case RGB_SAI1://饱和+
               // handleKeycodeRGB(shifted, rgblight_increase_sat, rgblight_decrease_sat);

                sat =value;// qsub8(rgblight_config.sat, RGBLIGHT_SAT_STEP);
                rgblight_sethsv_eeprom_helper(rgblight_config.hue, sat, rgblight_config.val, write_to_eeprom);

                return false;
            case RGB_SAD://饱和-
                //handleKeycodeRGB(shifted, rgblight_decrease_sat, rgblight_increase_sat);
                //return false;
            case RGB_VAI1://亮度+
                //handleKeycodeRGB(shifted, rgblight_increase_val, rgblight_decrease_val);
                //val = value;//qsub8(rgblight_config.val, RGBLIGHT_VAL_STEP);
                //rgblight_sethsv_eeprom_helper(rgblight_config.hue, rgblight_config.sat, val, write_to_eeprom);
                if(value>brightnessMax)
                    value=brightnessMax;
                backlight_config.level=value;
                if (backlight_config.level > 0) {
                       // backlight_config.level--;
                        backlight_config.enable = !!backlight_config.level;
                        eeconfig_update_backlight(backlight_config.raw);
                    }
                    dprintf("backlight decrease: %u\n", backlight_config.level);
                    backlight_set(backlight_config.level);

                return false;
            case RGB_VAD://亮度-
                //handleKeycodeRGB(shifted, rgblight_decrease_val, rgblight_increase_val);
                return false;
            case RGB_SPI:
                //handleKeycodeRGB(shifted, rgblight_increase_speed, rgblight_decrease_speed);
                return false;
            case RGB_SPD:
               // handleKeycodeRGB(shifted, rgblight_decrease_speed, rgblight_increase_speed);
                return false;
            case RGB_MODE_PLAIN1://静态（无动画）模 `RGB_M_P `
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                updateRgbBackLight();
                return false;
            case RGB_MODE_BREATHE1:// 呼吸动画模 `RGB_M_B`
#ifdef RGBLIGHT_EFFECT_BREATHING
                handleKeycodeRGBMode(RGBLIGHT_MODE_BREATHING, RGBLIGHT_MODE_BREATHING_end);
#endif
                return false;
            case RGB_MODE_RAINBOW1://彩虹动画模 `RGB_M_R`
#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
                handleKeycodeRGBMode(RGBLIGHT_MODE_RAINBOW_MOOD, RGBLIGHT_MODE_RAINBOW_MOOD_end);
#endif
                return false;
            case RGB_MODE_SWIRL1:// 漩涡动画模 `RGB_M_SW`
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
                handleKeycodeRGBMode(RGBLIGHT_MODE_RAINBOW_SWIRL, RGBLIGHT_MODE_RAINBOW_SWIRL_end);
#endif
                return false;
            case RGB_MODE_SNAKE1://蛇动画模 `RGB_M_SN`
#ifdef RGBLIGHT_EFFECT_SNAKE
                handleKeycodeRGBMode(RGBLIGHT_MODE_SNAKE, RGBLIGHT_MODE_SNAKE_end);
#endif
                return false;
            case RGB_MODE_KNIGHT1:// “骑士骑士”动画 `RGB_M_K`
#ifdef RGBLIGHT_EFFECT_KNIGHT
                handleKeycodeRGBMode(RGBLIGHT_MODE_KNIGHT, RGBLIGHT_MODE_KNIGHT_end);
#endif
                return false;
            case RGB_MODE_XMAS1://圣诞动画 `RGB_M_X`
#ifdef RGBLIGHT_EFFECT_CHRISTMAS
                rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
#endif
                return false;
            case RGB_MODE_GRADIENT1://静态渐变动画 `RGB_M_G`
#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
                handleKeycodeRGBMode(RGBLIGHT_MODE_STATIC_GRADIENT, RGBLIGHT_MODE_STATIC_GRADIENT_end);
#endif
                return false;
            case RGB_MODE_RGBTEST1://红、绿、蓝测试动画 `RGB_M_T`
#ifdef RGBLIGHT_EFFECT_RGB_TEST
                rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
#endif
                return false;
        }
}
