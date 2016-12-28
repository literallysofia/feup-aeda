#pragma once

/** @defgroup User Transaction
* @{
*
* User class declaration
*/
#include <string>
#include <vector>
#include "Transactions.h"

using namespace std;

class User
{
protected:

	/** @name  User data-members*/
	/**@{
	*
	*/
	int ID;
	const string name;
	string username;
	string password;
	float balance; //account balance
	static float maintenanceFee;
	int ntrips;
	vector <User *> buddies;
	string address;
	Date lastAccess;
	/** @} end of User data-members */
	
public:

	/**
	* @brief User default constructor
	*/
	User();

	/**
	* @brief User constructor from individual parameter
	*
	* @param name name of the new User to set
	*/
	User(string name);

	/**
	* @brief User constructor from individual parameters
	*
	* @param id of the User to set
	* @param name of the User to set
	* @param balance of the User to set
	* @param username of the User to set
	* @param password of the User to set
	* @param nt number of trips of the User to set
	* @param ad addres of the User to set
	* @param lastA date os last access of the User to set
	*/
	User(int ID, string name, float balance, string username, string password,int nt, string ad, Date lastA);

	/**
	* @brief User destructor
	*/
	~User();

	/** @name Basic Class Functions*/
	/**@{
	*
	* Functions that perform basic class functionality
	*/

	/**
	* @brief Sets object's username
	*
	* @param username to set
	*/
	void setUsername(string username);

	/**
	* @brief Sets object's ID
	*
	* @param ID id to set
	*/
	void setID(int ID);

	/**
	* @brief Retrieves object's ID
	*
	* @return int id
	*/
	int getID() const;

	/**
	* @brief Sets object's last access date
	*
	* @param Date date to set the last access to, read from file
	*/
	void setLastAccess(Date dt);

	/**
	* @brief Retrieves object's last access date
	*
	* @return Date
	*/
	Date getLastAccess() const;

	/**
	* @brief Retrieves object's name
	*
	* @return string name of the object 
	*/
	string getName() const;

	/**
	* @brief Retrieves object's username
	*
	* @return string username of the object
	*/
	string getUsername() const;

	/**
	* @brief Retrieves object's password
	*
	* @return string password of the User
	*/
	string getPassword() const;

	/**
	* @brief Retrieves object's balance
	*
	* @return float account balance of the User
	*/
	float getBalance() const;

	/**
	* @brief Retrieves object's # of trips
	*
	* @return int number of total month's trips
	*/
	int getNtrips() const;

	/**
	* @brief Increments object's # of trips
	*/
	void setNtrips();

	/**
	* @brief Deposits a value in User's account
	*
	* @param value to deposit
	*/
	void deposit(float value);

	/**
	* @brief CHecks if object is a driver
	*
	* @return bool true if User has a car, false otherwise
	*/
	virtual bool car() const;

	/**
	* @brief Resets object's number of monthly trips
	*/
	void resetTrips();
	/** @} end of Basic Class Functions */
	
	/**
	* @brief Retrieves object's payment based on monthly trips #
	*
	* @return float total in euros
	*/
	virtual float payment();

	/**
	* @brief Adds User to vector of Buddies of the object
	*
	* @param user pointer to the User to be added
	*/
	void addBuddy(User * user);

	/**
	* @brief Resets object's vector of buddies
	*/
	void deleteBuddies() { buddies.clear(); }

	/**
	* @brief Retrieves object's vector of Buddies
	*
	* @return vector vector of pointers to the Users who are the object's Buddies
	*/
	vector<User *> getBuddies() const { return buddies; };

	/**
	* @brief Compares two objects of the class User
	*
	* @param u pointer to the User to execute the comparison with
	*
	* @return bool true if ID or Username between User u matches the object's
	*/
	bool operator ==(const User *u) const;

	void setPassword(string password);

	void removeBuddy(int ID);
};

class Driver :
	public User
{
public:

	/**
	* @brief Driver constructor from individual parameters
	*
	* @param id of the User to set
	* @param name of the User to set
	* @param balance of the User to set
	* @param username of the User to set
	* @param password of the User to set
	* @param nt number of trips of the User to set
	*/
	Driver(int ID, string name, float balance, string username, string password, int nt, string ad, Date lastA);

	/**
	* @brief Retrieves object's payment based on monthly trips #
	*
	* @return float total in euros
	*/
	float payment();

	/**
	* @brief CHecks if object is a driver
	*
	* @return bool true if User has a car, false otherwise
	*/
	bool car() const;
};

class Passenger :
	public User
{
public:

	/**
	* @brief User constructor from individual parameter
	*
	* @param name to set has object's name
	*/
	Passenger(string name);

	/**
	* @brief Passenger constructor from individual parameters
	*
	* @param id of the User to set
	* @param name of the User to set
	* @param balance of the User to set
	* @param username of the User to set
	* @param password of the User to set
	* @param nt number of trips of the User to set
	*/
	Passenger(int ID, string name, float balance, string username, string password, int nt, string ad, Date lastA);

	/**
	* @brief Retrieves object's payment based on monthly trips #
	*
	* @return float total in euros
	*/
	float payment();

	/**
	* @brief Checks if object is a driver
	*
	* @return bool true if User has a car, false otherwise
	*/
	bool car() const;

};

/**
* @brief struct used for hash insertion
*/
struct userPtr {
	User *user;
};