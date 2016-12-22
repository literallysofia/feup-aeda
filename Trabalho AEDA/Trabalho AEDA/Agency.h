#pragma once

/** @defgroup Agency Agency
* @{
*
* Agency class declaration
*/

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
#include "BST.h"
#include "Vehicle.h"

using namespace std;

/** @name  Stop Struct*/
/**@{
*
* Struct that keeps info regarding the name and code of a stop
*/
struct stop {
	string code;
	string name;
};
/** @} end of Stop Struct */


struct cars {
	string brand;
	string model;
	int seats;
};

struct distanceStruct {
	string pnt1;
	string pnt2;
	float km;
};

class Agency
{
private:

	/**
	* @brief Agency instance 
	*/
	static Agency* singleton_instance;

	/**
	* @brief Int ID of who is logged in the application for global use
	*/
	int sessionID;

	/**
	* @brief Int Position of logged in User in the Users vector for global use
	*/
	int sessionPos;

	/** @name  Agency's Info Vectors*/
	/**@{
	*
	*/

	/**
	* @brief vector with all users of the application
	*/
	vector<User *> Users;

	/**
	* @brief vector with all trips of the application
	*/
	vector<Trip> Trips;

	/**
	* @brief vector with all active trips of the application
	*/
	vector<Trip> ActiveTrips;

	/**
	* @brief vector with all transactions of the application
	*/
	vector<Transaction> Transactions;

	/**
	* @brief vector with all available stops of the application 
	*/
	vector<stop> stopsAvailable;
	/** @} end of Agency's Info Vectors */

	vector<cars> Cars;

	BST<Vehicle> vehicles;

	vector<distanceStruct> distancesVec;

public:

	/**
	* @brief Agency constructor
	*/
	Agency();

	/**
	* @brief Agency destructor
	*/
	~Agency();

	/**
	* @brief Agency instance creator
	*
	*	Function that creates a single instance of the class Agency
	*/
	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

	/** @name  Login Options*/
	/**@{
	*
	* Functions that appear on program execution to login or register users
	*/

	/**
	* @brief Register a new User to use the application
	*/
	void registerUser();

	/**
	* @brief Runs prompt for valid login credentials
	*/
	void loginUser();

	/**
	* @brief Runs application with an ID = -1 for Guest type
	*/
	void loginGuest();
	/** @} end of Login Options */

	/** @name  Admin Options*/
	/**@{
	*
	* Previleged functions for Admin use only and menus displays
	*/

	/**
	* @brief Opens main menu after Admin login
	*/
	int mainMenu_Admin();

	/**
	* @brief Options in User main menu
	*/
	void optionsMainMenu_Admin();

	/**
	* @brief Opens Admin menu to display Users
	*/
	int menuDisplayUsers();

	/**
	* @brief Options in Admin User display menu
	*/
	void optionsDisplayUsers();

	/**
	* @brief Displays application Users sorted by username
	*/
	void menuDisplayUsersByUsername();

	/**
	* @brief Displays application Users sorted by name
	*/
	void menuDisplayUsersByName();

	/**
	* @brief Opens Admin menu to search information
	*/
	int menuSearch();

	/**
	* @brief Options in Admin search menu
	*/
	void optionsMenuSearch();

	/**
	* @brief Displays Users and their buddies
	*/
	void menuDisplayBuddies();

	/**
	* @brief Displays available stop in the application
	*/
	void menuDisplayStops();

	/**
	* @brief Displays the record of all Agency's Trips
	*/
	void menuDisplayRecord();

	/**
	* @brief Displays all Agency's transactions
	*/
	int menuDisplayTransactions();

	/**
	* @brief Options in Admin transactions menu
	*/
	void optionsMenuDTrans();

	/**
	* @brief Opens Admin menu to search Users
	*/
	int menuSearchUser();

	/**
	* @brief Options in Admin information search menu
	*/
	void optionsMenuSearchUser();

	/**
	* @brief Prompts for User ID to search for
	*/
	void menuSearchUserByID();

	/**
	* @brief Prompts for User username to search for
	*/
	void menuSearchUserByUsername();

	/**
	* @brief Opens Admin menu to search Trip
	*/
	int menuSearchTrip();

	/**
	* @brief Options in Admin Trips search menu
	*/
	void optionsMenuSearchTrip();

	/**
	* @brief Prompts for driver ID to search Trips for
	*/
	void menuSearchTripByDriver();

	/**
	* @brief Prompts for month to search Trips for
	*/
	void menuSearchTripByMonth();

	/**
	* @brief Opens Admin menu to search transactions
	*/
	int menuSearchTransaction();

	/**
	* @brief Options in Admin transaction search menu
	*/
	void optionsMenuSearchTransaction();

	/**
	* @brief Prompts for User to search transactions for
	*/
	void menuSearchTransactionByUser();

