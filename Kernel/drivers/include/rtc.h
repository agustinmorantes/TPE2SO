#pragma once

#include <stdint.h>

typedef struct Time {
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} Time;

Time getCurrentTime();
void printCurrentTime();
