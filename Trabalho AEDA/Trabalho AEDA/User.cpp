#include "User.h"

/*USER CLASS*/
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
	//numTrips = 0;
}

void User::addBuddy(User * user)
{
	buddies.push_back(user);
}

bool User::car() const
{
	return false;
}

/*
bool User::searchTrip(vector<Trip>& vec)
{
	return false;
}
*/
string User::getFirst() const
{
	return string();
}

string User::getLast() const
{
	return string();
}

bool User::operator ==(const User *u) const {

	if (this->ID == u->ID||this->username==u->username)
		return true;
	else
		return false;

}

/*DRIVER CLASS*/
Driver::Driver(int ID, string name, float balance, string username, string password, int nt) : User(ID, name, balance, username, password,nt) {
}

int Driver::getNumSeats() const
{
	return numSeats;
}

float Driver::payment()
{
	balance -= maintenanceFee;
	
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
	numTrips = 0;
}

int Passenger::getNumTrips() const
{
	return numTrips;
}

void Passenger::setNumTrips()
{
	numTrips++;
}

float Passenger::payment()
{
	balance -= (maintenanceFee + (numTrips * 2)); //paga 2 euros por viagem - desconto de socio
	return (maintenanceFee + (numTrips * 2));
}

bool Passenger::car() const
{
	return false;
}