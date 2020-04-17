
#include "SX_Tetris.h"

void SX_TetrisClass::drawGameWin(byte score, byte level, bool drawColor = true)
{

}

SX_TetrisClass::SX_TetrisClass(byte width, byte height)
{
	_width = width;
	_height = height;
	_num = new word[_height];
	word n = 2;
	//第一行设置为全是111111的。所以1，2，4，8减1就是1111111
	//float转换uint时会把第一位减少一位
	for (byte i = 1; i < _width; i++)
	{
		n = n * 2;
	}
	_numTopBottom = n - 1;
	_numMiddle = n >> 1 | 1;

}

void SX_TetrisClass::_fixSign()
{
	byte m, n;
	word mask;
	for (m = 0; m < SIGN_ALL; m++)//行循环
		for (n = 0; n < SIGN_ALL; n++)//列循环
		{
			//从图形的最下面往上进行判断
			mask = 0x1 << SIGN_ALL * m + n;

			if ((_Sign[0].dat&mask) != 0)
			{
				//mask = 0x1 << (_width - 1) - (_Sign[0].x / _signSize - (SIGN_ALL - 1 - n));
				mask = 0x1 << (_width - 1) - (_Sign[0].x - n);
				if (_Sign[0].y - m > 0)
				{
					_num[_Sign[0].y - m] |= mask;
				}
			}
		}
}

bool SX_TetrisClass::drawLogo()
{
	return true;
}

void SX_TetrisClass::drawBoard()
{

}

void SX_TetrisClass::drawSign(int x, int y, bool drawColor, struct Color color)
{

}

void SX_TetrisClass::tetrisStart()
{	
	randomSeed(analogRead(0));
	_drawLogo();
	_gameInit();
	drawBoard();
	if (_drawFrameEnable) {
		_drawFrame();
	}
	_createNewSign();
	_createSysSign();
}

void SX_TetrisClass::tetrisRun()
{
	//控制图形移动
	_controlSign();

}


void SX_TetrisClass::drawNewSign(int x, int y, bool drawColor, Color color)
{
}

void SX_TetrisClass::drawGameOver()
{
	byte y, x;
	word mask;
	//int numlength = sizeof(_num) / sizeof(word);
	for (y = 1; y < _height - 1; y++)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (x = 1; x < _width - 1; x++)
		{
			//由子类实现
			drawSign(x, y, false);
		}
	}
}

void SX_TetrisClass::setKeyBuffer(String keyBuffer)
{
	if (keyBuffer.length() != 0)
	{
		_KeyBuffer = (int)keyBuffer.toInt();
	}

}

void SX_TetrisClass::setDrawFrameEnable(bool drawFrameEnable)
{
	_drawFrameEnable = drawFrameEnable;
}

byte SX_TetrisClass::getWidth()
{
	return _width;
}

byte SX_TetrisClass::getHeight()
{
	return _height;
}

boolean SX_TetrisClass::_checkKnock(struct Jimu sign)
{
	byte m, n;
	word mask;
	for (m = 0; m < SIGN_ALL; m++)//行循环
		for (n = 0; n < SIGN_ALL; n++)//列循环
		{
			mask = 0x1 << (SIGN_ALL * m + n);
			if ((sign.dat&mask) != 0)
			{

				//mask = 0x1 << (_width - 1) - sign.x / _signSize - (SIGN_ALL - 1 - n);				
				mask = 0x1 << (_width - 1) - (sign.x - n);

				if (sign.y - m > 0 && (_num[sign.y - m] & mask) != 0) {
					return false;
				}

			}
		}
	return true;
}

boolean SX_TetrisClass::_checkDead()
{
	byte m, n;
	word mask;
	for (m = 0; m < SIGN_ALL; m++)//行循环
		for (n = 0; n < SIGN_ALL; n++)//列循环
		{
			mask = 0x1 << SIGN_ALL * m + n;

			if ((_Sign[0].dat&mask) != 0)
			{
				//mask = 0x1 << (_width - 1) - _Sign[0].x / _signSize - (SIGN_ALL - 1 - n);
				mask = 0x1 << (_width - 1) - (_Sign[0].x - n);

				//当Y小于1时是死了。否则会出现Y为负的情况
				if (_Sign[0].y <= 1 || (_Sign[0].y - m >= 0 && (_num[_Sign[0].y - m] & mask) != 0))
					return true;
			}
		}
	return false;
}



