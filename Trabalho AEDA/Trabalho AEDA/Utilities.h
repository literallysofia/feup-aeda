#pragma once
#include <Windows.h>
#include <iostream>
#include <limits>
#include <conio.h>
#include <ctime>

#undef max

using namespace std;

//TODO deixar a classe lmao

class Utilities
{
public:
	Utilities();
	~Utilities();

	void menuHeader();
	void setcolor(int ForgC);
	void clearScreen();
	int readInt(int min, int max);
	void getEnter();
	void clearScreen_param(int x);

	void white();
	void blue();
	void grey();
	void red();
	void green();
	void yellow();
};

