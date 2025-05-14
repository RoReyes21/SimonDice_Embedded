#include "Display.h"

uint16_t Display::RgbTo565(uint16_t r, uint16_t g, uint16_t b)
{
	return ((r << 11) | (g << 5) | b);
}

uint8_t Display::SetupDisplay()
{
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT);
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW, TFT_WIDTH, TFT_HEIGHT);
	if (myTFT.TFTInitSPI(HWSPI_DEVICE, HWSPI_CHANNEL, HWSPI_SPEED, HWSPI_FLAGS, GPIO_CHIP_DEVICE) != rdlib::Success)
		return 3;
	myTFT.TFTsetRotation(myTFT.Degrees_180);
	delayMilliSecRDL(100);
	return 0;
}

void Display::SelectOption(MENU_OPTIONS option)
{
	const uint16_t purple = RgbTo565(18, 17, 30);
	// Clear spaces
	myTFT.writeChar(50, 120, ' ');
	myTFT.writeChar(120, 120, ' ');
	myTFT.writeChar(40, 160, ' ');

	myTFT.setFont(font_orla);
	myTFT.setTextColor(purple);
	switch (option)
	{
	case SINGLEPLAYER:
		myTFT.writeChar(50, 120, '>');
		break;
	case MULTIPLAYER:
		myTFT.writeChar(120, 120, '>');
		break;
	case RECORDS:
		myTFT.writeChar(40, 160, '>');
		break;
	}
}

void Display::DrawInGameCounter(uint32_t value, uint16_t color)
{
	char buffer[256];

	myTFT.setFont(font_groTeskBig);

	myTFT.drawCircle(120, 120, 110, color);
	myTFT.drawCircle(120, 120, 100, color);
	myTFT.drawCircle(120, 120, 90, color);
	myTFT.setTextColor(color);

	snprintf(buffer, 256, "%u", value);

	uint8_t x = (240 / 2) - (strlen(buffer) * 15);
	uint8_t y = (240 / 2) - 30;
	myTFT.setCursor(x, y);

	myTFT.print(buffer);
}

void Display::DrawGameOver(uint32_t score)
{
	char buffer[256];
	myTFT.fillScreen(myTFT.RDLC_BLACK);

	myTFT.setFont(font_groTeskBig);
	myTFT.setTextColor(myTFT.RDLC_RED);

	myTFT.drawRoundRect(50, 50, 140, 140, 15, myTFT.RDLC_RED);

	myTFT.setCursor(55, 55);
	myTFT.print("GAME");

	myTFT.setCursor(55, 120);
	myTFT.print("OVER");

	snprintf(buffer, 256, "Score: %d", score);
	myTFT.setCursor((240 / 2) - ((strlen(buffer) * 15) / 2), 200);
	myTFT.setFont(font_orla);
	myTFT.print(buffer);
}

void Display::DrawMenu()
{
	// ============================== Colors ===================================
	const uint16_t mauve = RgbTo565(25, 41, 30);

	// ============================== Borders ==================================
	myTFT.setFont(font_mint);
	myTFT.fillScreen(myTFT.RDLC_BLACK);

	for (uint8_t i = 0; i < 5; i++)
		myTFT.drawRoundRect(i, i, 240 - (2 * i), 240 - (2 * i), 5, i % 2 == 0 ? myTFT.RDLC_DCYAN : myTFT.RDLC_CYAN);

	// ================================ Title ==================================
	myTFT.setTextColor(mauve);
	myTFT.setCursor(60, 30);
	myTFT.print("Simon");

	myTFT.setCursor(70, 60);
	myTFT.print("Dice");

	// ================================ Menu ===================================
	myTFT.setFont(font_orla);

	myTFT.setCursor(70, 120);
	myTFT.print("1P");

	myTFT.setCursor(140, 120);
	myTFT.print("2P");

	myTFT.setCursor(70, 160);
	myTFT.print("Record");

	// ============================== Options ==================================
	myTFT.setFont(font_retro);
	myTFT.setCursor(20, 210);
	myTFT.setTextColor(myTFT.RDLC_RED);
	myTFT.print("NEXT");

	myTFT.setCursor(70, 210);
	myTFT.setTextColor(myTFT.RDLC_BLUE);
	myTFT.print("PREV");

	myTFT.setCursor(120, 210);
	myTFT.setTextColor(myTFT.RDLC_GREEN);
	myTFT.print("SELECT");

	myTFT.setCursor(190, 210);
	myTFT.setTextColor(myTFT.RDLC_YELLOW);
	myTFT.print("EXIT");
}

void Display::DemoInGame()
{
	#warning Remove in final version
	std::cout << "Demo in game\n";
	myTFT.fillScreen(0);
	myTFT.setFont(font_groTeskBig);
	uint16_t bg = 0;
	for (uint32_t i = 0; i <= 120; i += 10)
	{
		uint8_t selection = std::rand() % 4;

		switch (selection)
		{
		case 0:
			bg = myTFT.RDLC_BLUE;
			break;
		case 1:
			bg = myTFT.RDLC_RED;
			break;
		case 2:
			bg = myTFT.RDLC_GREEN;
			break;
		case 3:
			bg = myTFT.RDLC_YELLOW;
			break;
		}

		DrawInGameCounter(i, bg);

		usleep(80000);
	}
}