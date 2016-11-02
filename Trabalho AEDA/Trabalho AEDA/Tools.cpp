#include "Tools.h"

Tools::Tools()
{
}

Tools::~Tools()
{
}

bool Tools::outputName(string output)
{
	if ((int)output.at(0) >= 48 && (int)output.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
		return false;
	else return true;
}