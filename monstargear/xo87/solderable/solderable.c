
#include "solderable.h"
#include "quantum.h"

#define noLed {255,255}

#define ledSollSP (80+3)
#define ledNumSP (80+7)
#define ledCapSP (80+8)

u8 led_backLight_val;

extern backlight_config_t backlight_config;
led_t led_s;

u8 rgbSp,r,g,b;

typedef struct
{
u8 step;
u8 brightnessStep;
u8 pressIndex;
u8 KeyLedBrightness[KEYLED_ROWS*KEYLED_COLS];
u8 ledonSp;
u8 delayRhythmOut;
}

keyLedDrive_;

keyLedDrive_ keyLedDrive;

RhythmLed_ RhythmLed;
backLedRgbG_ backLedRgbG;
u16 RhythmLed_timeOutR0;

static pin_t key_led_row_pins[KEYLED_ROWS] = KEYLED_ROW_PINS;
static pin_t key_led_col_pins[KEYLED_COLS] = KEYLED_COL_PINS;

void ledSollSet(bool onf)
{
    if(onf)
    {
        keyLedDrive.KeyLedBrightness[ledSollSP]=brightnessMax;
    }
    else
    {
     keyLedDrive.KeyLedBrightness[ledSollSP]=0;
    }
}

void ledNumSet(bool onf)
{
     if(onf)
    {
        keyLedDrive.KeyLedBrightness[ledNumSP]=brightnessMax;
    }
    else
    {
     keyLedDrive.KeyLedBrightness[ledNumSP]=0;
    }
}

void ledCapsSet(bool onf)
{
    if(onf)
    {
        keyLedDrive.KeyLedBrightness[ledCapSP]=brightnessMax;
    }
    else
    {
     keyLedDrive.KeyLedBrightness[ledCapSP]=0;
    }
}

extern rgblight_config_t rgblight_config;

void updateBackLight(void)
{
u8 i;
u8 level=backlight_config.level;
    reflashLedState();
    if(level>brightnessMax)
        level=brightnessMax;
    if(level!=led_backLight_val)
    {
        for(i=0;i<(KEYLED_ROWS*KEYLED_COLS);i++)
        {
            if((i==ledNumSP)||(i==ledCapSP)||(i==ledSollSP))
            {
            }
            else
                keyLedDrive.KeyLedBrightness[i]=level;
        }
    }
    led_backLight_val=level;
}

extern uint8_t getLightLevel(void)
{
    return backlight_config.level;
}

void updateRgbBackLight(void)
{
    u8 i=0;
    if(rgblight_get_mode()!=1)
    {
        rgblight_mode(1);
    }
    for(i=0;i<colorAGSize;i++)
    {
        rgblight_setrgb_at(backLedRgbG.colorAG[i].r,backLedRgbG.colorAG[i].g,backLedRgbG.colorAG[i].b,i);
    }
    for(i=0;i<(colorBGSize);i++)
    {
        rgblight_setrgb_at(backLedRgbG.colorBG[i].r,backLedRgbG.colorBG[i].g,backLedRgbG.colorBG[i].b,i+colorAGSize);
    }
   rgblight_set();
}

// cannot use raw_hid_receive with VIA enabled
//void raw_hid_receive(uint8_t *data, uint8_t length) {

//}


void matrix_init_kb(void) {
    u8 i;
	debug_enable = true;
    rgbSp=0;

    for(i=0;i<KEYLED_ROWS;i++)
    {
        setPinOutput(key_led_row_pins[i]);
        writePinLow(key_led_row_pins[i]);
    }
    for(i=0;i<KEYLED_COLS;i++)
    {
        setPinOutput(key_led_col_pins[i]);
        writePinLow(key_led_col_pins[i]);
    }
    for(i=0;i<(KEYLED_ROWS*KEYLED_COLS);i++)
    {
        keyLedDrive.KeyLedBrightness[i]=1;
    }
  setPinInput(E6);
  matrix_init_user();
}

void setKeyLedBrightness(u8 x,u8 y,u8 Brightness)
{
    u8 i;
    i=0;
    keyLedDrive.KeyLedBrightness[i]=Brightness;
}
void KeyLedCom(void)
{
    writePinLow(key_led_row_pins[keyLedDrive.step]);
}

void LampEffectFadeAway2Zero(u8 deci)
{
u8 i;
    for(i=0;i<(KEYLED_ROWS*KEYLED_COLS);i++)
    {
        if(keyLedDrive.KeyLedBrightness[i]>0)
        {
            keyLedDrive.KeyLedBrightness[i]--;
        }
    }
}

void reflashLedState(void)
{
    ledCapsSet(led_s.caps_lock);
    ledNumSet(led_s.num_lock);
    ledSollSet(led_s.scroll_lock);
}
bool led_update_user(led_t led_state) {
    led_s=led_state;
  return true;
}
u8 deltr0;
void keyLedDriver(void)
{
u8 i;
u8 sp;
u16 li;
u8 stepT;
     cli();
    for(i=0;i<KEYLED_COLS;i++)
    {
        sp=keyLedDrive.step*KEYLED_COLS+i;
        if(keyLedDrive.KeyLedBrightness[sp]>keyLedDrive.brightnessStep)
            writePinHigh(key_led_col_pins[i]);
        else
        {
           writePinLow(key_led_col_pins[i]);
        }
    }
    for(li=0;li<10;li++)
        writePinHigh(key_led_row_pins[keyLedDrive.step]);
    updateBackLight();
    stepT=keyLedDrive.step;
    keyLedDrive.step++;
    if(keyLedDrive.step>=KEYLED_ROWS)
    {
        keyLedDrive.step=0;
        keyLedDrive.brightnessStep++;
        if(keyLedDrive.brightnessStep>=brightnessMax)
        {
            keyLedDrive.brightnessStep=0;
        }
    }
    writePinLow(key_led_row_pins[stepT]);
    sei();
}

void matrix_scan_user(void) {
}
void matrix_scan_kb(void) {
   matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}
