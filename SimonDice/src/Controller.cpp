#include "Controller.h"
#include <cstdint>
#include <cstdio>
#include <wiringPi.h>
#include <wiringPiI2C.h>


Controller::Controller(const uint32_t input_direction, const uint32_t output_direction, const uint8_t mask)
{
	input_fd = wiringPiI2CSetup(input_direction);
	output_fd = wiringPiI2CSetup(output_direction);
	this->mask = mask;
}

void Controller::Write(const uint8_t value)
{
	wiringPiI2CWrite(output_fd, value);
}

uint8_t Controller::ReadInput()
{
	uint8_t valueRead = wiringPiI2CRead(input_fd);
	valueRead &= mask;
	return valueRead;
}
