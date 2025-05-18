#include "simon_dice.h"

SimonDice::SimonDice() : current_level(1) {
    srand(static_cast<unsigned int>(time(0)));
}

void SimonDice::start_game() {
    std::cout << "Juego iniciado. ¡Sigue la secuencia!" << std::endl;
    initialize_sequence();

    while (play_level()) {
        if (current_level > 10) {
            std::cout << "¡Felicidades! Has completado todos los niveles." << std::endl;
            break;
        }
    }

    std::cout << "Juego terminado. Nivel alcanzado: " << current_level << std::endl;
}   
 
bool SimonDice::play_level() {
    add_to_sequence();
    
    std::cout << "Nivel " << current_level << ". Memoriza la secuencia." << std::endl;

    for (int i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        system("clear");
    }

    std::vector<int> user_sequence;
    for (size_t i = 0; i < sequence.size(); ++i) {
        int input;
        std::cout << "Introduce el elemento " << i << " de la secuencia: ";
        std::cin >> input;
        user_sequence.push_back(input);
    }

    if (check_sequence(user_sequence)) {
        std::cout << "¡Correcto! Pasas al siguiente nivel." << std::endl;
        return true;
    } else {
        std::cout << "Incorrecto. Fin del juego." << std::endl;
        return false;
    }
}

bool SimonDice::check_sequence(const std::vector<int>& user_sequence) {
    if (user_sequence.size() != sequence.size()) {
        return false;
    }
    for (size_t i = 0; i < sequence.size(); ++i) {
        if (sequence[i] != user_sequence[i]) {
            return false;
        }
    }
    return true;
}
