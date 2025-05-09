#include "Controller.h"
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// bool Controller::isrRaised = false;
// uint8_t Controller::lastInput = 0;

void Controller::OnISR()
{
	std::cout << "ISR Raised\r";
	Controller::isrRaised = true;
}

Controller::Controller(const uint32_t input_direction, const uint32_t output_direction, const uint32_t isrPin, const uint8_t mask)
{
	input_fd = wiringPiI2CSetup(input_direction);
	output_fd = wiringPiI2CSetup(output_direction);
	this->mask = mask;
	this->isrPin = isrPin;
}

void Controller::Write(const uint8_t value)
{
	wiringPiI2CWrite(output_fd, value);
}

void Controller::BeginRead(void (*callback)())
{
	// isrRaised = false;
	// wiringPiISR(isrPin, INT_EDGE_FALLING, callback);
	// wiringPiISR(isrPin, INT_EDGE_RISING, &Controller::OnISR);
}

uint8_t Controller::ReadInput()
{
	uint8_t valueRead = wiringPiI2CRead(input_fd);
	valueRead &= mask;
	
	// if (!isrRaised) return 0;
	// if (valueRead == 0) return 0;
	// {
		// isrRaised = false;
		// return 0;
	// }

	// isrRaised = false;
	// lastInput = (valueRead >> 4) & 0x0F;
	return valueRead;
}

void Controller::EndRead()
{
	wiringPiISRStop(isrPin);
}