void SX_TetrisClass::_delFull()
{
	int m, n, i;
	//当前的符号的Y位置
	byte y;
	//清空一行的个数
	byte offset = 0;
	word mask;
	//int numlength = sizeof(_num) / sizeof(word);	
	y = _Sign[0].y;
	if (y >= _height - 1)//防止越过了下边界
		y = _height - 2;
	uint16_t color = 0xFF0000;
	drawGameWin(_Score, _Level, false);
	//在图形的大小4*4的范围内查找
	for (n = y; n > 0; n--)//积木图标的最顶行开始寻找满行比较有利于运算
	{
		if (_num[n] == _numTopBottom)
		{
			//去掉所有颜色
			_num[n] = _numMiddle;
			for (i = 1; i < _width - 1; i++)
			{
				drawSign(i, n, false);
			}
			_addScore();
			offset++;
		}
		else {
			if (offset != 0)
			{
				//把上面的移动下面来				
				for (i = 1; i < _width - 1; i++)
				{
					mask = 0x1 << i;
					if ((_num[n] & mask) != 0)
					{
						drawSign(((_width - 2) - (i - 1)), (n + offset), true, { 255,0,0 });
					}
				}

				for (i = 1; i < _width - 1; i++)
				{
					mask = 0x1 << i;
					if ((_num[n] & mask) != 0)
					{
						drawSign(((_width - 2) - (i - 1)), n, false);
					}
				}
				_num[n + offset] = _num[n];
				//去掉所有颜色
				_num[n] = _numMiddle;
			}
		}
	}

	drawGameWin(_Score, _Level, true);
}

void SX_TetrisClass::_createNewSign()
{
	byte n;
	word Temp;
	struct Jimu newSign;

	n = random(0, 28);
	//n = 22;
	Temp = Block[n][0] << 8;
	Temp = Temp | Block[n][1];
	newSign.dat = Temp;
	newSign.x = SIGN_ALL;//newSign.x = x - TETRIS_X
	newSign.y = SIGN_ALL;
	newSign.type = n / SIGN_ALL;
	newSign.change = n % SIGN_ALL;
	newSign.color = SX_Fun.getRandomColor();

	_drawSign(_Sign[1], false, true);//先清除
	_drawSign(newSign, true, true);//后画出

	_Sign[1] = newSign;
}

void SX_TetrisClass::_createSysSign()
{
	word mask;
	byte n, m;
	boolean b = false;
	//通过Num列减去符号列得到符号开始出现的X位置
	byte sign_x = (_width - 2 + SIGN_ALL) / 2;
	char sign_y = SIGN_ALL;
	_Sign[0] = _Sign[1];
	for (m = 0; m < SIGN_ALL; m++)//行循环
	{
		//从前面开始查询看是否需要往上
		//将积木图标出现置顶 因为有的图形并不是顶头的。
		for (n = 0; n < SIGN_ALL; n++)//列循环
		{
			mask = 0x1 << (SIGN_ALL - 1 - m) * SIGN_ALL + (SIGN_ALL - 1 - n);
			if ((_Sign[0].dat&mask) != 0)
				b = true;
		}
		if (b)
		{
			break;
		}
		sign_y -= 1;
	}

	_Sign[0].x = sign_x;
	_Sign[0].y = sign_y;
	//从后面开始查询看是否有重叠的
	for (m = 0; m < SIGN_ALL; m++)//行循环
	{
		if (_Sign[0].y > 0 && !_checkKnock(_Sign[0])) {
			_Sign[0].y -= 1;
		}
	}
	_drawSign(_Sign[0]);

	//如果死了就不需要画图形了。这样好看一些
	_gameOverEnable = _checkDead();
	//把当前图形给系统
	_createNewSign();
}

