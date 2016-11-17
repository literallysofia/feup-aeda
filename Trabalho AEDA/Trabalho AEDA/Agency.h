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

	//Formas de acesso
	int sessionID;
	int sessionPos;

	//Vetores globais
	vector<User *> Users;
	vector<Trip> Trips;
	vector<Trip> ActiveTrips;
	vector<Transaction> Transactions;
	vector<stop> stopsAvailable;

public:
	Agency();
	~Agency();

	//Cria uma nova instancia.
	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

	//Menu's

	void registerUser();
	void loginUser();
	void loginGuest();

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
	void menuDisplayStops();
	void menuDisplayRecord();

	int menuDisplayTransactions();
	void optionsMenuDTrans();

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

	void menuRunTrip();


	//User Only
	int mainMenu_User();
	void optionsMainMenu_User();

	int menuAccount();
	void optionsMenuAccount();
	void menuAddBuddy();

	void menuCreateTrip();
	void menuJoinTrip();
	void showRecTrips(vector<Trip> recTrips, vector<Trip> buddieTrips, vector<string> stopCodes);
	void showRecTripsGuest(vector<Trip> recTrips, vector<string> stopCodes);


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
	bool notBuddy(string bUsername);


	//Functions
	void addUser(User* u);
	void addBuddy();
	float deposit();
	void endMonth();
	time_t getUnixCode(Date &d, Hour &h);

	//Trip Related
	void addTrip();
	void joinTrip();
	vector<Trip> searchTrip(vector<string> stopCodes, Date tripDate);
	vector<Trip> availableTrips(vector<Trip> possibleTrips, vector<string> stopCodes);
	bool availableSpace(Trip possibleTrip, vector<string> stopCodes);
	bool hasBuddies(Trip recTrip);
	void chooseTrip(vector<Trip> recTrips, vector<Trip> buddieTrips, vector<string> stopCodes);
	void runTrip(int tripID);
	void joinTripGuest();
	void chooseTripGuest(vector<Trip> recTrips, vector<string> stopCodes);

	//Displays
	void displayUsers();
	void displayBuddies(); 
	void displayTransactions();
	void displayStops();
	void displayRecord();
	void displayActiveTrips();

	/*
	void imprimeTrips();					//function that uses the Trips class' operator<< method to
	//print all agency's trips to screen
	void readUsers(std::ifstream & infile);    //TODO

	void readTrips(std::ifstream & infile);
	*/

};


