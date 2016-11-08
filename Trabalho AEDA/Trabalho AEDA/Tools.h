#pragma once
#include "Utilities.h"
#include <string>
using namespace std;

class Tools
{
public:
	Tools();
	~Tools();

	bool outputName(string output); //verifica se output é um inteiro(false) ou string(true)
	string insertPassword(); //retorna password escrita com ***
	bool sameString(string a, string b);
};