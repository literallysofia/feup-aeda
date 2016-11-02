#pragma once
#include <Windows.h>

class Utilities
{
public:
	Utilities();
	~Utilities();
	void setcolor(int ForgC);
	void clearScreen();

	void white();
	void blue();
	void grey();
	void red();
};