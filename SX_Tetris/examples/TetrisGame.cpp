// 
// 
// 

#include "TetrisGame.h"
#if defined(SSD1306_TYPE)
//画的对象
Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#elif defined(LED8X8_TYPE)
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN, FLAGS);
#elif defined(WS2812B_TYPE)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(SCREEN_WIDTH, SCREEN_HEIGHT, PIN,
	NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT +
	NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
	NEO_GRB + NEO_KHZ800);
#elif defined(NOKIA5110_TYPE)
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK_PIN, DIN_PIN, DC_PIN, CE_PIN, RST_PIN);
#endif

TetrisGameClass::TetrisGameClass(byte width, byte height) :SX_TetrisClass(width, height)
{
}

bool TetrisGameClass::drawLogo()
{
#if defined(SSD1306_TYPE)
	display.clearDisplay();
	display.drawBitmap((SCREEN_WIDTH - IMG_WIDTH) / 2, 8, codeLogo, IMG_WIDTH, IMG_HEIGHT, 1);

	/*display.setTextSize(1);
	display.setTextColor(_logoMsgBlink);
	display.setCursor(0, 54);
	display.println(F("PRESS ANY KEY TO START..."));*/

	display.display();
	//String code = getKey();
	delay(3000);
	display.clearDisplay();
#elif defined(LED8X8_TYPE)

#elif defined(WS2812B_TYPE)

#elif defined(NOKIA5110_TYPE)
	display.clearDisplay();
	display.drawBitmap((SCREEN_WIDTH - IMG_WIDTH) / 2, 8, codeLogo, IMG_WIDTH, IMG_HEIGHT, 1);

	/*display.setTextSize(1);
	display.setTextColor(_logoMsgBlink);
	display.setCursor(0, 54);
	display.println(F("PRESS ANY KEY TO START..."));*/

	display.display();
	//String code = getKey();
	delay(3000);
	display.clearDisplay();
#endif
	return true;
}

void TetrisGameClass::drawBoard()
{
#if defined(SSD1306_TYPE)
	byte x = getWidth() * SIGN_SIZE + 2;
	byte step = 3;
	display.setTextSize(1);
	display.setTextColor(1);        // Draw white text
	display.setCursor(x, 0);             // Start at top-left corner
	display.println(F("Next:"));
	display.setCursor(x, (step + FONESIZE) * 2);             // Start at top-left corner
	display.println(F("Score:"));
	//display.setCursor(x + 4 * fonesize, (step + FONESIZE) * 2);             // Start at top-left corner
	//display.println(getScore());
	display.setCursor(x, (step + FONESIZE) * 3);             // Start at top-left corner
	display.println(F("Level:"));
	//display.setCursor(x + 4 * fonesize, (step + fonesize) * 3);             // Start at top-left corner
	//display.println(getLevel());
	//display.display();
#elif defined(LED8X8_TYPE)

#elif defined(WS2812B_TYPE)

#elif defined(NOKIA5110_TYPE)

#endif
}

void TetrisGameClass::drawSign(int x, int y, bool drawColor, Color color)
{
	int mX, mY;
	_changeXY(x, y, &mX, &mY);
#if defined(SSD1306_TYPE)	
	display.drawRect(mX*SIGN_SIZE, mY*SIGN_SIZE, SIGN_SIZE, SIGN_SIZE, drawColor);
#elif defined(LED8X8_TYPE)
	lmd.setPixel(mX, mY, drawColor);
#elif defined(WS2812B_TYPE)
	if (!drawColor)
	{
		matrix.drawPixel(mX, mY, matrix.Color(0, 0, 0));
	}
	else {
		matrix.drawPixel(mX, mY, matrix.Color(color.r, color.g, color.b));
	}
#elif defined(NOKIA5110_TYPE)
	display.drawRect(mX*SIGN_SIZE, mY*SIGN_SIZE, SIGN_SIZE, SIGN_SIZE, drawColor);
#endif
}

void TetrisGameClass::drawNewSign(int x, int y, bool drawColor, Color color)
{
	int mX, mY;
	_changeXY(x, y, &mX, &mY);
#if defined(SSD1306_TYPE)	
	display.drawRect((mX + getWidth() + 2)*SIGN_SIZE, (mY + 2)*SIGN_SIZE, SIGN_SIZE, SIGN_SIZE, drawColor);
#elif defined(LED8X8_TYPE)

#elif defined(WS2812B_TYPE)

#elif defined(NOKIA5110_TYPE)

#endif
}

void TetrisGameClass::drawGameWin(byte score, byte level, bool drawColor)
{
#if defined(SSD1306_TYPE)
	byte x = getWidth() * SIGN_SIZE + 2;
	byte step = 3;
	display.setTextSize(1);
	display.setTextColor(drawColor);        // Draw white text
	display.setCursor(x + 4 * FONESIZE, (step + FONESIZE) * 2);             // Start at top-left corner
	display.println(score);
	display.setCursor(x + 4 * FONESIZE, (step + FONESIZE) * 3);             // Start at top-left corner
	display.println(level);
#elif defined(LED8X8_TYPE)

#elif defined(WS2812B_TYPE)

#elif defined(NOKIA5110_TYPE)

#endif
}

