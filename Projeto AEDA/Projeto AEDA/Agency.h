#pragma once

#include "User.h"
#include <vector>
#include <fstream>

using namespace std;

class Agency
{
private:
	static Agency* singleton_instance;
	static unsigned int lastID;			//last ID attributed to a User
	vector<User *> users;				//vector including all the registred Users of the agency
	//vector<Trip *> trips;
	//vector<Transaction>
	static double maintenaceFee;
public:
	Agency();
	~Agency();

	static unsigned int getLastID();		//function that return the lastID of the agency and increments it by 1

	void imprimeUsers();					//function that uses the Users class' operator<< method to
											//print all agency's users to screen

	void imprimeTrips();					//function that uses the Trips class' operator<< method to
											//print all agency's trips to screen
	void readUsers(std::ifstream & infile);    //TODO

	void readTrips(std::ifstream & infile);

	static double getFee() { return maintenaceFee; }

	static void changeFee(double newValue) { maintenaceFee = newValue; }

	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

};

