#include "Transactions.h"

Transaction::Transaction(unsigned int id, Date date, float value)
{
	this->id = id;
	this->date = date;
	this->value = value;
}

unsigned int Transaction::GetId() const
{
	return id;
}

Date Transaction::GetDate() const
{
	return date;
}

float Transaction::GetValue() const
{
	return value;
}
