#include "Controller.h"
#include <cstdint>
#include <cstdio>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>

Controller::Controller(const uint32_t input_direction, const uint32_t output_direction, const uint8_t mask)
{
	input_fd = wiringPiI2CSetup(input_direction);
	output_fd = wiringPiI2CSetup(output_direction);
	this->mask = mask;
}

Controller::~Controller()
{
	wiringPiI2CWrite(input_fd, 0);
	wiringPiI2CWrite(output_fd, 0);
    close(input_fd);
    close(output_fd);
}

void Controller::write_in_leds(const uint8_t value)
{
	wiringPiI2CWrite(output_fd, value);
}

uint8_t Controller::ReadInput()
{
	uint8_t valueRead = wiringPiI2CRead(input_fd);
	valueRead &= mask;
	return valueRead;
}