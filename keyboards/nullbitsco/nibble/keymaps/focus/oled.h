#pragma once

#include <stdint.h>

typedef enum {
    OLED_MODE_TIMER_OFF = 0,
    OLED_MODE_TIMER_ON,
} oled_mode_t;

extern oled_mode_t oled_mode;

void set_oled_mode(oled_mode_t mode);

void render_frame(void);
