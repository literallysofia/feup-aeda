#pragma once
#include <string>
#include <vector>
#include "Trip.h"

using namespace std;

class User
{
protected:
	int ID;
	const string name;
	string password;
	float balance; //saldo disponivel na conta
	static int maintenanceFee;
	vector <User *> buddies;
	
public:
	User(string name);
	User(int ID, string name, float balance, string password);

	~User();
	int getID() const;
	string getName() const;
	string getPassword() const;
	float getBalance() const;
	void deposit(float value);

	virtual bool car() const;
	virtual void addTrip(Trip &t) {};
	virtual bool searchTrip(vector<Trip> &vec);
	virtual string getFirst() const;
	virtual string getLast() const;
	
	virtual void payment();
	void addBuddy(User * user) { buddies.push_back(user); };
	void deleteBuddies() { buddies.clear(); }
	vector<User *> getBuddies() const { return buddies; };
};

class Driver :
	public User
{
private:
	int numSeats;
	Trip currentTrip;
public:
	Driver(int ID, string name, float balance, string password);
	int getNumSeats() const;		//apenas retorna o numero de lugares dados pelo utilizador,
	Trip getCurrentTrip() const;		//retorna um objeto da classe Trip
	void payment();
	bool car() const;
	void addTrip(Trip& t);
	bool searchTrip(vector<Trip> &vec) const;
	string getFirst() const;
	string getLast() const;
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
	int currentTrip;

public:

	Passenger(string name);
	Passenger(int ID, string name, float balance, string password);
	int getNumTrips() const;
	string getFirst() const;
	string getLast() const;
	void setNumTrips();
	void payment();
	bool car() const;
	void resetTrips(void);
	void addTrip(Trip &t) { numTrips++; };
	bool searchTrip(vector<Trip> &vec);
};