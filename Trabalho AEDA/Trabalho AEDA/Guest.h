#pragma once
#include <string>

using namespace std;

class Guest
{
private:
	const string name;
	string start, end;
public:
	Guest();
	~Guest();
	string getName() const;
	string getStart() const;
	string getEnd() const;
	//void setStart(string s) { start = s; };
	//void setEnd(string e) { end = e; };
};