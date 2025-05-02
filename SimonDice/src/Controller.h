#include <cstdint>
#include <functional>

class Controller
{
  public:
	explicit Controller(const uint32_t direction, const uint32_t isrPin);
	void Init();
	void Write(const uint8_t value);
	void BeginRead();
	uint8_t ReadInput();
	void EndRead();

  private:
	static void OnISR();
	static bool isrRaised;
	static uint8_t lastInput;
	uint32_t fd = 0;
	uint32_t isrPin = 0;
};