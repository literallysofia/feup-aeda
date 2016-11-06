#include "User.h"

/*USER CLASS*/
int User::maintenanceFee = 20;

User::User(int ID, string name, string password) : ID(ID), name(name) {
	this->password = password;
	balance = 0;
}

User::~User()
{
}

int User::getID() const
{
	return ID;
}

string User::getName() const
{
	return name;
}

string User::getPassword() const
{
	return password;
}

float User::getBalance() const
{
	return balance;
}

void User::deposit(float value)
{
	balance += value;
}

/*DRIVER CLASS*/
Driver::Driver(int ID, string name, string password) : User(ID, name, password) {}

int Driver::getNumSeats() const
{
	return numSeats;
}

Trip Driver::getCurrentTrip() const
{
	return currentTrip;
}

void Driver::payment()
{
	balance -= maintenanceFee;
}

bool Driver::car() const
{
	return true;
}

/*PASSENGER CLASS*/

Passenger::Passenger(int ID, string name, string password) : User(ID, name, password) {
	numTrips = 0;
}

int Passenger::getNumTrips() const
{
	return numTrips;
}

string Passenger::getFirst() const
{
	return first;
}

string Passenger::getLast() const
{
	return last;
}

void Passenger::setNumTrips()
{
	numTrips++;
}

void Passenger::payment()
{
	balance -= (maintenanceFee + numTrips); //TODO metodo de pagamento estupido
}

bool Passenger::car() const
{
	return false;
}

void Passenger::resetTrips(void)
{
	numTrips = 0;
}