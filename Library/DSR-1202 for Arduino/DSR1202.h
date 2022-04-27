/*
 *DSR1202.h
 *
 *created by anbara
 */
 
#ifndef DSR1202_H
#define DSR1202_H

#include "Arduino.h"

class DSR1202
{
  public:
	DSR1202(int pin);
	void Init();
	void move(int a, int b, int c, int d);
  private:
	int PinNo = 0;
};


#endif
