#include "simon_dice.h"
#include "common.h"

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
 
bool SimonDice::play_level(Controller* cntrls) {
    add_to_sequence();
    
    std::cout << "Nivel " << current_level << ". Memoriza la secuencia." << std::endl;

    for (int i = 0; i < sequence.size(); ++i) {
        if (color_name_map.find(sequence[i]) != color_name_map.end()) {
            std::cout << color_name_map.at(sequence[i]) << std::flush << std::endl;
        } else {
            std::cerr << "Error: Key not found in color_name_map for sequence element " << sequence[i] << std::endl;
            return false;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //system("clear");
    }

    std::vector<int> user_sequence;
    for (size_t i = 0; i < sequence.size(); ++i) {
        uint8_t input = 0;
        std::cout << "Introduce el elemento " << i << " de la secuencia: " << std::flush << std::endl;
        
        while (input == 0) {
            input = cntrls->ReadInput();
        }
        cntrls->write_in_leds(input);
        user_sequence.push_back(color_number_map.at(input));

        std::cout << "Valor presionado: " << static_cast<int>(input) << std::flush << std::endl;

        while (input != 0) {
            input = cntrls->ReadInput();
        }
        cntrls->write_in_leds(0x0);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
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
