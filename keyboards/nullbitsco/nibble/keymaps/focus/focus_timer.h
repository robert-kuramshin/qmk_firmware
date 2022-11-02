#ifndef FOCUS_TIMER_H
#define FOCUS_TIMER_H

#include <stdint.h>

typedef enum state{
    WORK = 0,
    REST,
    NUM_STATES,
} state_t;

extern state_t focus_state;
extern uint32_t focus_timer;
extern bool focus_paused;

extern const uint32_t FIVE_MIN;
extern const uint32_t TWENTY_FIVE_MIN;

void handle_timer_onoff(void);

void handle_timer_skip(void);

void handle_timer_pause(void);

void update_time(void);

#endif