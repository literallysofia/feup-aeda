#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Date.h"

using namespace std;

class Transaction
{
private:
	int id;
	Date date;
	float value;
public:
	Transaction();
	Transaction (int id, Date date, float value);
	int GetId() const;
	Date GetDate() const;
	float GetValue() const;
	void save(ofstream & out) const;
	friend ostream& operator<<(ostream & out, const Transaction & t);
};