void SX_TetrisClass::_moveSign(struct Jimu &sign, byte key)
{
	switch (key)
	{
	case KEY_LEFT:
		sign.x -= 1;
		break;
	case KEY_RIGHT:
		sign.x += 1;
		break;
	case KEY_DOWN:
		sign.y += 1;
		break;
	case KEY_UP:
		byte i;
		word Temp;
		if (++sign.change > SIGN_ALL - 1)
			sign.change = 0;
		i = sign.type * SIGN_ALL + sign.change;
		Temp = Block[i][0] << 8;
		Temp = Temp | Block[i][1];
		sign.dat = Temp;
		break;
	case KEY_PAUSE:

		break;
	default:
		break;
	}
}

void SX_TetrisClass::_controlSign()
{
	if (_gameOverEnable)
	{
		//Serial.println("_checkDead");
		//delay(500);
		drawGameOver();
		_gameInit();
		_createSysSign();
		return;
	}
	struct Jimu sign = _Sign[0];
	
	if (_KeyBuffer == KEY_PAUSE)
	{
		_pauseFlag = !_pauseFlag;
	}
	if (!_pauseFlag)
	{
		if (_KeyBuffer != 0)
		{
			_moveSign(sign, _KeyBuffer);
			if (_checkKnock(sign))
			{
				//Serial.println(_KeyBuffer);
				_drawSign(_Sign[0], false);
				_moveSign(_Sign[0], _KeyBuffer);
				_drawSign(_Sign[0], true);
			}
			//_DelayTime = millis();
		}
		else
		{
			//delay(50 * (MAX_LEVEL - _Level + 1));
			if (millis() - _DelayTime > 50 * (MAX_LEVEL - _Level + 1))
			{
				_DelayTime = millis();
			}
			else {
				return;
			}

			_moveSign(sign, KEY_DOWN);//假设下降一格
			if (_checkKnock(sign))//判断是否能继续下降一格
			{
				_drawSign(_Sign[0], false);
				_moveSign(_Sign[0], KEY_DOWN);
				_drawSign(_Sign[0], true);
			}
			else
			{
				_fixSign();
				_delFull();
				//drawBoard();
				_createSysSign();
			}
		}
	}

	_KeyBuffer = 0;
}

void SX_TetrisClass::_drawLogo()
{
	while (!drawLogo()) {}
}

void SX_TetrisClass::_drawFrame()
{
	byte y, x;
	word mask;
	//int numlength = sizeof(_num) / sizeof(word);
	for (y = 0; y < _height; y++)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		for (x = 0; x < _width; x++)
		{
			mask = 0x1 << x;
			if ((_num[y] & mask) != 0)
			{
				//由子类实现
				drawSign(x, y);
			}
		}
	}
}

void SX_TetrisClass::_addScore()
{
	_Score++;//每找到一个满行，则分数加1
	//当分数达到10分时升级
	if (_Score == 10)
	{
		if (++_Level > MAX_LEVEL)
			_Level = 1;
	}
}

void SX_TetrisClass::_initNum()
{
	byte m;

	_num[0] = _numTopBottom;
	_num[_height - 1] = _numTopBottom;
	for (m = 1; m <= _height - 2; m++)//为加速，不必要重第一行重画起，只需要从积木图标最下行开始往上的重画
	{
		_num[m] = _numMiddle;
	}

}

void SX_TetrisClass::_drawSign(struct Jimu sign, bool drawColor, bool drawNewSignEnable)
{
	byte m, n;
	int x, y;
	word mask;
	for (m = 0; m < SIGN_ALL; m++) {
		for (n = 0; n < SIGN_ALL; n++)
		{
			mask = 0x1 << SIGN_ALL * m + n;
			if ((sign.dat&mask) != 0)
			{
				x = sign.x - n;
				y = sign.y - m;
				//当画的点超出边框时不画
				if (x > 0 && x < _width - 1 && y>0 && y < _height - 1)
				{
					if (drawNewSignEnable)
					{
						//由子类实现
						drawNewSign(x, y, drawColor, sign.color);
					}
					else {
						//由子类实现
						drawSign(x, y, drawColor, sign.color);
					}
				}
			}
		}
	}
}



void SX_TetrisClass::_gameInit()
{
	_initNum();
	
	drawGameWin(_Score, _Level, false);		
	_Score = 0;
	_Level = 1;
	drawGameWin(_Score, _Level, true);
}




