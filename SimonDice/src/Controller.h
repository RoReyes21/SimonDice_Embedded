#include <cstdint>
#include <functional>

class Controller
{
  public:
	explicit Controller(const uint32_t input_direction, const uint32_t output_direction, const uint32_t isrPin, const uint8_t mask = 0xF0);
	void Init();
	void Write(const uint8_t value);
	void BeginRead(void (*callback)());
	uint8_t ReadInput();
	void EndRead();
	void OnISR();

  private:
	bool isrRaised = false;
	uint8_t lastInput = 0;
	uint32_t input_fd = 0;
	uint32_t output_fd = 0;
	uint32_t isrPin = 0;
	uint8_t mask = 0;
};