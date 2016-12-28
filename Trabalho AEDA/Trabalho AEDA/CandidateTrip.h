#pragma once

/** @defgroup CandidateTrip CandidateTrip
* @{
*
* CandidateTrip class declaration
*/

#include <string>
#include <vector>
#include "User.h"

using namespace std;


class CandidateTrip
{
private:

	/** @name  CandidateTrip data-members*/
	/**@{
	*
	*/
	User *passanger;
	User *driver;
	float distance; //distancia desde o inicio da viagem até onde o user entra
	string initStop;
	string endStop;
	/** @} end of Trip data-members */

public:
	/**
	* @brief CandidateTrip constructor from individual parameters
	*
	* @param passenger pointer
	* @param driver pointer
	* @param distance from the first stop of the passenger to the first stop of the driver
	* @param code of the first stop of the passneger
	* @param code of the last stop of the passenger
	*/
	CandidateTrip(User *u, User *d, float dist, string IS, string ES);

	/** @name Basic Class Functions*/
	/**@{
	*
	* Functions that perform basic class functionality
	*/

	/**
	* @brief Retrieves object's passenger
	*
	* @return pointer to the passenger
	*/
	User *getPassanger() const;

	/**
	* @brief Retrieves object's driver
	*
	* @return pointer to the driver
	*/
	User *getDriver() const;

	/**
	* @brief Retrieves object's distance
	*
	* @return float distance in km
	*/
	float getDistance() const;

	/**
	* @brief Retrieves object's first stop
	*
	* @return string of the code of the first stop
	*/
	string getInitStop() const;

	/**
	* @brief Retrieves object's last stop
	*
	* @return string of the code of the last stop
	*/
	string getEndStop() const;

	/** @} end of Basic Class Functions */

	/**
	* @brief Verifies if the driver and the passenger in this object are buddies
	*
	* @return bool true if the password they are buddies, false if they aren't
	*/
	bool areBuddies() const;

	/** @name Trip Operators Functions*/
	/**@{
	*
	* Basic Operators of the class
	*/

	/**
	* @brief Compares two objects of the class to check if one is less than the other comparing if buddies and the distance
	*
	* @param ct1 object for comparison
	*
	* @return true if object is not buddy and the distance is smaller
	*/
	bool operator<(const CandidateTrip & ct1) const; 

	/** @} end of Trip Operators Functions */
};



