#pragma once

/** @defgroup Vehicle 
* @{
*
* Vehicle class declaration
*/

#include "User.h"
#include <string>

using namespace std;

class Vehicle
{
private:

	/** @name  Vehicle data-members*/
	/**@{
	*
	*/
	string brand;
	string model;
	int year;
	User *driver;
	/** @} end of Vehicle data-members */
public:
	/**
	* @brief Vehicle constructor
	*
	* @param brand of vehicle
	* @param model of vehicle
	* @param year of vehicle
	* @param pointer to owner of vehicle (user)
	*/
	Vehicle(string brand, string model, int year, User *driver);

	/**
	* @brief Vehicle destructor
	*/
	~Vehicle();

	/** @name Basic Class Functions*/
	/**@{
	*
	* Functions that perform basic class functionality
	*/

	/**
	* @brief returns the vehicle's brand
	*
	* @return brand of vehicle
	*/
	string getBrand() const;

	/**
	* @brief returns the vehicle's model
	*
	* @return model of vehicle
	*/
	string getModel() const;

	/**
	* @brief returns the vehicle's year
	*
	* @return year of vehicle
	*/
	int getYear() const;

	/**
	* @brief returns the vehicle's owner
	*
	* @return owner of vehicle
	*/
	User* getUser() const;

	/**
	* @brief Sets object's owner
	*
	* @param owner (user) to set
	*/
	void setUser(User* d1);

	/**
	* @brief operator for organization of the BST
	*
	* @param v1 object of vehicle
	*/
	bool operator<(const Vehicle& v1) const;
	/** @} end of Basic Class Functions*/

	/**
	* @brief operator for display of a vehicle
	*
	* @return display string
	*/
	friend ostream& operator<<(ostream& os, const Vehicle& v1) {
		os << v1.brand << ";" << v1.model << ";" << v1.year << ";" << v1.driver->getName();
		return os;
	}
};

