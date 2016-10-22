#include "User.h"



User::User(string name, string password) : name(name), ID(Agency::getLastID()){
	this->password = password;
}


User::~User()
{
}
