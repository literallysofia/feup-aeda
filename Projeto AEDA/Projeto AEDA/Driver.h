#pragma once
#include "User.h"

class Driver :
	public User
{
	unsigned int numSeats;
	
public:
	Driver(std::string name, std::string password);
	~Driver();
	inline bool ownCar() const { return true; }
	void setNumSeats(unsigned int num) { numSeats = num; };   //é perguntado ao utilizador aquando de inscricao
	unsigned int getNumSeats() const { return numSeats; }		//apenas retorna o numero de lugares dados pelo utilizador, 
																//a sua atualizaçao será feita apenas na struct Trip ao longo da viagem
	float payment() const { return Agency::getFee(); };
	void resetTrips() {};					//nao faz nada se for Driver quando chamada por um iterador

};

