#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>

int read_score_file(const std::string filename);
void write_score_file(const std::string filename, int max_score);

#endif