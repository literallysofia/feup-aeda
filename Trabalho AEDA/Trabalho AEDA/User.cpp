#include "User.h"

float User::maintenanceFee = 10;

User::User()
{
}

User::User(string name) :name(name)
{
}

User::User(int ID, string name, float balance, string username, string password, int nt, string ad, Date lastA) : ID(ID), name(name) {
	this->username = username;
	this->password = password;
	this->balance = balance;
	ntrips = nt;
	address = ad;
	lastAccess = lastA;
	this->upToDate = 0;
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

int User::updated() const
{
	return this->upToDate;
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

void User::setAdress(string ad)
{
	address = ad;
}

string User::getAddress() const
{
	return address;
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
Driver::Driver(int ID, string name, float balance, string username, string password, int nt, string ad, Date lastA) : User(ID, name, balance, username, password,nt, ad, lastA) {
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

Passenger::Passenger(int ID, string name, float balance, string username, string password, int nt, string ad, Date lastA) : User(ID, name, balance, username, password, nt, ad, lastA) {
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

ostream & operator<<(ostream & out, const User *u)
{
	out << u->getID() << ";" << u->getName() << ";";

	if (u->car())
		out << "1";
	else out << "0";

	out << ";" << u->getBalance() << ";" << u->getUsername() << ";" << u->getPassword() << ";" << u->getNtrips();

	out << ";" << u->getAddress() << ";" << u->getLastAccess() << endl;

	return out;
}
