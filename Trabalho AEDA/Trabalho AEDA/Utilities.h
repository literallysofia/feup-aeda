#pragma once
#include <Windows.h>
#include <iostream>
#include <limits>
#include <conio.h>

#undef max

using namespace std;

class Utilities
{
public:
	Utilities();
	~Utilities();
	void setcolor(int ForgC);
	void clearScreen();
	int leInteiro(int min, int max);
	void getEnter();

	void white();
	void blue();
	void grey();
	void red();
	void green();
};

