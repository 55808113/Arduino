// 
// 
// 

#include "SX_Fun.h"


void SX_FunClass::remove(int* heap, int key, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		if (key == *(heap + i))
		{
			j = i;
			for (j; j < size; j++)
			{
				*(heap + j) = *(heap + j + 1);
			}
			size--;
		}
	}
	for (i = 0; i < size; i++)
		printf("%d ", *(heap + i));
	printf("\n");
}

const char* SX_FunClass::itoa2(int val)
{
	static char result[sizeof(int) << 3 + 2];
	sprintf(result, "%d", val);
	return result;
}

char* SX_FunClass::strtochar(String val) {
	char* c;
	c = new char[val.length() + 1];
	strcpy(c, val.c_str());
	return c;
}


int SX_FunClass::StrToHex(char * string, byte * cbuf, int len)
{
	byte high, low;
	int idx, ii = 0;
	for (idx = 0; idx<len; idx += 2)
	{
		high = string[idx];
		low = string[idx + 1];

		if (high >= '0' && high <= '9')
			high = high - '0';
		else if (high >= 'A' && high <= 'F')
			high = high - 'A' + 10;
		else if (high >= 'a' && high <= 'f')
			high = high - 'a' + 10;
		else
			return -1;

		if (low >= '0' && low <= '9')
			low = low - '0';
		else if (low >= 'A' && low <= 'F')
			low = low - 'A' + 10;
		else if (low >= 'a' && low <= 'f')
			low = low - 'a' + 10;
		else
			return -1;

		cbuf[ii++] = high << 4 | low;
	}
	return 0;
}

void SX_FunClass::HexToStr(char * ptr, byte * buf, int len)
{
	for (int i = 0; i < len; i++)
	{
		sprintf(ptr, "%02x", buf[i]);
		ptr += 2;
	}
}

// Convert Hue/Saturation/Brightness values to a packed 32-bit RBG color.
// hue must be a float value between 0 and 360
// saturation must be a float value between 0 and 1
// brightness must be a float value between 0 and 1
int *SX_FunClass::HSVColor(float h, float s, float v) {
	/*Serial.print("h:");
	Serial.println(h);
	Serial.print("s:");
	Serial.println(s);
	Serial.print("v:");
	Serial.println(v);*/
	int *rgb = (int *)malloc(sizeof(int) * 3);
	h = constrain(h, 0, 360);
	s = constrain(s, 0, 1);
	v = constrain(v, 0, 1);

	int i, b, p, q, t;
	float f;

	h /= 60.0;  // sector 0 to 5
	i = floor(h);
	f = h - i;  // factorial part of h

	b = v * 255;
	p = v * (1 - s) * 255;
	q = v * (1 - s * f) * 255;
	t = v * (1 - s * (1 - f)) * 255;

	switch (i) {
	case 0:
		rgb[0] = b;
		rgb[1] = t;
		rgb[2] = p;
		break;
	case 1:
		rgb[0] = q;
		rgb[1] = b;
		rgb[2] = p;
		break;
	case 2:
		rgb[0] = p;
		rgb[1] = b;
		rgb[2] = t;
		break;
	case 3:
		rgb[0] = p;
		rgb[1] = q;
		rgb[2] = b;
	case 4:
		rgb[0] = t;
		rgb[1] = p;
		rgb[2] = b;
		break;
	default:
		rgb[0] = b;
		rgb[1] = p;
		rgb[2] = q;
		break;
	}
	/*Serial.print("hue:");
	Serial.println(rgb[0]);
	Serial.print("saturation:");
	Serial.println(rgb[1]);
	Serial.print("brightness:");
	Serial.println(rgb[2]);*/
	return rgb;
}

Color SX_FunClass::getRandomColor(byte start, byte end)
{
	//  为了在白色背景上显示，尽量生成深色
	Color color;
	double Y;
	bool result;
	do
	{
		color.r = random(0, 255);
		color.g = random(0, 255);
		color.b = random(0, 255);
		//Y值计算公式
		Y = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
		result = Y >= start && Y <= end;
	} while (!result);

	return color;
}

uint16_t SX_FunClass::GetColorInt(Color color)
{
	return ((uint16_t)(color.r & 0xF8) << 8) |
		((uint16_t)(color.g & 0xFC) << 3) |
		(color.b >> 3);;
}

SX_FunClass SX_Fun;
