#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <font_data_RDL.hpp>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "Controller.h"
#include "Display.h"
#include "simon_dice.h"

volatile bool stopProgram = false;

Display display;
Controller player1(0x20, 0x21);
SimonDice game;

/**
 * @brief Función para la interrupción SIGINT (ctrl + c)
 * Utilizada solamente para detener el programa.
 * @param s Numero del signal recibido.
 */
void onSigInt(int s)
{
	std::cout << "\rExiting...\n";
	if (s == SIGINT)
	{
		stopProgram = true;
		exit(1);
	}
}

int main()
{
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = onSigInt;
	sigIntHandler.sa_flags = 0;
	sigemptyset(&sigIntHandler.sa_mask);
	sigaction(SIGINT, &sigIntHandler, nullptr);

	wiringPiSetupPinType(WPI_PIN_BCM);

	std::srand(std::time({}));

#if TEST_SIMON_DICE
	player1.Write(0xFF);

	std::cout << "Juego iniciado. ¡Sigue la secuencia!" << std::endl;
    game.initialize_sequence();

    while (game.play_level(&player1)) {
        if (game.get_current_level() > 10) {
            std::cout << "¡Felicidades! Has completado todos los niveles." << std::endl;
            break;
        }
    }

    std::cout << "Juego terminado. Nivel alcanzado: " << game.get_current_level() << std::endl;

#endif


#if TEST_DISPLAY
	if (display.SetupDisplay() != 0) return -1;

	std::cout << "Demo menu\n";
	display.DrawMenu();
	for (uint8_t i = 0; i < 5; i++)
	{
		display.SelectOption(static_cast<MENU_OPTIONS>(i % 3));
		usleep(250000);
	}

	display.DemoInGame();

	display.DrawGameOver(86);
#endif

#if TEST_CONTROLLER
	player1.Write(0xFF);

	std::vector<int> user_sequence;
	while (!stopProgram)
	{
		uint8_t input = 0;

		while (input == 0)
		{
			input = player1.ReadInput();
		}

		player1.Write(input);
		user_sequence.push_back(input);

		printf("Value: %u\n", input);

		while (input != 0)
		{
			input = player1.ReadInput();
		}

		player1.Write(0x0);
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
	}
#endif
	return 0;
}