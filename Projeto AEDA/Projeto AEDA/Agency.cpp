#include "Agency.h"
Utilities ut;

unsigned int Agency::lastID = 1;

Agency::Agency()
{
}

Agency::~Agency()
{
}

unsigned int Agency::getLastID() {

	unsigned int toBeReturned = lastID;
	lastID++;
	return toBeReturned;
}