	/**
	* @brief Prompts for month to search transactions for
	*/
	void menuSearchTransactionByMonth();

	/**
	* @brief Opens menu for Admin to select a displayed Trip to run
	*/
	void menuRunTrip();
	/** @} end of Admin Options */


	/** @name  User Options*/
	/**@{
	*
	* User's functions and menus
	*/

	/**
	* @brief Opens main menu after User login
	*/
	int mainMenu_User();

	/**
	* @brief Options in User main menu
	*/
	void optionsMainMenu_User();

	/**
	* @brief Opens account info for User
	*/
	int menuAccount();

	/**
	* @brief Options in User account info menu
	*/
	void optionsMenuAccount();

	/**
	* @brief Opens menu for User to add a buddy to his account
	*/
	void menuAddBuddy();

	/**
	* @brief Opens menu for User to create a Trip
	*/
	void menuCreateTrip();

	/**
	* @brief Opens menu for User to join a Trip
	*/
	void menuJoinTrip();
	
	/**
	* @brief Shows recommended trips to a User on screen
	*
	* @param recTrips vector containing the recommended trips without buddies onboard
	* @param buddieTrips vector containing the recommended trips with buddies onboard
	* @param stopCodes vector containing only the initial and final stop of the User
	*/
	void showRecTrips(vector<Trip> recTrips, vector<Trip> buddieTrips, vector<string> stopCodes);

	/**
	* @brief Shows recommended trips to a Guest on screen
	*
	* @param recTrips vector containing the recommended trips
	* @param stopCodes vector containing only the initial and final stop of the Guest
	*/
	void showRecTripsGuest(vector<Trip> recTrips, vector<string> stopCodes);
	/** @} end of User Options */

	/** @name  Data Management functions*/
	/**@{
	*
	* Functions to read from and write to files
	*
	* Reads and writes for:
	* Users, Buddies, Transactions, Available Stops, Trips Record, Active Trips
	*/

	/**
	* @brief Runs all data extraction functions
	*/
	void extractData();

	/**
	* @brief Runs all data saving functions
	*/
	void saveData();

	/** @name  User Data*/
	/**@{
	*
	* Functions that manage User data in and out of the application
	*/

	void extractUsers();
	void saveUsers();
	/** @} end of User Data */

	/** @name  Buddies Data*/
	/**@{
	*
	* Functions that manage Buddies data in and out of the application
	*/

	void extractBuddies();
	void saveBuddies();
	/** @} end of Buddies Data */

	/** @name  Transactions Data*/
	/**@{
	*
	* Functions that manage Transactions data in and out of the application
	*/

	void extractTransactions();
	void saveTransactions();
	/** @} end of Transactions Data */

	/**
	* @brief Extracts stops available from file
	*/
	void extractStops();

	/** @name  Record Data*/
	/**@{
	*
	* Functions that manage Trips record data in and out of the application
	*/

	void extractRecord();
	void saveRecord();
	/** @} end of Record Data */

	/** @name  ActiveTrips Data*/
	/**@{
	*
	* Functions that manage active trips data in and out of the application
	*/

	void extractActive();
	void saveActive();
	/** @} end of ActiveTrips Data */

	/** @} end of Data Management functions */

	/** @name  Base Functions*/
	/**@{
	*
	* Functions that manage basic functionalities
	*/

	/**
	* @brief Verifies if a User of given username exists in the app
	*
	* @param username string containing the username to search for
	*
	* @return bool true if such username exists, false otherwise
	*/
	bool validUser(string username); 

	/**
	* @brief Verifies the given password is correct for the user of given position in the vector of the Agency
	*
	* @param password string containing the password to verify
	* @param pos position on the global vector of the User trying to login
	*
	* @return bool true if the password is correct, false otherwise
	*/
	bool validPassword(int pos, string password);

	/**
	* @brief Searchs for the ID of the User of given name
	*
	* @param name string containing the name to search for
	*
	* @return ID of the User, -1 otherwise
	*/
	int findID(string name);

	/**
	* @brief Searchs for the position of the User of given ID, on the Agency's vector of Users
	*
	* @param id int containing the id to search for
	*
	* @return position of the User, -1 if it does not exist
	*/
	int getPos(int id);

	/**
	* @brief Returns last ID in use for Users
	*
	* @return last ID in use in the application
	*/
	int getLastId();

	/**
	* @brief Checks if a given stop code exists
	*
	* @param s string containing the code to search for
	*
	* @return bool true if such stop exists, false otherwise
	*/
	bool checkStop(string s);

	/**
	* @brief Checks if a given username is buddy of the user using the application
	*
	* @param bUsername string containing the buddy username
	*
	* @return bool true if the User with that username is not a buddy, false otherwise
	*/
	bool notBuddy(string bUsername);

	/**
	* @brief Adds a new User to the Agency
	*
	* @param u User pointer to be added
	*/
	void addUser(User* u);

