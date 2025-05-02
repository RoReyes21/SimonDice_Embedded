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
	// region Configuración interrupciones Linux.
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = onSigInt;
	sigIntHandler.sa_flags = 0;
	sigemptyset(&sigIntHandler.sa_mask);
	sigaction(SIGINT, &sigIntHandler, nullptr);
	// endregion

	wiringPiSetupPinType(WPI_PIN_BCM);
	Controller player1(0x20, 17);

    std::vector<int> user_sequence;
    
    for (size_t i = 0; i < 5; ++i) {
        uint8_t input = 0;
        
        player1.BeginRead();
		while (input == 0)
		{
            input = player1.ReadInput();
        }
        player1.EndRead();
        
		player1.Write(input);
		user_sequence.push_back(input);
        
		printf("Read: %u\n", input);
    }

	sleep(1);
	return 0;
}