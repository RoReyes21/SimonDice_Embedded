#ifndef DISPLAY_H
#define DISPLAY_H

#include "ST7789_TFT_LCD_RDL.hpp"

enum MENU_OPTIONS
{
	SINGLEPLAYER,
	MULTIPLAYER,
	RECORDS
};

class Display
{
  private:
	ST7789_TFT myTFT;
	int8_t RST_TFT = 23;
	int8_t DC_TFT = 24;
	int GPIO_CHIP_DEVICE = 0;

	uint8_t OFFSET_COL = 0;
	uint8_t OFFSET_ROW = 0;
	uint16_t TFT_WIDTH = 240;
	uint16_t TFT_HEIGHT = 240;

	int HWSPI_DEVICE = 0;
	int HWSPI_CHANNEL = 0;
	// int HWSPI_SPEED = 8000000;
	int HWSPI_SPEED = 125000000;
	int HWSPI_FLAGS = 3;

  public:
	uint16_t RgbTo565(uint16_t r, uint16_t g, uint16_t b);
	void SelectOption(MENU_OPTIONS option);
	uint8_t SetupDisplay();
	void DrawInGameCounter(uint32_t value, int enum_color);
	#warning DrawGameOver no se muestra bien
	void DrawGameOver(uint32_t score);
	void DrawMenu();

	// ! REMOVE LATER
	void DemoInGame();
};

#endif