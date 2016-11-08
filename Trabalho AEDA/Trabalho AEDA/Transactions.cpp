#include "Transactions.h"

Transaction::Transaction(unsigned int id, string date, float value)
{
	this->id = id;
	this->date = date;
	this->value = value;
}

unsigned int Transaction::GetId() const
{
	return id;
}

string Transaction::GetDate() const
{
	return date;
}

float Transaction::GetValue() const
{
	return value;
}
