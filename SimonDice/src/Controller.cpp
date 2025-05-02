#include "Controller.h"
#include <cstdint>
#include <functional>
#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

bool Controller::isrRaised = false;
uint8_t Controller::lastInput = 0;

void Controller::OnISR()
{
	Controller::isrRaised = true;
}

Controller::Controller(const uint32_t direction, const uint32_t isrPin)
{
	fd = wiringPiI2CSetup(direction);
	this->isrPin = isrPin;
}

void Controller::Write(const uint8_t value)
{
	wiringPiI2CWrite(fd, value);
}

void Controller::BeginRead()
{
	isrRaised = false;
	wiringPiISR(isrPin, INT_EDGE_RISING, &Controller::OnISR);
}

uint8_t Controller::ReadInput()
{
	uint8_t valueRead = wiringPiI2CRead(fd) & 0xF0;
	wiringPiI2CWrite(fd, lastInput);

	if (!isrRaised) return 0;
	if (valueRead == 0)
	{
		isrRaised = false;
		return 0;
	}

	isrRaised = false;
	lastInput = (valueRead >> 4) & 0x0F;
	return lastInput;
}

void Controller::EndRead()
{
	wiringPiISRStop(isrPin);
}