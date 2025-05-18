#ifndef COMMON_H
#define COMMON_H

#include <map>

#include "pins.h"

typedef enum {
    YELLOW,
    GREEN,
    BLUE,
    RED
} COLORNUMBERS;

static const std::map<int, COLORNUMBERS> color_number_map = {
    {INPUT_VALUE_YELLOW, YELLOW},
    {INPUT_VALUE_GREEN, GREEN},
    {INPUT_VALUE_BLUE, BLUE},
    {INPUT_VALUE_RED, RED}
};

static const std::map<int, std::string> color_name_map = {
    {YELLOW, "YELLOW"},
    {GREEN, "GREEN"},
    {BLUE, "BLUE"},
    {RED, "RED"}
};

#endif