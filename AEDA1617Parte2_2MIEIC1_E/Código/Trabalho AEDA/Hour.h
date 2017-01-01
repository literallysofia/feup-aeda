#pragma once

/** @defgroup Hour Hour
* @{
*
* Hour class declaration
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <stdio.h>

using namespace std;

class Hour {
private:

	/** @name  Hour data-members*/
	/**@{
	*
	*/
	int hour;
	int minutes;
	/** @} end of Hour data-members */

public:

	/**
	* @brief Hour default constructor
	*/
	Hour() {};

	/**
	* @brief Hour constructor from string
	*
	* @param hour string in the hh:mm format
	*/
	Hour(string hour);

	/**
	* @brief Hour constructor from individual integers
	*
	* @param hour hour to set
	* @param minutes minutes to set
	*/
	Hour(int hour, int minutes);

	/** @name Basic Class Functions*/
	/**@{
	*
	* Functions that perform basic class functionality
	*/

	/**
	* @brief Retrieves object's hour
	*
	* @return int hour
	*/
	int getHour() const;

	/**
	* @brief Retrieves object's minutes
	*
	* @return int minutes
	*/
	int getMinutes() const;

	/**
	* @brief Sets object's hour
	*
	* @param hour to set to
	*/
	void setHour(int hour);

	/**
	* @brief Sets object's minutes
	*
	* @param minutes to set to
	*/
	void setMinutes(int mimnutes);
	/** @} end of Basic Class Functions */

	/** @name Hour Operators Functions*/
	/**@{
	*
	* Basic Operators of the class
	*/

	/**
	* @brief Compares two objects of the class to check if one hour if previous to the other
	*
	* @param h2 object for comparison
	*
	* @return true first object is before, false otherwise
	*/
	bool operator<(const Hour &h2) const;

	/**
	* @brief Writes to ostream the information of a object of class Hour
	*
	* @param hour object of which we want to print the information for
	*/
	friend ostream& operator<<(ostream& out, Hour& hour);
	/** @} end of Hour Operators Functions */

	/**
	* @brief Checks if the object of class Hour is valid by evaluating it's private data on logical validity in the real-world
	*
	* @return bool true if valid members, false otherwise
	*/
	bool validHour();

	/**
	* @brief Sets object to be the current system's hour
	*/
	void setCurrent();
};