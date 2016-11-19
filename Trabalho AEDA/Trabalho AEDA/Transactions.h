#pragma once

/** @defgroup Transaction Transaction
* @{
*
* Transaction class declaration
*/
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Date.h"

using namespace std;

class Transaction
{
private:

	/** @name  Transaction data-members*/
	/**@{
	*
	*/
	int id;
	Date date;
	float value;
	/** @} end of Transaction data-members */

public:

	/**
	* @brief Transaction default constructor
	*/
	Transaction();

	/**
	* @brief Transaction constructor from individual parameters
	*
	* @param id to set
	* @param Date to set
	* @param value year to set
	*/
	Transaction (int id, Date date, float value);

	/** @name Basic Class Functions*/
	/**@{
	*
	* Functions that perform basic class functionality
	*/

	/**
	* @brief Retrieves object's ID
	*
	* @return int id
	*/
	int GetId() const;

	/**
	* @brief Retrieves object's Date
	*
	* @return Date date
	*/
	Date GetDate() const;

	/**
	* @brief Retrieves object's value
	*
	* @return float value
	*/
	float GetValue() const;
	/** @} end of Basic Class Functions */

	/**
	* @brief Writes object's information into file
	*
	* @param out ofstream type variable initialized to the location of the file to be written too
	*/
	void save(ofstream & out) const;

	/** @name Transaction Operators Functions*/
	/**@{
	*
	* Basic Operators of the class
	*/

	/**
	* @brief Writes to ostream the information of a object of class Transaction
	*
	* @param date object of which we want to print the information for
	*/
	friend ostream& operator<<(ostream & out, const Transaction & t);
	/** @} end of Transaction Operators Functions */
};