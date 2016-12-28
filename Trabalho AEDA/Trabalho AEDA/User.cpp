#include "User.h"

float User::maintenanceFee = 10;

User::User()
{
}

User::User(string name) :name(name)
{
}

User::User(int ID, string name, float balance, string username, string password, int nt) : ID(ID), name(name) {
	this->username = username;
	this->password = password;
	this->balance = balance;
	ntrips = nt;
}

User::~User()
{
}

void User::setUsername(string username)
{
	this->username = username;
}

void User::setID(int ID)
{
	this->ID = ID;
}

int User::getID() const
{
	return ID;
}

void User::setLastAccess(Date dt)
{
	lastAccess = dt;
}

Date User::getLastAccess() const
{
	return lastAccess;
}

string User::getName() const
{
	return name;
}

string User::getUsername() const
{
	return username;
}

string User::getPassword() const
{
	return password;
}

float User::getBalance() const
{
	return balance;
}

int User::getNtrips() const
{
	return ntrips;
}

void User::setNtrips()
{
	ntrips++;
}

void User::setInactive()
{
	isInactive = true;
}

void User::setActive()
{
	isInactive = false;
}

void User::deposit(float value)
{
	balance += value;
}

float User::payment()
{
	return 0.00;
}

void User::resetTrips()
{
	ntrips = 0;
}

void User::addBuddy(User * user)
{
	buddies.push_back(user);
}

bool User::car() const
{
	return false;
}

bool User::operator ==(const User *u) const {

	if (this->ID == u->ID||this->username==u->username)
		return true;
	else
		return false;

}

void User::setPassword(string password)
{
	this->password = password;
}

void User::removeBuddy(int ID)
{
	for (unsigned int i = 0; i < buddies.size(); i++) {
		if (buddies.at(i)->getID() == ID) {
			buddies.erase(buddies.begin() + i);
			i--;
		}
	}
	return;
}


/*DRIVER CLASS*/
Driver::Driver(int ID, string name, float balance, string username, string password, int nt) : User(ID, name, balance, username, password,nt) {
}

float Driver::payment()
{
	balance -= maintenanceFee;
	balance += ntrips;
	
	return maintenanceFee;
}

bool Driver::car() const
{
	return true;
}

/*PASSENGER CLASS*/

Passenger::Passenger(string name) : User(name) {
}

Passenger::Passenger(int ID, string name, float balance, string username, string password, int nt) : User(ID, name, balance, username, password, nt) {
}

float Passenger::payment()
{
	balance -= (maintenanceFee + (ntrips * 2)); //paga 2 euros por viagem - desconto de socio
	return (maintenanceFee + (ntrips * 2));
}

bool Passenger::car() const
{
	return false;
}
