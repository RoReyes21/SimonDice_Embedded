#include "utils.h"

int read_score_file(const std::string filename) {

    std::ifstream file(filename.c_str());
    std::string line;
    int max_score = 0;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.rfind("Max_Score=", 0) == 0) {
                max_score = std::stoi(line.substr(10));
                break;
            }
        }
        file.close();
    } else {
        std::cout << "No se pudo abrir el archivo.\n";
    }

    return max_score;
}

void write_score_file(const std::string filename, int max_score) {
    std::ofstream file(filename.c_str());
    if (file.is_open()) {
        file << "Max_Score=" << max_score << std::endl;
        file.close();
    } else {
        std::cout << "No se pudo abrir el archivo.\n";
    }
}