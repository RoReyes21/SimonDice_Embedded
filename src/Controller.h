#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdint>
#include <functional>

class Controller
{
  public:
	/**
	 * @brief Constructs a Controller for a player.
	 * 
	 * @param input_direction Input buttons I2C controller.
	 * @param output_direction Output leds I2C controller.
	 * @param mask An optional mask value to configure specific bits, defaulting to 0xF0.
	 */
	explicit Controller(const uint32_t input_direction, const uint32_t output_direction, const uint8_t mask = 0xF0);
	~Controller();

	/**
	 * @param value Value to write in the outputs (leds) I2C controller.
	 */
	void write_in_leds(const uint8_t value);

	/**
	 * @return uint8_t Last I2C controller input.
	 */
	uint8_t ReadInput();

  private:
	uint32_t input_fd = 0;
	uint32_t output_fd = 0;
	uint8_t mask = 0;
};

#endif