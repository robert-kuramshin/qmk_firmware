#include <stdbool.h>

#include "timer.h"
#include "focus_timer.h"
#include "oled.h"

const uint32_t FIVE_MIN = (uint32_t)5*60*1000;
const uint32_t TWENTY_FIVE_MIN = (uint32_t)25*60*1000;


state_t focus_state = WORK;
uint32_t focus_timer = 0;
bool focus_paused = false;

static bool enabled = false;
static bool last_focus_paused = false;
static uint32_t paused_time = 0;
static uint32_t pstart;

void reset_timer(void) {
    timer_clear();
    pstart = 0;
    paused_time=0;
    focus_timer=0;
}
void increment_state(void){
    reset_timer();
    focus_state = (focus_state + 1) % NUM_STATES; 
}

void check_state(void) {
    switch(focus_state) {
        case WORK:
        if (focus_timer >= TWENTY_FIVE_MIN) {
            increment_state();
        }
        break;
        case REST:
        if (focus_timer >= FIVE_MIN) {
            increment_state();
        }
        break;
        default:
        break;
    }
}

void update_time() {
    // Paused transition
    if (focus_paused && !last_focus_paused) {
        pstart = timer_read32();
    }

    // Unpaused transition
    if (!focus_paused && last_focus_paused) {
        paused_time += timer_read32() - pstart;
    }

    // If not paused -> update time
    if (!focus_paused) {
        focus_timer = timer_read32();
        focus_timer -= paused_time;
    }
    last_focus_paused = focus_paused;

    check_state();
}

void handle_timer_onoff() {
    enabled = !enabled;
    set_oled_mode(enabled ? OLED_MODE_TIMER_ON: OLED_MODE_TIMER_OFF);
    if (enabled) {
        reset_timer();
        focus_paused=false;
    }
}

void handle_timer_skip() {
    focus_paused = false;
    if (enabled){
        increment_state();
    }
}

void handle_timer_pause() {
    focus_paused = !focus_paused;
}