#pragma once
#include "Agency.h"

class Guest
{
	const string name;
	string beginning, end;

public:
	Guest();
	~Guest();
	string getName() const { return name; };
	string getBeginning() const { return beginning; };
	string getEnd() const { return end; };
	void setBeginning(string beg) { beginning = beg; };
	void setEnd(string e) { end = e; };
};

