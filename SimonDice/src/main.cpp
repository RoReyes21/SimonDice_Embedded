#include "Controller.h"
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

volatile bool stopProgram = false;
Controller player1(0x20, 0x21, 17);

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

void PlayerOneCallback() { player1.OnISR(); }

int main()
{
	// region Configuración interrupciones Linux.
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = onSigInt;
	sigIntHandler.sa_flags = 0;
	sigemptyset(&sigIntHandler.sa_mask);
	sigaction(SIGINT, &sigIntHandler, nullptr);
	// endregion

	wiringPiSetupPinType(WPI_PIN_BCM);

	player1.Write(0xFF);

	std::vector<int> user_sequence;

	// player1.BeginRead(PlayerOneCallback);
	while (true)
	{
		uint8_t input = 0;

		while (input == 0)
		{
			input = player1.ReadInput();
		}

		player1.Write(input);
		user_sequence.push_back(input);

		// usleep(200000); // Smart delay of 200ms
		// wait to user release
		printf("Value: %u\n", input);
		
		while (input != 0)
		{
			input = player1.ReadInput();
		}

		player1.Write(0x0); // Reset to 0x0
	}
	// player1.EndRead();

	sleep(1);
	return 0;
}