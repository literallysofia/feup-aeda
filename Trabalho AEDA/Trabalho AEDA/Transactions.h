#pragma once
#include <string>
#include <vector>

using namespace std;

class Transaction
{
private:
	int id;
	string date;
	float value;
public:
	Transaction (unsigned int id, string date, float value);
	unsigned int GetId() const;
	string GetDate() const;
	float GetValue() const;
};