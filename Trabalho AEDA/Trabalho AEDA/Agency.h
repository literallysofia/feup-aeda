#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <ctime>
#include <Windows.h>
#include <algorithm>
#include "Utilities.h"
#include "Tools.h"
#include "User.h"
#include "Guest.h"
#include "Trip.h"
#include "Transactions.h"
#include "Stop.h"
#include "Date.h"
#include "SearchAndSort.h"

using namespace std;

struct stop {
	string code;
	string name;
};



class Agency
{
private:
	static Agency* singleton_instance;

	int sessionID;
	int sessionPos;

	//Global Vectors
	vector<User *> Users;
	vector<Trip> Trips;
	vector<Guest *> Guests;
	vector<Trip> ActiveTrips;
	vector<Transaction> Transactions;
	vector<stop> stopsAvailable;

public:
	Agency();
	~Agency();

	//Cria uma nova inst�ncia.
	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

	//Elimina a inst�ncia atual e cria outra.
	/*void logout() {
	delete singleton_instance;
	singleton_instance = NULL;
	instance()->importInfo();
	}*/
	
	vector<User *> getUsers();

	//Menu's

	void registerUser();
	void loginUser();

	//Admin Only
	int mainMenu_Admin();
	void optionsMainMenu_Admin();

	int menuDisplayUsers();
	void optionsDisplayUsers();

	void menuDisplayUsersByUsername();
	void menuDisplayUsersByName();

	int menuSearch();
	void optionsMenuSearch();

	void menuDisplayBuddies();
	void menuDisplayTransactions();
	void menuDisplayStops();
	void menuDisplayRecord();


	int menuSearchUser();
	void optionsMenuSearchUser();
	void menuSearchUserByID();
	void menuSearchUserByUsername();

	int menuSearchTrip();
	void optionsMenuSearchTrip();
	void menuSearchTripByDriver();
	void menuSearchTripByMonth();

	int menuSearchTransaction();
	void optionsMenuSearchTransaction();
	void menuSearchTransactionByUser();
	void menuSearchTransactionByMonth();


	//User Only
	int mainMenu_User();
	void optionsMainMenu_User();

	int menuAccount();
	void optionsMenuAccount();
	void menuAddBuddy();

	int menuCreateTrip();
	int menuJoinTrip();
	void showRecTrips(vector<Trip> recTrips, vector<Trip> buddieTrips, vector<string> &stopCodes);


	//Files

	void extractData();
	void saveData();
	void extractUsers();
	void saveUsers();
	void extractBuddies();
	void saveBuddies();
	void extractTransactions();
	void saveTransactions();
	void extractStops();
	void extractRecord();
	void saveRecord();
	void extractActive();
	void saveActive();

	//Basic Functions

	bool validUser(string username); //existe user
	bool validPassword(int pos, string password); //verifica se password esta correta
	int findID(string name); //retorna id de name, id = -1 caso nao exista
	int getPos(int id); //retorna posicao no vetor de users de id UTIL!!!
	int getLastId();
	bool checkStop(string s);


	//Functions
	void addUser(User* u);
	void addBuddy();
	void addTrip();
	void joinTrip();
	vector<Trip> searchTrip(vector<string> &stopCodes, Date &tripDate);
	vector<Trip> availableTrips(vector<Trip> &possibleTrips, vector<string> &stopCodes);
	bool availableSpace(Trip &possibleTrip, vector<string> &stopCodes);
	bool hasBuddies(Trip &recTrip);
	void choseTrip(vector<Trip> &recTrips, vector<Trip> &buddieTrips, vector<string> &stopCodes);
	//void runTrip(int tripID);
	float deposit();
	time_t getUnixCode(Date &d, Hour &h);

	//Displays
	void displayUsers();
	void displayBuddies(); 
	void displayTransactions();
	void displayStops();
	void displayRecord();

	/*
	void imprimeTrips();					//function that uses the Trips class' operator<< method to
	//print all agency's trips to screen
	void readUsers(std::ifstream & infile);    //TODO

	void readTrips(std::ifstream & infile);


	float endMonth();
	*/

};


