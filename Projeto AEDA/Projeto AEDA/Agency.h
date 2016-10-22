#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <Windows.h>
#include <algorithm>
#include "Utilities.h"
using namespace std;

class Agency
{
private:
	static Agency* singleton_instance;
public:
	Agency();
	~Agency();


	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

};


