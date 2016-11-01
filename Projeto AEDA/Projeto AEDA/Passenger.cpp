#include "Passenger.h"


Passenger::Passenger(string name, string password): User(name, password){
	numTrips = 0;
}


Passenger::~Passenger()
{
}

//retorno do total no final do mes e reset do numero de viagens do passageiro
float Passenger::payment() const{

	return  Agency::getFee() + numTrips;
}