void TetrisGameClass::drawGameOver()
{
	int mX, mY;
	bool b = true;
#if defined(SSD1306_TYPE)
	//int numlength = sizeof(_num) / sizeof(word);
	for (byte y = getHeight() - 2; y > 0; y--)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (byte x = 1; x < getWidth() - 1; x++)
		{
			if (b)
			{
				_changeXY(x, y, &mX, &mY);
			}
			else
			{
				_changeXY(getWidth() - 1 - x, y, &mX, &mY);
			}
			display.drawRect(mX*SIGN_SIZE, mY*SIGN_SIZE, SIGN_SIZE, SIGN_SIZE, true);
			display.display();
			delay(2);
		}
		b = !b;
	}
	//int numlength = sizeof(_num) / sizeof(word);
	for (byte y = getHeight() - 2; y > 0; y--)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (byte x = 1; x < getWidth() - 1; x++)
		{
			_changeXY(x, y, &mX, &mY);
			display.drawRect(mX*SIGN_SIZE, mY*SIGN_SIZE, SIGN_SIZE, SIGN_SIZE, false);
		}
	}
	display.display();
#elif defined(LED8X8_TYPE)
	//int numlength = sizeof(_num) / sizeof(word);
	for (byte y = getHeight() - 2; y > 0; y--)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (byte x = 1; x < getWidth() - 1; x++)
		{
			if (b)
			{
				_changeXY(x, y, &mX, &mY);
			}
			else
			{
				_changeXY(getWidth() - 1 - x, y, &mX, &mY);
			}
			lmd.setPixel(mX, mY, true);
			lmd.display();
			delay(20);
		}
		b = !b;
	}
	//int numlength = sizeof(_num) / sizeof(word);
	for (byte y = getHeight() - 2; y > 0; y--)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (byte x = 1; x < getWidth() - 1; x++)
		{
			_changeXY(x, y, &mX, &mY);
			lmd.setPixel(mX, mY, false);
		}
	}
	lmd.display();
#elif defined(WS2812B_TYPE)
	uint16_t color = SX_Fun.GetColorInt(SX_Fun.getRandomColor());
	for (byte y = getHeight() - 2; y > 0; y--)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (byte x = 1; x < getWidth() - 1; x++)
		{
			if (b)
			{
				_changeXY(x, y, &mX, &mY);
			}
			else
			{
				_changeXY(getWidth() - 1 - x, y, &mX, &mY);
			}
			matrix.drawPixel(mX, mY, color);
			matrix.show();
			delay(20);
		}
		b = !b;
	}

	matrix.fillScreen(0);
	matrix.show();
#elif defined(NOKIA5110_TYPE)
	//int numlength = sizeof(_num) / sizeof(word);
	for (byte y = getHeight() - 2; y > 0; y--)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (byte x = 1; x < getWidth() - 1; x++)
		{
			if (b)
			{
				_changeXY(x, y, &mX, &mY);
			}
			else
			{
				_changeXY(getWidth() - 1 - x, y, &mX, &mY);
			}
			display.drawRect(mX*SIGN_SIZE, mY*SIGN_SIZE, SIGN_SIZE, SIGN_SIZE, true);
			display.display();
			delay(2);
		}
		b = !b;
	}
	//int numlength = sizeof(_num) / sizeof(word);
	for (byte y = getHeight() - 2; y > 0; y--)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (byte x = 1; x < getWidth() - 1; x++)
		{
			_changeXY(x, y, &mX, &mY);
			display.drawRect(mX*SIGN_SIZE, mY*SIGN_SIZE, SIGN_SIZE, SIGN_SIZE, false);
		}
	}
	display.display();
#endif
}



void TetrisGameClass::init()
{
	//Serial.begin(9600);
#if defined(SSD1306_TYPE)
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed!"));
		for (;;); // Don't proceed, loop forever
	}
	display.clearDisplay();
	//游戏初始化
	setDrawFrameEnable(true);
#elif defined(LED8X8_TYPE)
	// 开始是否显示
	lmd.setEnabled(true);
	// 0 = low, 10 = high
	lmd.setIntensity(2);
#elif defined(WS2812B_TYPE)
	matrix.begin();
	matrix.setTextWrap(false);
	matrix.setBrightness(BRIGHTNESS);
#elif defined(NOKIA5110_TYPE)
	display.begin();
	// for the best viewing!
	display.setContrast(50);
	//display.display(); // show splashscreen
	display.clearDisplay();   // clears the screen and buffer
	//游戏初始化
	setDrawFrameEnable(true);
#endif
	tetrisStart();

#if defined(SSD1306_TYPE)
	display.display();
#elif defined(LED8X8_TYPE)
	lmd.display();
#elif defined(WS2812B_TYPE)
	matrix.show();
#elif defined(NOKIA5110_TYPE)
	display.display();
#endif
}

void TetrisGameClass::run()
{
	while (true)
	{
		String code = "";
		while (Serial.available())
		{
			char c = Serial.read();
			/*Serial.print("1c");
			Serial.println(c);*/
			code += c;
			/*Serial.print("1code");
			Serial.println(code);*/
			//一定要添加因为有延迟
			delay(2);
		}

		setKeyBuffer(code);
		tetrisRun();
#if defined(SSD1306_TYPE)
		display.display();
#elif defined(LED8X8_TYPE)
		lmd.display();
#elif defined(WS2812B_TYPE)
		matrix.show();
#elif defined(NOKIA5110_TYPE)
		display.display();
#endif
	}
}

void TetrisGameClass::_changeXY(int x, int y, int *n, int *m)
{
#if defined(SSD1306_TYPE)
	*n = x;
	*m = y;
#elif defined(LED8X8_TYPE)
	byte step;
	byte size = 8;

	step = (y - 1) / size;
	*n = size * (1 + step) - x;
	*m = y - (1 + size * step);
#elif defined(WS2812B_TYPE)
	*n = y - 1;
	*m = SCREEN_HEIGHT - x;
#elif defined(NOKIA5110_TYPE)
	*n = x;
	*m = y;
#endif
}

TetrisGameClass TetrisGame;
