#pragma once

/** @defgroup Stop Stop
* @{
*
* Stop class declaration
*/
#include <string>
#include <vector>
using namespace std;

class Stop
{
private:

	/** @name  Stop data-members*/
	/**@{
	*
	*/

	/**
	* @brief string of 3 letters that represents the code of a stop
	*/
	string code;

	/**
	* @brief Number of available seats at a stop
	*/
	int availableSeats;

	/**
	* @brief vector containing the IDs of the passengers present at that stop
	*/
	vector<int> passengers;
	/** @} end of Stop data-members */

public:

	/**
	* @brief Stop default constructor
	*/
	Stop();

	/**
	* @brief Date constructor from individual parameters
	*
	* @param code to set
	* @param seats to set
	*/
	Stop(string code, int seats);

	/**
	* @brief Date constructor from individual parameters
	*
	* @param code to set
	* @param seats to set
	* @param vpass vector containing IDs of passengers to set
	*/
	Stop(string code, int seats, vector <int> vpass);

	/**
	* @brief Stop default destructor
	*/
	~Stop();

	/** @name Basic Class Functions*/
	/**@{
	*
	* Functions that perform basic class functionality
	*/

	/**
	* @brief Retrieves the object's code
	*
	* @return code of the object
	*/
	string getCode() const;

	/**
	* @brief Retrieves the object's number of available seats
	*
	* @return int number of seats
	*/
	int getAvailableSeats() const;

	/**
	* @brief Retrieves the object's vector of passengers IDs
	*
	* @return vector of the passengers IDs
	*/
	vector<int> getPassengers() const;

	/**
	* @brief Decrements the object's number of available seats by 1
	*/
	void decAvailableSeats();

	/**
	* @brief Adds the ID of a passenger to the object's vector of IDs
	*
	* @param id ID of the passenger to push_back to the vector
	*/
	void addPassenger(int id);
	/** @} end of Basic Class Functions */
};