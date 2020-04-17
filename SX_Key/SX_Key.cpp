// 
// 
// 

#include "SX_Key.h"

void SX_KeyClass::init()
{
	for (int i = 0; i < sizeof(arKeys) / sizeof(byte); ++i)
	{
		pinMode(arKeys[i], INPUT);
		digitalWrite(arKeys[i], LOW);
	}

}

char SX_KeyClass::keyRead()
{
	//按钮
	for (byte i = 0; i < sizeof(arKeys) / sizeof(byte); ++i)
	{		
		if (digitalRead(arKeys[i]) == HIGH)
			return arKeys[i];
	}
	//串口
	String code = "";
	while (Serial.available())
	{
		char c = Serial.read();
		code = code + c;
		//一定要添加因为有延迟
		delay(2);
	}
	if (code == "P") {
		return KEY_PAUSE;
	}
	else if (code == "U") {
		return KEY_UP;
	}
	else if (code == "D") {
		return KEY_DOWN;
	}
	else if (code == "R") {
		return KEY_RIGHT;
	}
	else if (code == "L") {
		return KEY_LEFT;
	}	
	
	return -1;
}

SX_KeyClass SX_Key;

