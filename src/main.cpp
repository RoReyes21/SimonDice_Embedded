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
#include "pins.h"
#include "common.h"
#include "utils.h"

volatile bool stopProgram = false;
int max_score = 0;

/**
 * @brief Función para la interrupción SIGINT (ctrl + c)
 * Utilizada solamente para detener el programa.
 * @param s Numero del signal recibido.
 */
void onSigInt(int s)
{
	std::cout << "\rExiting...\n";
	if (s == SIGINT)
		stopProgram = true;
}

bool gaming_simon_says(int number_players, std::shared_ptr<SimonDice> game, std::shared_ptr<Display> display, std::shared_ptr<Controller> contrls_p1, std::shared_ptr<Controller> contrls_p2 = nullptr) {

	if (game == nullptr || display == nullptr || contrls_p1 == nullptr) {
		std::cerr << "Error: Game, Display or Controller is null." << std::endl;

		if (number_players == 2 && contrls_p2 == nullptr)
			std::cerr << "Error: Second Controller is null." << std::endl;

		return false;
	}

	std::string print_info = number_players == 1 ? "1P" : "2P";
	std::cout << "Iniciando juego en modo de " << print_info << "\n";

	game->initialize_sequence();

	do
	{
		display->DrawInGameCounter(game->get_current_level() * 10, YELLOW);
	} while (!stopProgram && game->play_level(contrls_p1, display) && number_players == 1 ? true : game->play_level(contrls_p2, display, false));	

	display->DrawGameOver((game->get_current_level() - 1) * 10);

	if (((game->get_current_level() - 1) * 10) > max_score)
	{
		max_score = ((game->get_current_level() - 1) * 10);
		write_score_file("data/score.txt", max_score);
		std::cout << "Nuevo record: " << max_score << "\n";
	}
	std::this_thread::sleep_for(std::chrono::seconds(2));
	display->DrawMenu();
}

int main()
{
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = onSigInt;
	sigIntHandler.sa_flags = 0;
	sigemptyset(&sigIntHandler.sa_mask);
	sigaction(SIGINT, &sigIntHandler, nullptr);

	std::shared_ptr<Controller> contrls_p1 = std::make_shared<Controller>(I2C_ADDR_INPUT_P1, I2C_ADDR_OUTPUT_P1);
	std::shared_ptr<Controller> contrls_p2 = std::make_shared<Controller>(I2C_ADDR_INPUT_P2, I2C_ADDR_OUTPUT_P2);
	std::shared_ptr<Display> display = std::make_shared<Display>();
	std::shared_ptr<SimonDice> game = std::make_shared<SimonDice>();

	std::srand(std::time({}));

	wiringPiSetupPinType(WPI_PIN_BCM);

#if !defined(TEST_SIMON_DICE) && !defined(TEST_DISPLAY) && !defined(TEST_CONTROLLER)

	contrls_p1->write_in_leds(0xFF);

	if (display->SetupDisplay() != 0)
		return -1;

	max_score = read_score_file("data/score.txt");
	
	display->DrawMenu();
	int current_menu = 0;
	display->SelectOption(static_cast<MENU_OPTIONS>(current_menu));

	while (!stopProgram)
	{
		uint8_t input = 0;
		int selection = 0;

		while (input == 0)
			input = contrls_p1->ReadInput();

		contrls_p1->write_in_leds(input);

		printf("Value: %u\n", input);
		selection = static_cast<int>(input);

		while (input != 0)
			input = contrls_p1->ReadInput();
		
		contrls_p1->write_in_leds(0x0);

		if (selection == INPUT_VALUE_YELLOW)
		{
			display->DrawGameOver(420); //TODO: Crear funcion para despedirse
			stopProgram = true;
		} 
		else if (selection == INPUT_VALUE_GREEN)
		{

			if (current_menu == SINGLEPLAYER)
			{
				gaming_simon_says(1, game, display, contrls_p1);
			} 
			else if (current_menu == MULTIPLAYER)
			{
				gaming_simon_says(2, game, display, contrls_p1, contrls_p2);
			} 
			else if (current_menu == RECORDS)
			{
				std::cout << "Mostrando records\n";

				display->DrawInGameCounter(max_score, YELLOW); //TODO: Crear funcion para mostrar el record
				std::this_thread::sleep_for(std::chrono::seconds(3));
				display->DrawMenu();
			}
		} 
		else if (selection == INPUT_VALUE_BLUE)
		{
			current_menu = (current_menu - 1 + 3) % 3;
		} 
		else if (selection == INPUT_VALUE_RED)
		{
			current_menu = (current_menu + 1) % 3;
		}

		display->SelectOption(static_cast<MENU_OPTIONS>(current_menu));

		std::this_thread::sleep_for(std::chrono::milliseconds(400));
	}

	std::cout << "Fin del programa\n";
#endif

#if TEST_SIMON_DICE
	contrls_p1.write_in_leds(0xFF);

	std::cout << "Juego iniciado. ¡Sigue la secuencia!" << std::endl;
    game.initialize_sequence();

    while (game.play_level(&contrls_p1)) {
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
	contrls_p1.write_in_leds(0xFF);

	std::vector<int> user_sequence;
	while (!stopProgram)
	{
		uint8_t input = 0;

		while (input == 0)
		{
			input = contrls_p1.ReadInput();
		}

		contrls_p1.write_in_leds(input);
		user_sequence.push_back(input);

		printf("Value: %u\n", input);

		while (input != 0)
		{
			input = contrls_p1.ReadInput();
		}

		contrls_p1.write_in_leds(0x0);
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
	}
#endif
	return 0;
}