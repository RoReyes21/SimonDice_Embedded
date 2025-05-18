#ifndef COMMON_H
#define COMMON_H

#include <map>

typedef enum {
    YELLOW,
    GREEN,
    BLUE,
    RED
} COLORNUMBERS;

static const std::map<int, COLORNUMBERS> color_number_map = {
    {16, YELLOW},
    {32, GREEN},
    {64, BLUE},
    {128, RED}
};

static const std::map<int, std::string> color_name_map = {
    {YELLOW, "YELLOW"},
    {GREEN, "GREEN"},
    {BLUE, "BLUE"},
    {RED, "RED"}
};

#endif