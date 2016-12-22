#pragma once

/** @defgroup Trip Transaction
* @{
*
* Trip class declaration
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Stop.h"
#include "Date.h"
#include "Hour.h"
#include "CandidateTrip.h"
using namespace std;

class Trip
{
private:

	/** @name  Trip data-members*/
	/**@{
	*
	*/
	int ID;
	int driver;
	vector<Stop> stops;
	Date date;
	Hour startTime;
	Hour endTime;
	/** @} end of Trip data-members */

	priority_queue<CandidateTrip> candidateQueue;


public:

	/**
	* @brief Trip default constructor
	*/
	Trip();

	/**
	* @brief Trip constructor from individual parameters
	*
	* @param id of the trip to set
	* @param driver of the trip to set
	* @param vector stops of the trip to set
	* @param date of the Trip to set
	* @param start starting hour of the trip
	* @param end estimated ending hour of the trip
	*/
	Trip(int ID, int driver, vector<Stop> stops, Date date, Hour start, Hour end);

	/**
	* @brief Trip destructor
	*/
	~Trip();

	/** @name Basic Class Functions*/
	/**@{
	*
	* Functions that perform basic class functionality
	*/

	/**
	* @brief Retrieves object's driver
	*
	* @return int idof the driver
	*/
	int getDriver() const;

	/**
	* @brief Retrieves object's ID
	*
	* @return int id
	*/
	int getID() const;

	/**
	* @brief Retrieves object's vector of stops
	*
	* @return vector of objects of class Stop
	*/
	vector<Stop> getStops() const;

	/**
	* @brief Retrieves object's Date
	*
	* @return object of class Date
	*/
	Date getDate() const;

	/**
	* @brief Retrieves object's starting hour
	*
	* @return object of class Hour which is the starting hour of the trip
	*/
	Hour getStart() const;

	/**
	* @brief Retrieves object's estimated finishing hour
	*
	* @return object of class Hour which is the estimated finishing hour of the trip
	*/
	Hour getEnd() const;

	/**
	* @brief Retrieves object's origin stop
	*
	* @return string containing the code of the stop
	*/
	string getOrigin() const;

	/**
	* @brief Retrieves object's destination stop
	*
	* @return string containing the code of the stop
	*/
	string getDestination() const;

	/**
	* @brief Sets object's driver id
	*
	* @param id to set to
	*/
	void setDriver(int id);

	/**
	* @brief Sets object's Date
	*
	* @param object of class date to set to
	*/
	void setDate(Date d);

	/**
	* @brief Changes object's stops ir order to add a passenger
	*
	* Decreses the number of available seats in the stops between User's desired stops
	* and adds its userID to each one
	*
	* @param pos index of which stop is going to be changed, in object's vector of stops
	* @param userID id of the User to be added to each stop he is riding
	*/
	void setStops(int pos, int userID);
	/** @} end of Basic Class Functions */

	/**
	* @brief Writes object's information into file
	*
	* @param out ofstream type variable initialized to the location of the file to be written too
	*/
	void save(ofstream & out) const;

	/**
	* @brief Writes object's information into file (only for active trips, to remain in the program for next use)
	*
	* @param out ofstream type variable initialized to the location of the file to be written too
	*/
	void saveAT(ofstream & out) const;

	/** @name Trip Operators Functions*/
	/**@{
	*
	* Basic Operators of the class
	*/

	/**
	* @brief Writes to ostream the information of a object of class Trip
	*
	* @param t object of which we want to print the information for
	*/
	friend ostream& operator<<(ostream& out, const Trip &t);

	/**
	* @brief Basi operator that verifies if two diferent objects of the class Trip have equal data members
	*
	* @param t object we want to compare this-> object with
	*/
	bool operator ==(const Trip t) const;
	/** @} end of Trip Operators Functions */
};