	/**
	* @brief Adds a new User as a buddy to the User using the application
	*/
	void addBuddy();

	/**
	* @brief Deposits an amount to the User's account balance
	*/
	void deposit();

	/**
	* @brief Collects payments from all the registered users adding the transactions to the Agency
	*/
	void endMonth();

	/**
	* @brief Handles bad input from cin
	*/
	void handleInput();

	/**
	* @brief Adds a new User as a buddy to the User using the application
	*
	* @param d object of type Date to convert to Unix timestamp
	* @param h object of type Hour to convert to Unix timestamp
	*
	* @return time_t variable representing the Unix timestamp of the given date and hour combined
	*/
	time_t getUnixCode(Date &d, Hour &h);
	/** @} end of Base Functions */

	/** @name  Trip Related Functions*/
	/**@{
	*
	* Functions regarding trips creation, search and join by Users and Guests
	*/

	/**
	* @brief Adds a new Trip the to Agency
	*/
	void addTrip();

	/**
	* @brief Lets a User search for and join a Trip
	*/
	void joinTrip();

	/**
	* @brief Searches for a trip that fits the parameters
	*
	* @param stopCodes codes for the first and last stop to search Trips for
	* @param tripDate date of the requested trip
	*
	* @return vector containg all the trips that satisfy the prerequesits
	*/
	vector<Trip> searchTrip(vector<string> stopCodes, Date tripDate);

	/**
	* @brief Searches for a trip from the given vector that has available seats in the required stops
	*
	* @param stopCodes codes for the first and last stop to search possibleTrips for
	* @param possibleTrips vector containing all the Trip that are a possible match, obtained from a previous function	
	*
	* @return vector containg all the trips with available seat for passenger
	*/
	vector<Trip> availableTrips(vector<Trip> possibleTrips, vector<string> stopCodes);

	/**
	* @brief Checks if there are seats left to be able to join the trip between point A to point B
	*
	* @param possibleTrip Trip to check for seats between the given stops
	* @param stopCodes codes for the first and last stop to search possibleTrip for
	*
	* @return bool true if there are available seats, false otherwise
	*/
	bool availableSpace(Trip possibleTrip, vector<string> stopCodes);

	/**
	* @brief Checks if there are buddies doing the same trip
	*
	* @param recTrip Trip to check for buddies
	*
	* @return bool true if there are buddies on given trip, false otherwise
	*/
	bool hasBuddies(Trip recTrip);

	/**
	* @brief Lets User choose a Trip displayed on screen separated by existence of buddies or not
	*
	* @param recTrips vector of recommended trips without buddies
	* @param buddieTrips vector of recommended trips with buddies
	* @param stopCodes vector containing the strings of the User's first and last stop
	*/
	void chooseTrip(vector<Trip> recTrips, vector<Trip> buddieTrips, vector<string> stopCodes);

	/**
	* @brief Lets a Guest search for and join a Trip
	*/
	void joinTripGuest();

	/**
	* @brief Lets Guest choose a Trip displayed on screen
	*
	* @param recTrips vector of recommended trips
	* @param stopCodes vector containing the strings of the Guest's first and last stop
	*/
	void chooseTripGuest(vector<Trip> recTrips, vector<string> stopCodes);

	/**
	* @brief Run a select trip with follow-up information of passengers changes, stop by stop
	*
	* @param tripID ID of the trip to run in "real-time"
	*/
	void runTrip(int tripID);
	/** @} end of Trip Related Functions */

	/** @name  Display Functions*/
	/**@{
	*
	* Functions that manage basic functionalities
	*/

	/**
	* @brief Displays all Users on screen
	*/
	void displayUsers();

	/**
	* @brief Displays each User and his buddies on screen
	*/
	void displayBuddies(); 

	/**
	* @brief Displays all Agency transactions on screen
	*/
	void displayTransactions();

	/**
	* @brief Displays all available stops on screen
	*/
	void displayStops();

	/**
	* @brief Displays all agency trips record on screen
	*/
	void displayRecord();

	/**
	* @brief Displays all active trips on screen
	*/
	void displayActiveTrips();
	/** @} end of Display Functions */

	BST<Vehicle> getVehicles() const {
		return vehicles;
	}

	void addVehicle(Vehicle &v1) {
		vehicles.insert(v1);
	}

	void optionsMenuCar();
	int MenuCar();

	void displayCar(); //display dos carros respetivos de um driver(user)
	void displayCars(); //display de todos os carros reconhecidos pela agencia
	bool carExists(string model);
	void addCar();
	void removeCar();

	void extractVehicles();
	void extractVehiclesTree();
	void saveTree();

	void extractDistances();
	float distanceBetweenTwoPoints(string pnt1, string pnt2);
	float distanceRide(vector<string> v1, string pnt1);
};