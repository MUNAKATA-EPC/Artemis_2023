/*
 *DSR1202.cpp
 *
 *created by anbara
 */


#include "Arduino.h"
#include "DSR1202.h"


DSR1202::DSR1202(int pin)
{
	PinNo = pin;
}

void DSR1202::Init()
{
	if(PinNo == 2)
	{
		Serial2.begin(115200);
	}
	else if(PinNo == 3)
	{
		Serial3.begin(115200);
	}
	else
	{
		Serial1.begin(115200);
	}
}

void DSR1202::move(int a, int b, int c, int d, bool breaking)
{
	int val = 0;
	int input[4] = {a, b, c, d};
	String StringA = "0";
	String StringB = "0";
	String StringC = "0";
	String StringD = "0";
	String StringX = "0";
	String StringY = "0";
	String StringZ = "0";
	String String0 = "0";

	if(breaking)
	{
		StringA = "1R000";
		StringB = "2R000";
		StringC = "3R000";
		StringD = "4R000";

	}
	else
	{
		StringX = String(1);
		val = input[0];
		if (val < 0 && val >= -100)
		{
			StringY = String('R');
			val = abs(val);
			StringZ = String(val);
		}
		else if (val >= 0 && val <= 100)
		{
			StringY = String('F');
			StringZ = String(val);
		}
		else
		{
			StringY = String('F');
			StringZ = String(0);
		}
		if (val < 10)
		{
			String0 = String("00");
			StringZ = String0 + StringZ;
		}
		else if (val < 100)
		{
			String0 = String('0');
			StringZ = String0 + StringZ;
		}
		else
		{
			String0 = String("");
		}
		StringA = StringX + StringY + StringZ;


		StringX = String(2);
		val = input[1];
		if (val < 0 && val >= -100)
		{
			StringY = String('R');
			val = abs(val);
			StringZ = String(val);
		}
		else if (val >= 0 && val <= 100)
		{
			StringY = String('F');
			StringZ = String(val);
		}
		else
		{
			StringY = String('F');
			StringZ = String(0);
		}
		if (val < 10)
		{
			String0 = String("00");
			StringZ = String0 + StringZ;
		}
		else if (val < 100)
		{
			String0 = String('0');
			StringZ = String0 + StringZ;
		}
		else
		{
		}
		StringB = StringX + StringY + StringZ;


		StringX = String(3);
		val = input[2];
		if (val < 0 && val >= -100)
		{
			StringY = String('R');
			val = abs(val);
			StringZ = String(val);
		}
		else if (val >= 0 && val <= 100)
		{
			StringY = String('F');
			StringZ = String(val);
		}
		else
		{
			StringY = String('F');
			StringZ = String(0);
		}
		if (val < 10)
		{
			String0 = String("00");
			StringZ = String0 + StringZ;
		}
		else if (val < 100)
		{
			String0 = String('0');
			StringZ = String0 + StringZ;
		}
		else
		{
		}
		StringC = StringX + StringY + StringZ;


		StringX = String(4);
		val = input[3];
		if (val < 0 && val >= -100)
		{
			StringY = String('R');
			val = abs(val);
			StringZ = String(val);
		}
		else if (val >= 0 && val <= 100)
		{
			StringY = String('F');
			StringZ = String(val);
		}
		else
		{
			StringY = String('F');
			StringZ = String(0);
		}
		if (val < 10)
		{
			String0 = String("00");
			StringZ = String0 + StringZ;
		}
		else if (val < 100)
		{
			String0 = String('0');
			StringZ = String0 + StringZ;
		}
		else
		{
		}
		StringD = StringX + StringY + StringZ;
	}

	if(PinNo == 2)
	{
		Serial2.println(StringA + StringB + StringC + StringD);
	}
	else if(PinNo == 3)
	{
		Serial3.println(StringA + StringB + StringC + StringD);
	}
	else
	{
		Serial1.println(StringA + StringB + StringC + StringD);
	}
}
