#pragma once

#include "Agency.h"
#include <string>

using namespace std;

class User
{
	const string name;
	const unsigned int ID;
	string password;
	vector <User *> buddies;

public:
	User(string name, string password);
	~User();
	void addBuddy(User * user) { buddies.push_back(user); }
};

