#pragma once
#include <string>
#include <vector>
#include "Trip.h"
#include "Transactions.h"

using namespace std;

struct pTrip {
	int id;
	string first;
	string last;
};

class User
{
protected:
	int ID;
	const string name;
	string username;
	string password;
	float balance; //saldo disponivel na conta
	static int maintenanceFee;
	vector <User *> buddies;
	
public:
	User();
	User(string name);
	User(int ID, string name, float balance, string username, string password);
	~User();
	void setUsername(string username);
	void setID(int ID);
	int getID() const;
	string getName() const;
	string getUsername() const;
	string getPassword() const;
	float getBalance() const;
	void deposit(float value);
	virtual bool car() const;
	virtual void addTrip(int tripID, string first, string last) {};
	virtual string getFirst() const;
	virtual string getLast() const;
	
	virtual void payment();
	void addBuddy(User * user);
	void deleteBuddies() { buddies.clear(); }
	vector<User *> getBuddies() const { return buddies; };
	bool operator ==(const User *u) const;
};

class Driver :
	public User
{
private:
	int numSeats;
public:
	Driver(int ID, string name, float balance, string username, string password);
	int getNumSeats() const;		//apenas retorna o numero de lugares dados pelo utilizador,
	void payment();
	bool car() const;
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
	vector<pTrip> pTrips; //vetor com a estrutura pTrip que diz o ID da trip na qual esta, e origem e destino do trecho
public:
	Passenger(string name);
	Passenger(int ID, string name, float balance, string username, string password);
	int getNumTrips() const;
	vector<pTrip> getPTrips();
	void setNumTrips();
	void payment();
	bool car() const;
	void resetTrips(void);
	void addTrip(int tripID, string first, string last);
	//bool searchTrip(vector<Trip> &vec);
};