#pragma once
#include <string>
#include <vector>
#include "Trip.h"

using namespace std;

class User
{
protected:
	const int ID;
	const string name;
	string password;
	float balance; //saldo disponivel na conta
	static int maintenanceFee;
	//vector <User *> buddies;
	virtual bool car() { return false; };
public:
	User(int ID, string name, string password);
	~User();
	int getID() const;
	string getName() const;
	string getPassword() const;
	void deposit(float value);
	virtual void payment() { return; };

	//void addBuddy(User * user) { buddies.push_back(user); }
	//vector<User *> getBuddies() const { return buddies; };
};

class Driver :
	public User
{
private:
	int numSeats;
	Trip currentTrip;
public:
	Driver(int ID, string name, string password);
	int getNumSeats() const;		//apenas retorna o numero de lugares dados pelo utilizador,
	Trip getCurrentTrip() const;		//retorna um objeto da classe Trip
	void payment();
	bool car();
	/*
	void setNumSeats(unsigned int num) { numSeats = num; };   //é perguntado ao utilizador aquando de inscricao
	void resetTrips() {};					//nao faz nada se for Driver quando chamada por um iterador
	*/
};

class Passenger :
	public User
{
private:
	int numTrips;
	string first, last;			//nomes das paragens finais e iniciais
								//podem ser sempre as mesmas ou alteradas pelo utilizador no programa
public:
	Passenger(int ID, string name, string password);
	int getNumTrips() const;
	string getFirst() const;
	string getLast() const;
	void setNumTrips();
	void payment();
	bool car();
	void resetTrips(void);
	//void addTrip(void) { numTrips++; };
};