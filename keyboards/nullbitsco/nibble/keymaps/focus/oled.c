#include <stdio.h>

#include "quantum.h"

#include "focus_timer.h"
#include "oled.h"


oled_mode_t oled_mode;

void set_oled_mode(oled_mode_t mode) {
    oled_mode = mode;
}

const char *get_u8_str_pad(uint8_t curr_num) {
    static char    buf[3]   = {0};
    return get_numeric_str(buf, sizeof(buf), curr_num, '0');
}

void render_time(void) {
    uint32_t total_seconds = focus_timer / 1000UL;
    uint32_t minutes = total_seconds / 60UL;
    uint32_t seconds = total_seconds - minutes * 60;
    
    switch(focus_state) {
        case WORK:
        oled_write_P(PSTR("TIMER: WORK\n"),false);
        break;
        case REST:
        oled_write_P(PSTR("TIMER: REST\n"),false);
        break;
        default:
        break;
    }
    oled_write_P(PSTR("   "), false);
    oled_write(get_u8_str_pad(minutes),false);
    oled_write_P(PSTR(":"), false);
    oled_write(get_u8_str_pad(seconds),false);
    oled_write_P(PSTR("\n"), false);
    if (focus_paused) {
        oled_write_P(PSTR("  PAUSED\n"),false);
    } else {
        oled_write_P(PSTR("\n"),false);
    }

    if (focus_paused) {
        rgblight_setrgb(255,255,0);
    } else {
        if (focus_state == WORK) {
            if (focus_time >= TWENTY_FIVE_MIN - 10000 && seconds%2==0) {
                rgblight_setrgb(0,0,0);
            } else {
                rgblight_setrgb(255,0,0);
            }
        } else {
            if (focus_time >= FIVE_MIN - 10000 && seconds%2==0) {
                rgblight_setrgb(0,0,0);
            } else {
                rgblight_setrgb(0,255,0);
            }
        }
    }
}

void render_shleep(void) {
    oled_write_P(PSTR("TIMER: OFF\n"),false);
    oled_write_P(PSTR("\n"),false);
    oled_write_P(PSTR("\n"),false);
    // insert sleeping pusheen
    rgblight_setrgb(0,0,0);
}

void render_frame(void) {
    switch (oled_mode) {
        case OLED_MODE_TIMER_ON:
            render_time();
            break;
        default:
            render_shleep();
            break;
    }
}
