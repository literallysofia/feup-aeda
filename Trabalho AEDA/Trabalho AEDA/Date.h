#pragma once

/** @defgroup Date Date
* @{
*
* Date class declaration
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Date {
private:

	/** @name  Date data-members*/
	/**@{
	*
	*/
	int day;
	int month;
	int year;
	/** @} end of Date data-members */

public:

	/**
	* @brief Date default constructor
	*/
	Date() {};

	/**
	* @brief Date constructor from string
	*
	* @param date string in the dd/mm/yyyy format
	*/
	Date(string date);

	/**
	* @brief Date constructor from individual integers
	*
	* @param day day to set
	* @param month month to set
	* @param year year to set
	*/
	Date(int day, int month, int year);

	/** @name Basic Class Functions*/
	/**@{
	*
	* Functions that perform basic class functionality
	*/

	/**
	* @brief Retrieves object's day
	*
	* @return int day
	*/
	int getDay() const;

	/**
	* @brief Retrieves object's month
	*
	* @return int month
	*/
	int getMonth() const;

	/**
	* @brief Retrieves object's year
	*
	* @return int year
	*/
	int getYear() const;

	/**
	* @brief Sets object's day
	*
	* @param day to set to
	*/
	void setDay(int day);

	/**
	* @brief Sets object's month
	*
	* @param month to set to
	*/
	void setMonth(int month);

	/**
	* @brief Sets object's year
	*
	* @param year to set to
	*/
	void setYear(int year);

	/**
	* @brief Converts object of type Date to string
	*
	* @return string in the format dd/mm/yyyy 
	*/
	string toString();
	/** @} end of Basic Class Functions */

	/** @name Date Operators Functions*/
	/**@{
	*
	* Basic Operators of the class
	*/

	/**
	* @brief Writes to ostream the information of a object of class Date
	*
	* @param date object of which we want to print the information for
	*/
	friend ostream& operator<<(ostream& out, Date& date); 

	/**
	* @brief Compares two objects of the class to check if one date if previous to the other
	*
	* @param d1 object we want to check if is previous to the other
	* @param d2 object for comparison
	*
	* @return true first object is previous, false otherwise
	*/
	friend bool operator< (Date & d1, Date& d2);

	/**
	* @brief Compares two objects of the class to check if one date if after the other
	*
	* @param d1 object we want to check if is after the other
	* @param d2 object for comparison
	*
	* @return true first object is after, false otherwise
	*/
	friend bool operator> (Date& d1, Date& d2);

	/**
	* @brief Compares two objects of the class to check if they are the same date
	*
	* @param d1 object for comparison
	* @param d2 object for comparison
	*
	* @return true  objects are equal, false otherwise
	*/
	friend bool operator== (Date& d1, Date& d2); 
	/** @} end of Date Operators Functions */

	/**
	* @brief Calculates the number of days between the object calling the function and other of same class type Date
	*
	* @param other object to calculate numbers of days between
	*
	* @return number of days between the dates
	*/
	int daysBetween(Date &other);

	/**
	* @brief Sets object to be the current system's date
	*/
	void setCurrent();

	/**
	* @brief Checks if the object of class Date is valid by evaluating it's private data on logical validity in the real-world
	*
	* @return bool true if valid members, false otherwise
	*/
	bool valid() const;

};