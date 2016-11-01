#include "User.h"



User::User(string name, string password): ID(Agency::getLastID()), name(name) {
	this->password = password;
}


User::~User()
{
}
