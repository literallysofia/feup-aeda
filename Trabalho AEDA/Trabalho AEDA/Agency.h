#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <Windows.h>
#include <algorithm>
#include "Utilities.h"
#include "Tools.h"
#include "User.h"
#include "Guest.h"
#include "Trip.h"
#include "Transactions.h"

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
	vector<string> stopsAvailable = { "a","b","c" };
	vector<Transaction> Transactions;
	vector<stop> Stops;

public:
	Agency();
	~Agency();

	//Cria uma nova instância.
	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

	//Elimina a instância atual e cria outra.
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

	void menuDisplayBuddies();
	void menuDisplayTransactions();
	void menuDisplayStops();


	//User Only
	int mainMenu_User();
	void optionsMainMenu_User();


	//Files

	void extractUsers();
	void saveUsers();
	void extractBuddies();
	void saveBuddies();
	void extractTransactions();
	void saveTransactions();
	void extractStops();
	void saveStops();

	//Basic Functions

	bool validUser(string username); //existe user
	bool validPassword(int pos, string password); //verifica se password esta correta
	int findID(string name); //retorna id de name, id = -1 caso nao exista
	int getPos(int id); //retorna posicao no vetor de users de id UTIL!!!
	int getLastId();


	//Functions
	void addUser(User* u);
	void addTrip();
	bool checkStop(string s);
	void runTrip(int tripID);

	//Displays
	void displayUsers();
	void displayBuddies(); 
	void displayTransactions();
	void displayStops();

	/*
	void imprimeTrips();					//function that uses the Trips class' operator<< method to
	//print all agency's trips to screen
	void readUsers(std::ifstream & infile);    //TODO

	void readTrips(std::ifstream & infile);


	float endMonth();
	*/


};