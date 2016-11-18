#pragma once
#include <string>
#include <vector>
#include "Trip.h"
#include "Transactions.h"

using namespace std;

class User
{
protected:
	int ID;
	const string name;
	string username;
	string password;
	float balance; //saldo disponivel na conta
	static float maintenanceFee;
	int ntrips;
	vector <User *> buddies;
	
public:
	User();
	User(string name);
	User(int ID, string name, float balance, string username, string password,int nt);
	~User();
	void setUsername(string username);
	void setID(int ID);
	int getID() const;
	string getName() const;
	string getUsername() const;
	string getPassword() const;
	float getBalance() const;
	int getNtrips() const;
	void setNtrips();
	void deposit(float value);
	virtual bool car() const;
	virtual void addTrip(int tripID, string first, string last) {};
	virtual string getFirst() const;
	virtual string getLast() const;
	
	virtual float payment();
	void resetTrips();
	void addBuddy(User * user);
	void deleteBuddies() { buddies.clear(); }
	vector<User *> getBuddies() const { return buddies; };
	bool operator ==(const User *u) const;
};

class Driver :
	public User
{
public:
	Driver(int ID, string name, float balance, string username, string password,int nt);
	float payment();
	bool car() const;
};

class Passenger :
	public User
{
public:
	Passenger(string name);
	Passenger(int ID, string name, float balance, string username, string password,int nt);
	float payment();
	bool car() const;
};