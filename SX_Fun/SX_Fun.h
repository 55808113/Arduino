/*
* SX_Fun.h
* 公共函数类
* Created: 2017-8-10 23:05:39
*  Author: sunxdd
使用例子

*/

#ifndef _SX_FUN_h
#define _SX_FUN_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//How much to increment or decrement each color every cycle
struct Color {
	byte r;
	byte g;
	byte b;
};

class SX_FunClass
{
protected:


public:
	/*删除数组中的值并且移位
	void remove(int* heap, int key, int size);
	int a[]={0,2,1,4,3,9,5,7,6,8,1,2,3,8,6,4};
	int s;
	int k=2;
	s=sizeof(a)/sizeof(int);
	remove(a,k,s);
	return 0;
	*/
	void remove(int* heap, int key, int size);
	/*===================转换函数======================*/
	//int to const char
	const char* itoa2(int val);
	//string to char*
	char* strtochar(String val);
	/*将字符转化为16进制	
	例子：
    char *s="F1F2F3F4F5F6F7F8";
	byte hex_byte[strlen(s)/2] = {0};
    SX_Fun.StrToHex(s,hex_byte,strlen(s));
	*/
	int StrToHex(char *string, byte *cbuf, int len);
	/*十六进制转字符串
	例子：
	byte data[8]={0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8};
    int len = sizeof(data)/sizeof(data[0]);
    char str[len];
    SX_Fun.HexToStr(str,data,len);
	*/
	void HexToStr(char *ptr, byte *buf, int len);
	/*Convert Hue/Saturation/Brightness values to a packed 32-bit RBG color.
	//返回一个RGB数组
	int * arr;
	arr = SX_Fun.HSVColor();
	*/
	int *HSVColor(float h, float s, float v);
	/*得到随机颜色
	两点:1 Y值范围为0-255
		2 Y值越大,颜色越亮
	*/
	struct Color getRandomColor(byte start = 180, byte end = 255);
	/*得到颜色0xFFFFFF值
	两点:1 Y值范围为0-255
	2 Y值越大,颜色越亮
	获取暗色 默认小于180
	获取亮色 默认大于180
	*/
	uint16_t GetColorInt(struct Color color);
};

extern SX_FunClass SX_Fun;
#endif

