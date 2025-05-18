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

static const std::map<int, int> color_input_map = {
    {INPUT_VALUE_YELLOW, YELLOW},
    {INPUT_VALUE_GREEN, GREEN},
    {INPUT_VALUE_BLUE, BLUE},
    {INPUT_VALUE_RED, RED}
};

static const std::map<int, int> color_output_map = {
    {YELLOW, OUTPUT_VALUE_YELLOW},
    {GREEN, OUTPUT_VALUE_GREEN},
    {BLUE, OUTPUT_VALUE_BLUE},
    {RED, OUTPUT_VALUE_RED}
};

static const std::map<int, std::string> color_name_map = {
    {YELLOW, "YELLOW"},
    {GREEN, "GREEN"},
    {BLUE, "BLUE"},
    {RED, "RED"}
};

#endif