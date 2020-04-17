/*
* SX_Key.h
* 按键模块的实现
* Created: 2017-10-10 23:05:39
*  Author: sunxdd
说明：接口分配如下


使用例子
#include "SX_Key.h"
void setup() {
SX_Tetris.init();
}
void loop() {
SX_Tetris.run();
}

*/

#ifndef _SX_KEY_h
#define _SX_KEY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define KEY_UP     8
#define KEY_DOWN   7
#define KEY_LEFT   6
#define KEY_RIGHT  5
#define KEY_PAUSE  4
#define KEY_RESET  3

class SX_KeyClass
{
 protected:


 public:
	// 初始化
	void init();
	// 键盘扫描 有键按下返回键值，否则返回 -1
	char  keyRead();
private:
	byte arKeys[6] = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_PAUSE, KEY_RESET };
};

extern SX_KeyClass SX_Key;

#endif

