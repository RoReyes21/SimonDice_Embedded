#ifndef SIMON_DICE_H
#define SIMON_DICE_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

class SimonDice {

public:
    SimonDice();
    
    void start_game();
    bool play_level();
    bool check_sequence(const std::vector<int>& userSequence);
    const std::vector<int>& get_secuence() const { return sequence; }
    int get_current_level() const { return current_level; }

    void add_to_sequence() {
        current_level++;
        sequence.push_back(rand() % 4);
    }

    void initialize_sequence() {
        sequence.clear();
        current_level = 0;
    }

private:
    std::vector<int> sequence;
    int current_level;
};

#endif