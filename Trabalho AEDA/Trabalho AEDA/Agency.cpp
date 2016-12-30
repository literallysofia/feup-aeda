
#include "Agency.h"

/*/////////////////
//// EXCECOES /////
/////////////////*/

class NonexistentStop
{
public:
	string stop;
	NonexistentStop(string name) { stop = name; }
};
ostream & operator<<(ostream &out, const NonexistentStop &obj)
{
	out << "ERROR: The stop '" << obj.stop << "' does not exist.\n"; return out;
}

class RepeatedStop
{
public:
	string stop;
	RepeatedStop(string name) { stop = name; }
};
ostream & operator<<(ostream &out, const RepeatedStop &obj)
{
	out << "ERROR: The stop '" << obj.stop << "' was already used.\n"; return out;
}

class InvalidDate
{
public:
	Date date;
	InvalidDate(Date d) { date = d; }
};
ostream & operator<<(ostream &out, const InvalidDate &obj)
{
	out << "ERROR: '" << obj.date.getDay() << '/' << obj.date.getMonth()
		<< '/' << obj.date.getYear() << "' is not a valid date format.\n"; return out;
};

class PassedDate
{
public:
	int day, month, year;
	PassedDate(int d, int m, int y) { day = d; month = m; year = y; }
};
ostream & operator<<(ostream &out, const PassedDate &obj)
{
	out << "ERROR: '" << obj.day << '/' << obj.month
		<< '/' << obj.year << "' has passed already.\n"; return out;
};

class TooLong
{
public:
	int day, month, year;
	TooLong(int d, int m, int y) { day = d; month = m; year = y; }
};
ostream & operator<<(ostream &out, const TooLong &obj)
{
	out << "ERROR: The trip must be within a year. You entered" << " '" << obj.day << '/' << obj.month
		<< '/' << obj.year << "' .\n"; return out;
};

class InvalidHour
{
public:
	int hour, minutes;
	InvalidHour(int h, int m) { hour = h; minutes = m; }
};
ostream & operator<<(ostream &out, const InvalidHour &obj)
{
	out << "ERROR: '" << obj.hour << ':' << obj.minutes << "' is invalid.\n"; return out;
};

class PassedHour
{
public:
	int hour, minutes;
	PassedHour(int h, int m) { hour = h; minutes = m; }
};
ostream & operator<<(ostream &out, const PassedHour &obj)
{
	out << "ERROR: '" << obj.hour << ':';
	if (obj.minutes < 10)
	{
		out << '0';
	}
	out << obj.minutes << "' as passed already.\n"; return out;
};

class Error
{
public:
	int m;
	Error(int n) { m = n; };
};
ostream & operator<<(ostream &out, const Error &obj)
{
	out << "ERROR: Invalid Input. Try again\n"; return out;
};

class NonexistentCar
{
public:
	NonexistentCar() {};
};
ostream & operator<<(ostream &out, const NonexistentCar &obj)
{
	out << "ERROR: The car you typed isn't valid.\n"; return out;
}

class userGone
{
public:
	userGone() {};
};
ostream & operator<<(ostream &out, const userGone &obj)
{
	out << "WARNING: Your account was deleted.\n"; return out;
}

// PRINT DA STRUCT STOP
ostream & operator<<(ostream &out, const stop &e) {
	out << "ERROR: " << e.code << " - " << e.name << endl; return out;
};

Agency::Agency() : vehicles(Vehicle("", "", 0, NULL))
{
}

Agency::~Agency()
{
}

/*///////////
MENUS
//////////*/

void Agency::registerUser()
{
	clearScreen();
	Date t; t.setCurrent();
	string type, name, username, password, address;

	menuHeader();
	cout << "|                      ";  grey(); cout << "CREATE ACCOUNT";  white(); cout << "                     |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl; white();
	grey(); cout << " Types of accounts:\n\n";
	blue(); cout << " - Driver: "; grey(); cout << "You need to register your car and host trips.\n           You'll also earn some money.\n\n";
	blue(); cout << " - Passenger: "; grey(); cout << "You can only join existing trips.\n\n\n";
	yellow(); cout << " > "; grey(); cout << "Do you want to register as a Driver? (y/n) "; white(); cin >> type;  cout << endl;

	while (cin.fail() || ((type != "y") && (type != "Y") && (type != "n") && (type != "N")))
	{
		if (cin.eof())
		{
			cin.clear();
			clearScreen();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << " > Invalid choice!" << endl;
		white(); cout << " Please try again: ";
		cin >> type; cout << endl;
	}
	yellow(); cout << "    > "; grey(); cout << "Enter username: "; white(); cin >> username;

	while (cin.fail() || validUser(username)) {

		if (cin.eof())
		{
			cin.clear();
			clearScreen();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "\n Username taken!" << endl;
		white(); cout << " Please type another one: ";
		cin >> username;
	}

	bool a = false;
	while (!a) {
		red(); cout << "\n WARNING: "; grey(); cout << "Password lenght should be at least 5.\n\n";
		yellow(); cout << "    > "; grey(); cout << "Enter password: "; white();
		password = insertPassword();
		yellow(); cout << "\n    > "; grey(); cout << "Confirm password: "; white();
		if (sameString(password, insertPassword()))
			a = true;
		else { red(); cout << "\n Password does not match! Try again.\n\n"; }
	}

	yellow(); cout << "\n\n    > "; grey(); cout << "Enter name: "; white(); cin.ignore(); getline(cin, name);

	while (cin.fail() || name.empty()) {

		if (cin.eof())
		{
			cin.clear();
			clearScreen();
			return;
		}
		cin.clear();
		red(); cout << "\n Not a valid name!" << endl;
		white(); cout << " Please try again: ";
		getline(cin, name);
	}

	yellow(); cout << "\n    > "; grey(); cout << "Enter address: "; white(); cin >> address;

	while (cin.fail() || address.empty()) {

		if (cin.eof())
		{
			cin.clear();
			clearScreen();
			return;
		}
		cin.clear();
		red(); cout << "\n Not a valid input!" << endl;
		white(); cout << " Please try again: ";
		cin >> address;
	}
	address = convertUpper(address);
	if (!checkStop(address)) {
		cin.clear();
		red(); cout << "\n OUT OF OUR OPERATION ZONE!" << endl;
		blue(); cout << "\n Press ENTER to continue ";
		getEnter();
		clearScreen();
		return;
	}

	int nID = getLastId() + 1;

	if ((type == "y") || (type == "Y")) {
		User *u1 = new Driver(nID, name, 0.00, username, password, 0, address, t);
		addUser(u1);
	}
	else {
		User *u1 = new Passenger(nID, name, 0.00, username, password, 0, address, t);
		addUser(u1);
	}

	this->sessionID = nID;
	this->sessionPos = (int)Users.size() - 1;
	yellow(); cout << "\n\n Success! You just created your account!\n"; Sleep(2500); white();

	optionsMainMenu_User();


	clearScreen();
	return;
}

void Agency::loginUser()
{
	clearScreen();
	int id;
	string username, password;

	menuHeader();
	cout << "|                          ";  grey(); cout << "LOGIN";  white(); cout << "                          |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	yellow(); cout << "    > "; grey(); cout << "Enter username: "; white(); cin >> username;

	while (cin.fail() || (validUser(username) == false && username != "admin"))
	{
		if (cin.eof())
		{
			cin.clear();
			clearScreen();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << " Login failed!" << endl;
		white(); cout << " Please try again.\n\n";
		yellow(); cout << "    > "; grey(); cout << "Enter username: "; white(); cin >> username;
	}

	if (username == "admin") {
		yellow(); cout << "\n    > "; grey(); cout << "Enter password: "; white();
		if (insertPassword() == "admin") {
			yellow(); cout << "\n\n > Login as admin succeeded!\n"; Sleep(2000); white();
			optionsMainMenu_Admin();
		}
		else {
			red(); cout << "\n\n> Login failed!" << endl; white();
			Sleep(2000);
			clearScreen();
			return;
		}
	}
	else {
		id = findID(username);

		yellow(); cout << "\n    > "; grey(); cout << "Enter password: "; white();
		password = insertPassword();
		if (validPassword(getPos(id), password)) {
			this->sessionID = id;
			this->sessionPos = getPos(sessionID);
			yellow(); cout << "\n\n > Login succeeded!\n"; Sleep(2000); white();
			optionsMainMenu_User();
		}
		else {
			red(); cout << "\n\n Login failed..." << endl; white();
			Sleep(2000);
			clearScreen();
			return;
		}
	}
	clearScreen();
	return;
}

void Agency::loginGuest()
{
	clearScreen();
	menuHeader();
	cout << "|                       ";  grey(); cout << "TRIP PLANNER - GUEST";  white(); cout << "                      |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(16) << "Code" << setw(33) << "Town" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white(); displayStops();
	blue(); cout << "-----------------------------------------------------------" << endl; white();

	joinTripGuest();
	return;
}

/* ADMINISTRADOR */

int Agency::mainMenu_Admin() {

	clearScreen();
	menuHeader();
	cout << "|~~~                   ";  grey(); cout << "ADMINISTRATION";  white(); cout << "                  ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(18) << "1. Users" << setw(21) << "5. Stops" << endl
		<< setw(24) << "2. Trip Record" << setw(16) << "6. Search" << endl
		<< setw(25) << "3. Transactions" << setw(23) << "7. Run Trip by ID" << endl
		<< setw(24) << "4. Friendships" << setw(30) << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;  white();
	cout << "|~~~                               ";  grey(); cout << "< 0. Logout >";  white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 7) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsMainMenu_Admin() {
	unsigned short int option;

	while (option = mainMenu_Admin())
		switch (option)
		{
		case 1:
			optionsDisplayUsers();
			break;
		case 2:
			menuDisplayRecord();
			break;
		case 3:
			optionsMenuDTrans();
			break;
		case 4:
			menuDisplayBuddies();
			break;
		case 5:
			menuDisplayStops();
			break;
		case 6:
			optionsMenuSearch();
			break;
		case 7:
			menuRunTrip();
			break;
		}
	return;
}


int Agency::menuDisplayUsers() {
	clearScreen();
	menuHeader();
	cout << "|                          ";  grey(); cout << "USERS";  white(); cout << "                          |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;

	grey(); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayUsers();
	blue(); cout << "-----------------------------------------------------------" << endl;  grey();
	cout << setw(24) << "1. Sort by Username" << setw(29) << "2. Sort by Name" << endl;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  grey(); cout << "< 0. Return >";  white(); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option < 0) || ((option > 2)))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsDisplayUsers() {
	unsigned short int option;

	while (option = menuDisplayUsers())
		switch (option)
		{
		case 1:
			menuDisplayUsersByUsername();
			break;
		case 2:
			menuDisplayUsersByName();
			break;
		}
	return;
}


void Agency::menuDisplayUsersByUsername() {

	clearScreen();
	vector<User*> UsersV = Users;

	sort(UsersV.begin(), UsersV.end(), [](User* a, User* b) {return a->getUsername() < b->getUsername(); });

	menuHeader();
	cout << "|                    ";  grey(); cout << "USERS BY USERNAME";  white(); cout << "                    |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	grey(); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;

	white();

	for (unsigned int i = 0; i < UsersV.size(); i++)
	{
		cout << setw(5) << UsersV.at(i)->getID();
		cout << setw(10) << UsersV.at(i)->getUsername();
		cout << setw(20) << UsersV.at(i)->getName();
		cout << setw(10) << setprecision(2) << fixed << UsersV.at(i)->getBalance();

		if (UsersV.at(i)->car())
			cout << setw(10) << "[X]" << endl;
		else cout << setw(10) << "[ ]" << endl;
	}

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getEnter();
	return;
}

void Agency::menuDisplayUsersByName() {

	clearScreen();
	vector<User*> UsersV = Users;
	sort(UsersV.begin(), UsersV.end(), [](User* a, User* b) {return a->getName() < b->getName(); });

	menuHeader();
	cout << "|                      ";  grey(); cout << "USERS BY NAME";  white(); cout << "                      |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	grey(); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl; white();

	for (unsigned int i = 0; i < UsersV.size(); i++)
	{
		cout << setw(5) << UsersV.at(i)->getID();
		cout << setw(10) << UsersV.at(i)->getUsername();
		cout << setw(20) << UsersV.at(i)->getName();
		cout << setw(10) << setprecision(2) << fixed << UsersV.at(i)->getBalance();

		if (UsersV.at(i)->car())
			cout << setw(10) << "[X]" << endl;
		else cout << setw(10) << "[ ]" << endl;
	}

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getEnter();
	return;
}


int Agency::menuSearch() {

	clearScreen();
	menuHeader();
	cout << "|~~~                       ";  grey(); cout << "SEARCH";  white(); cout << "                      ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(18) << "1. Users" << setw(30) << "3. Transactions" << endl
		<< setw(18) << "2. Trips" << endl;

	blue(); cout << "-----------------------------------------------------------" << endl;  white();
	cout << "|~~~                               ";  grey(); cout << "< 0. Return >";  white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 3) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsMenuSearch() {
	unsigned short int option;

	while (option = menuSearch())
		switch (option)
		{
		case 1:
			optionsMenuSearchUser();
			break;
		case 2:
			optionsMenuSearchTrip();
			break;
		case 3:
			optionsMenuSearchTransaction();
			break;
		}
	return;
}


void Agency::menuDisplayBuddies() {
	clearScreen();
	menuHeader();
	cout << "|                       ";  grey(); cout << "FRIENDSHIPS";  white(); cout << "                       |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayBuddies();
	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getEnter();
	return;
}

void Agency::menuDisplayStops() {
	clearScreen();
	menuHeader();
	cout << "|~~~                       ";  grey(); cout << "STOPS";  white(); cout << "                       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(15) << "Code" << setw(35) << "Name" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayStops();
	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getEnter();
	return;
}

void Agency::menuDisplayRecord()
{
	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "TRIP RECORD";  white(); cout << "                   ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(3) << "ID" << setw(8) << "Driver" << setw(8) << "Origin" << setw(10) << "Destiny" << setw(9) << "Date" << setw(11) << "Start" << setw(7) << "End" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayRecord();
	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getEnter();
	return;
}


int Agency::menuDisplayTransactions() {
	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "TRANSACTIONS";  white(); cout << "                  ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(5) << "ID" << setw(27) << "Date" << setw(22) << "Value" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayTransactions();
	blue(); cout << "-----------------------------------------------------------" << endl; white();
	cout << setw(23) << "1. Collect Payment\n";
	blue(); cout << "-----------------------------------------------------------" << endl;  white();
	cout << "|~~~                               ";  grey(); cout << "< 0. Return >";  white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 1) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsMenuDTrans()
{
	unsigned short int option;
	while (option = menuDisplayTransactions())
		switch (option)
		{
		case 1:
			endMonth();
			break;
		}
	return;
}


int Agency::menuSearchUser() {

	clearScreen();
	menuHeader();

	cout << "|~~~                    ";  grey(); cout << "SEARCH USER";  white(); cout << "                    ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(18) << "1. By ID" << setw(30) << "2. By Username" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;  white();
	cout << "|~~~                               ";  grey(); cout << "< 0. Return >";  white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 2) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');

		red(); cout << "> Invalid Input!" << endl;
		white(); cout << "Try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsMenuSearchUser() {
	unsigned short int option;

	while (option = menuSearchUser())
		switch (option)
		{
		case 1:
			menuSearchUserByID();
			break;
		case 2:
			menuSearchUserByUsername();
			break;
		}
	return;
}

void Agency::menuSearchUserByID() {

	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "SEARCH USER";  white(); cout << "                   ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int id, pos;

	yellow(); cout << "\n > "; grey(); cout << "ID of the user you are searching for: "; white(); cin >> id; cout << endl;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid Input!" << endl;
		white(); cout << "Try again: ";
		cin >> id;
	}


	User *u = new User();
	u->setID(id);


	u->setID(id);
	if (sequentialSearch(Users, u) != -1)
		pos = sequentialSearch(Users, u);
	else {
		red(); cerr << "> User with that ID not found." << endl; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}

	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "User Info";  white(); cout << "                     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();
	cout << setw(5) << Users.at(pos)->getID();
	cout << setw(10) << Users.at(pos)->getUsername();
	cout << setw(20) << Users.at(pos)->getName();
	cout << setw(10) << setprecision(2) << fixed << Users.at(pos)->getBalance();

	if (Users.at(pos)->car())
		cout << setw(10) << "[X]" << endl;
	else cout << setw(10) << "[ ]" << endl;

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press any key to go back."; white(); getEnter();
	return;
}

void Agency::menuSearchUserByUsername() {

	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "SEARCH USER";  white(); cout << "                   ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int  pos;
	string input;

	yellow(); cout << "\n > "; grey(); cout << "Username of the user you are searching for: "; white(); cin >> input; cout << endl;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid Input!" << endl;
		white(); cout << "Try again: ";
		cin >> input;
	}


	User *u = new User();
	u->setUsername(input);

	if (sequentialSearch(Users, u) != -1)
		pos = sequentialSearch(Users, u);
	else {
		red(); cerr << "> User with that username not found." << endl; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}

	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "User Info";  white(); cout << "                     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();
	cout << setw(5) << Users.at(pos)->getID();
	cout << setw(10) << Users.at(pos)->getUsername();
	cout << setw(20) << Users.at(pos)->getName();
	cout << setw(10) << setprecision(2) << fixed << Users.at(pos)->getBalance();

	if (Users.at(pos)->car())
		cout << setw(10) << "[X]" << endl;
	else cout << setw(10) << "[ ]" << endl;

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press any key to go back."; white(); getEnter();
	return;
}


int Agency::menuSearchTrip() {

	clearScreen();
	menuHeader();
	cout << "|~~~                   ";  grey(); cout << "SEARCH TRIPS";  white(); cout << "                    ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(22) << "1. By Driver" << setw(26) << "2. By Month" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;  white();
	cout << "|~~~                               ";  grey(); cout << "< 0. Return >";  white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 3) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsMenuSearchTrip() {
	unsigned short int option;

	while (option = menuSearchTrip())
		switch (option)
		{
		case 1:
			menuSearchTripByDriver();
			break;
		case 2:
			menuSearchTripByMonth();
			break;
		}
	return;
}

void Agency::menuSearchTripByDriver() {

	clearScreen();
	menuHeader();
	cout << "|~~~              ";  grey(); cout << "SEARCH TRIPS BY DRIVER";  white(); cout << "               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int id;

	yellow(); cout << "\n > "; grey(); cout << "ID of the driver: "; white(); cin >> id; cout << endl;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid Input!" << endl;
		white(); cout << "Try again: ";
		cin >> id;
	}

	bool b = false;

	for (unsigned int i = 0; i < Trips.size(); i++) {
		if (Trips.at(i).getDriver() == id)
			b = true;
	}

	if (!b)
	{
		red(); cerr << "> Trip with that driver not found." << endl; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}

	clearScreen();
	menuHeader();
	cout << "|~~~              ";  grey(); cout << "SEARCH TRIPS BY DRIVER";  white(); cout << "               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(3) << "ID" << setw(8) << "Driver" << setw(8) << "Origin" << setw(10) << "Destiny" << setw(9) << "Date" << setw(11) << "Start" << setw(7) << "End" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();

	for (unsigned int i = 0; i < Trips.size(); i++)
	{
		if (Trips.at(i).getDriver() == id)
			cout << Trips.at(i);
	}

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press any key to go back."; white(); getEnter();
	return;
}

void Agency::menuSearchTripByMonth() {

	clearScreen();
	menuHeader();
	cout << "|~~~               ";  grey(); cout << "SEARCH TRIPS BY MONTH";  white(); cout << "               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int month;

	yellow(); cout << "\n > "; grey(); cout << "Month of the trip you are searching for: "; white(); cin >> month; cout << endl;

	while (cin.fail() || month < 1 || month > 12)
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid Month!" << endl;
		white(); cout << "Try again: ";
		cin >> month;
	}

	bool b = false;

	for (unsigned int i = 0; i < Trips.size(); i++)
	{
		if (Trips.at(i).getDate().getMonth() == month)
		{
			b = true;
			break;
		}
	}


	if (!b)
	{
		red(); cerr << "> There were no trips in that month." << endl; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}


	clearScreen();
	menuHeader();
	cout << "|~~~               ";  grey(); cout << "SEARCH TRIPS BY MONTH";  white(); cout << "               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(3) << "ID" << setw(8) << "Driver" << setw(8) << "Origin" << setw(10) << "Destiny" << setw(9) << "Date" << setw(11) << "Start" << setw(7) << "End" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();

	for (unsigned int i = 0; i < Trips.size(); i++)
	{
		if (Trips.at(i).getDate().getMonth() == month)
			cout << Trips.at(i);
	}

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press any key to go back."; white(); getEnter();
	return;
}


int Agency::menuSearchTransaction() {

	clearScreen();
	menuHeader();

	cout << "|~~~                ";  grey(); cout << "SEARCH TRANSACTION";  white(); cout << "                 ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(20) << "1. By User" << setw(28) << "2. By Month" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;  white();
	cout << "|~~~                               ";  grey(); cout << "< 0. Return >";  white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;


	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;


	while (cin.fail() || (option > 3) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsMenuSearchTransaction() {
	unsigned short int option;

	while (option = menuSearchTransaction())
		switch (option)
		{
		case 1:
			menuSearchTransactionByUser();
			break;
		case 2:
			menuSearchTransactionByMonth();
			break;
		}
	return;
}

void Agency::menuSearchTransactionByUser() {

	clearScreen();
	menuHeader();
	cout << "|~~~            ";  grey(); cout << "SEARCH TRANSACTION BY USER";  white(); cout << "             ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int id;

	yellow(); cout << "\n > "; grey(); cout << "User ID: "; white(); cin >> id; cout << endl;

	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid Input!" << endl;
		white(); cout << "Try again: ";
		cin >> id;
	}

	bool b = false;

	for (unsigned int i = 0; i < Transactions.size(); i++) {
		if (Transactions.at(i).GetId() == id)
			b = true;
	}

	if (!b)
	{
		red(); cerr << "> Transaction with that User ID not found." << endl; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}

	clearScreen();
	menuHeader();
	cout << "|~~~            ";  grey(); cout << "SEARCH TRANSACTION BY USER";  white(); cout << "             ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(5) << "ID" << setw(25) << "Date" << setw(26) << "Value" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();

	for (unsigned int i = 0; i < Transactions.size(); i++)
	{
		if (Transactions.at(i).GetId() == id)
			cout << Transactions.at(i);
	}

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press any key to go back."; white(); getEnter();
	return;
}

void Agency::menuSearchTransactionByMonth() {

	clearScreen();
	menuHeader();
	cout << "|~~~            ";  grey(); cout << "SEARCH TRANSACTION BY MONTH";  white(); cout << "            ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	int month;

	yellow(); cout << "\n > "; grey(); cout << "Month (by number): "; white(); cin >> month; cout << endl;

	while (cin.fail() || month < 1 || month > 12)
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid Month!" << endl;
		white(); cout << "Try again: ";
		cin >> month;
	}

	bool b = false;

	for (unsigned int i = 0; i < Transactions.size(); i++)
	{
		if (Transactions.at(i).GetDate().getMonth() == month)
		{
			b = true;
			break;
		}
	}


	if (!b)
	{
		red(); cerr << "> There were no transactions in that month." << endl; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}


	clearScreen();
	menuHeader();
	cout << "|~~~            ";  grey(); cout << "SEARCH TRANSACTION BY MONTH";  white(); cout << "            ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(5) << "ID" << setw(25) << "Date" << setw(26) << "Value" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();

	for (unsigned int i = 0; i < Transactions.size(); i++)
	{
		if (Transactions.at(i).GetDate().getMonth() == month)
			cout << Transactions.at(i);
	}

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press any key to go back."; white(); getEnter();
	return;
}


void Agency::menuRunTrip()
{
	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "RUN  TRIP";  white(); cout << "                     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(3) << "ID" << setw(8) << "Driver" << setw(8) << "Origin" << setw(10) << "Destiny" << setw(9) << "Date" << setw(11) << "Start" << setw(7) << "End" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayActiveTrips();
	blue(); cout << "-----------------------------------------------------------" << endl;

	int TripID;
	vector<int> tripsAvailableID;

	for (size_t i = 0; i < ActiveTrips.size(); i++)
	{
		tripsAvailableID.push_back(ActiveTrips.at(i).getID());
	}

	yellow(); cout << "\n > "; grey(); cout << "Choose a trip to run: "; white();
	cin >> TripID; cout << endl;

	while (cin.fail() || (find(tripsAvailableID.begin(), tripsAvailableID.end(), TripID) == tripsAvailableID.end()))
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid trip!" << endl;
		white(); cout << "Try again: ";
		cin >> TripID;
	}

	runTrip(TripID);
	return;
}



/* MENUS USER */

int Agency::mainMenu_User() {
	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "MAIN MENU";  white(); cout << "                     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(30) << "You are logged in as: "; white(); cout << Users.at(getPos(sessionID))->getName() << endl;
	blue(); cout << "-----------------------------------------------------------" << endl; white();

	cout << setw(18) << "1. Account" << setw(30) << "3. Add Buddy" << endl;

	if (Users.at(sessionPos)->car()) { //caso seja driver
		cout << setw(22) << "2. Create Trip" << setw(29) << "4. Car Details\n";
		cout << setw(26) << "5. Scheduled Trips" << endl;
	}
	else { // caso seja passenger
		cout << setw(21) << "2. Join Trip\n";

	}

	blue(); cout << "-----------------------------------------------------------" << endl;  white();
	cout << "|~~~                                ";  grey(); cout << "< 0. Logout >";  white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	int max;

	if (Users.at(sessionPos)->car())
		max = 5;
	else max = 3;

	while (cin.fail() || (option > max) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsMainMenu_User() {
	unsigned short int option;

	try {
		while (option = mainMenu_User())
			switch (option)
			{
			case 1:
				optionsMenuAccount();
				break;
			case 2:
				if (Users.at(sessionPos)->car())
					menuCreateTrip();
				else menuJoinTrip();
				break;
			case 3:
				menuAddBuddy();
				break;
			case 4:
				if (Users.at(sessionPos)->car())
					optionsMenuCar();
				break;
			case 5:
				if (Users.at(sessionPos)->car())
					scheduledTripsMenu();
				break;
			}
	}
	catch (const userGone &e)
	{
		cout << endl;
		red(); cout << e; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
	}

	return;
}


int Agency::menuAccount()
{
	clearScreen();
	menuHeader();
	cout << "|                        ";  grey(); cout << "ACCOUNT";  white(); cout << "                          |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();

	cout << setw(5) << Users.at(getPos(sessionID))->getID();
	cout << setw(10) << Users.at(getPos(sessionID))->getUsername();
	cout << setw(20) << Users.at(getPos(sessionID))->getName();
	cout << setw(10) << setprecision(2) << fixed << Users.at(getPos(sessionID))->getBalance();

	if (Users.at(getPos(sessionID))->car())
		cout << setw(10) << "[X]" << endl;
	else cout << setw(10) << "[ ]" << endl;

	blue(); cout << "-----------------------------------------------------------" << endl;  grey();
	cout << setw(18) << "1. Deposit" << setw(32) << "4. Change Password\n";
	cout << setw(26) << "2. Change Username" << setw(23) << "5. Delete Account\n";
	cout << setw(26) << "3. Change address\n"; white();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  grey(); cout << "< 0. Return >";  white(); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	if (Users.at(getPos(sessionID))->getBalance() <= 0) {
		red(); cout << "WARNING: You need to deposit in your account!\n\n\n"; white();
	}

	typedef
		unordered_set<userPtr, inactivePtr, inactivePtr>::iterator iteratorH;

	userPtr u1;
	u1.user = Users.at(getPos(sessionID));
	pair<iteratorH, bool> res = inactiveUsers.insert(u1);

	if (!res.second) {	//nao inseriu, já existia
		red(); cout << "WARNING: You need to update your address!\n\n\n"; white();
	}
	else {
		iteratorH it = res.first;
		inactiveUsers.erase(it);
	}

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option < 0) || ((option > 4)))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::optionsMenuAccount()
{
	unsigned short int option;
	while (option = menuAccount())
		switch (option)
		{
		case 1:
			deposit();
			break;
		case 2:
			changeUsername();
			break;
		case 3:
			changeAddress();
			break;
		case 4:
			changePassword();
			break;
		case 5:
			deleteAccount();
			break;
		}
	return;
}


void Agency::menuAddBuddy()
{
	clearScreen();
	menuHeader();
	cout << "|                        ";  grey(); cout << "ADD BUDDY";  white(); cout << "                        |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	addBuddy();
	return;
}


void Agency::menuCreateTrip()
{
	clearScreen();
	menuHeader();
	cout << "|                       ";  grey(); cout << "TRIP PLANNER";  white(); cout << "                      |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(16) << "Code" << setw(33) << "Town" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white(); displayStops();
	blue(); cout << "-----------------------------------------------------------" << endl; white();

	try {
		addTrip();
	}
	catch (const NonexistentCar &e)
	{
		cout << endl;
		red(); cout << e; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return;
}

void Agency::menuJoinTrip()
{
	clearScreen();
	menuHeader();
	cout << "|                       ";  grey(); cout << "TRIP PLANNER";  white(); cout << "                      |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(16) << "Code" << setw(33) << "Town" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white(); displayStops();
	blue(); cout << "-----------------------------------------------------------" << endl; white();

	joinTrip();
	return;
}

void Agency::showRecTrips(vector<Trip> recTrips, vector<Trip> buddieTrips, vector<string> stopCodes)
{
	clearScreen();
	menuHeader();
	cout << "|                     ";  grey(); cout << "TRIPS AVAILABLE";  white(); cout << "                     |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	if (buddieTrips.size() != 0) {
		grey(); cout << setw(16) << "Trips with buddies:\n";
		blue(); cout << "-----------------------------------------------------------" << endl;
		grey(); cout << setw(3) << "ID" << setw(8) << "Driver" << setw(8) << "Origin" << setw(10) << "Destiny" << setw(9) << "Date" << setw(11) << "Start" << setw(7) << "End" << endl;
		blue(); cout << "-----------------------------------------------------------" << endl; white();
		for (unsigned int i = 0; i < buddieTrips.size(); i++) {
			cout << buddieTrips.at(i);
		}
	}
	if (recTrips.size() != 0) {
		grey(); cout << setw(16) << "\n\nTrips without buddies:\n";
		blue(); cout << "-----------------------------------------------------------" << endl;
		grey(); cout << setw(3) << "ID" << setw(8) << "Driver" << setw(8) << "Origin" << setw(10) << "Destiny" << setw(9) << "Date" << setw(11) << "Start" << setw(7) << "End" << endl;
		blue(); cout << "-----------------------------------------------------------" << endl; white();
		for (unsigned int i = 0; i < recTrips.size(); i++) {
			cout << recTrips.at(i);
		}
	}

	candidateTrip(recTrips, buddieTrips, stopCodes);
	return;
}

void Agency::showRecTripsGuest(vector<Trip> recTrips, vector<string> stopCodes)
{
	clearScreen();
	menuHeader();
	cout << "|                     ";  grey(); cout << "TRIPS AVAILABLE";  white(); cout << "                     |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(3) << "ID" << setw(8) << "Driver" << setw(8) << "Origin" << setw(10) << "Destiny" << setw(9) << "Date" << setw(11) << "Start" << setw(7) << "End" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl; white();
	for (unsigned int i = 0; i < recTrips.size(); i++) {
		cout << recTrips.at(i);
	}

	candidateTripGuest(recTrips, stopCodes);
	return;
}


/*///////////
FICHEIROS
///////////*/

/* EXTRACT AND SAVE */
void Agency::extractData() {
	extractUsers();
	extractBuddies();
	extractStops();
	extractTransactions();
	extractRecord();
	extractActive();
	extractVehicles();
	extractVehiclesTree();
	extractDistances();
	extractCandidatesQueues();
	generateTable();
}

void Agency::saveData() {
	saveUsers();
	saveBuddies();
	saveTransactions();
	saveRecord();
	saveActive();
	saveTree();
	saveVehicles();
	saveCandidatesQueues();
	return;
}

void Agency::extractUsers()
{
	ifstream Userfile("Users.txt");
	string line;


	if (Userfile.is_open())
	{
		if (!Users.empty()) Users.clear();

		while (getline(Userfile, line))
		{

			size_t pos1 = line.find(";"); //posi�ao 1
			string str1 = line.substr(pos1 + 1); //nome+balance+carro+user+pass+nt
			size_t pos2 = str1.find(";"); //posi�ao 2
			string str2 = str1.substr(pos2 + 1); //balance+carro+user+pass+nt
			size_t pos3 = str2.find(";"); //posi�ao 3
			string str3 = str2.substr(pos3 + 1); //balance+user+pass+nt
			size_t pos4 = str3.find(";"); //posi�ao 4
			string str4 = str3.substr(pos4 + 1); //user+pass+nt
			size_t pos5 = str4.find(";"); //posi�ao 5
			string str5 = str4.substr(pos5 + 1); //pass+nt
			size_t pos6 = str5.find(";"); //posi�ao 6
			string str6 = str5.substr(pos6 + 1); //nt+morada+ultimoacesso
			size_t pos7 = str6.find(";"); //posi?ao 7
			string str7 = str6.substr(pos7 + 1); //morada+ultimoacesso
			size_t pos8 = str7.find(";"); //posi?ao 8

			string ids = line.substr(0, pos1); //string id
			string nome = str1.substr(0, pos2);
			string scar = str2.substr(0, pos3); //string carro
			string sbalance = str3.substr(0, pos4); //string balance
			string user = str4.substr(0, pos5);
			string pass = str5.substr(0, pos6);
			string nt_s = str6.substr(0, pos7); //string nro de trips
			string adress = str7.substr(0, pos8);	//string morada
			string sdate = str7.substr(pos8 + 1);  //string ultimo acesso

			int idi = stoi(ids, nullptr, 10); //passa o id de string para int
			bool bcar;
			if (scar == "1") //passa a tring carro para bool
				bcar = true;
			else bcar = false;

			float balancef = stof(sbalance, NULL); //passa o balance de string para float

			int nt = stoi(nt_s, nullptr, 10); //passa o id de string para int

			Date d(sdate); // passa a data de ultimo acesso de string para Date;

			if (bcar)
			{
				//se o User tiver carro, adiciona um novo driver
				User *d1 = new Driver(idi, nome, balancef, user, pass, nt, adress, sdate);
				Users.push_back(d1);
			}
			else
			{
				//caso contrario adiciona um novo passenger
				User *p1 = new Passenger(idi, nome, balancef, user, pass, nt, adress, sdate);
				Users.push_back(p1);
			}
		}
		Userfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::saveUsers()
{
	ofstream UserFile("Users.txt", ios::trunc);

	if (UserFile.is_open())
	{
		for (unsigned int i = 0; i < Users.size(); i++)
		{
			UserFile << Users.at(i);
		}
		UserFile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::extractBuddies()
{
	ifstream Buddiesfile("Buddies.txt");
	string line;

	if (Buddiesfile.is_open())
	{
		while (getline(Buddiesfile, line))
		{
			size_t pos1 = line.find(";"); //posi?ao 1
			string ids = line.substr(0, pos1); //string id do user

			string buddiess = line.substr(pos1 + 1); //string buddies

			int id = stoi(ids, nullptr, 10); //passa o id do user de string para int

			for (unsigned int i = 0; i < Users.size(); i++)
			{
				if (Users.at(i)->getID() == id) //se o user na posi?ao i ? o user do ficheiro
				{
					if (!Users.at(i)->getBuddies().empty())  Users.at(i)->deleteBuddies(); //se o vetor buddies desse user nao est? vazio, apaga os elementos existentes

					buddiess.append(","); //adiciona ? string buddies uma virgula no final

					while (!(buddiess.empty()))
					{
						int idbuddy = stoi(buddiess.substr(0, buddiess.find_first_of(",")), nullptr, 10); //id do buddy a analisar

						for (unsigned int j = 0; j < Users.size(); j++)
						{
							if (Users.at(j)->getID() == idbuddy)
							{
								Users.at(i)->addBuddy(Users.at(j)); //adiciona esse buddy ao vetor de buddies do user
								buddiess.erase(0, buddiess.find_first_of(",") + 1); //apaga esse buddy e a virgula seguinte da string de buddies
								break;
							}
						}
					}
				}
			}
		}

		Buddiesfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::saveBuddies()
{
	ofstream BuddiesFile("Buddies.txt", ios::trunc);


	if (BuddiesFile.is_open())
	{
		for (unsigned int i = 0; i < Users.size(); i++)
		{
			if (!Users.at(i)->getBuddies().empty()) {
				BuddiesFile << Users.at(i)->getID() << ";";

				string buddies_s;

				for (unsigned int j = 0; j < Users.at(i)->getBuddies().size(); j++)
				{
					buddies_s.append(to_string(Users.at(i)->getBuddies().at(j)->getID()));
					buddies_s.append(",");
				}

				buddies_s.erase(buddies_s.size() - 1, 1); //apaga a ultima virgula
				BuddiesFile << buddies_s << endl;
			}
		}
		BuddiesFile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::extractTransactions() {

	ifstream Transfile("Transactions.txt");
	string line;

	int i = 0;

	if (Transfile.is_open())
	{
		if (!Transactions.empty()) Transactions.clear();

		while (getline(Transfile, line))
		{

			size_t pos1 = line.find(";"); //posi�ao 1
			string str1 = line.substr(pos1 + 1); //id+date+value
			size_t pos2 = str1.find(";"); //posi�ao 2
			string str2 = str1.substr(pos2 + 1); //date+value
			size_t pos3 = str2.find(";"); //posi�ao 3


			string ids = line.substr(0, pos1); //string id
			string date = str1.substr(0, pos2);
			string svalue = str2.substr(0, pos3); //string balance

			int idi = stoi(ids, nullptr, 10); //passa o id de string para int

			float valuef = stof(svalue, NULL); //passa o balance de string para float

			Date d1(date);

			Transactions.push_back(Transaction(idi, d1, valuef)); //cria um novo elemento no vector
			i++;
		}

		Transfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::saveTransactions() {

	ofstream TransFile("Transactions.txt", ios::trunc);

	if (TransFile.is_open())
	{
		for (unsigned int i = 0; i < Transactions.size(); i++)
		{
			Transactions.at(i).save(TransFile);
		}
		TransFile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::extractStops() {

	ifstream Stopsfile("Stops.txt");
	string line;

	if (Stopsfile.is_open())
	{
		while (getline(Stopsfile, line))
		{
			size_t pos1 = line.find(";"); //posi?ao 1
			string code = line.substr(0, pos1); //string codigo da paragem
			string name = line.substr(pos1 + 1); //string nome da paragem

			stop s;
			s.code = code;
			s.name = name;
			stopsAvailable.push_back(s);
		}
		Stopsfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::extractRecord()
{

	ifstream Recfile("Record.txt");
	string line;

	if (Recfile.is_open())
	{
		if (!Trips.empty()) Trips.clear();

		while (getline(Recfile, line))
		{

			size_t pos1 = line.find(";"); //posi�ao 1
			string str1 = line.substr(pos1 + 1); //driver+stopStart+stopEnd+date+horaStart+horaEnd
			size_t pos2 = str1.find(";"); //posi�ao 2
			string str2 = str1.substr(pos2 + 1); //stopStart+stopEnd+date+horaStart+horaEnd
			size_t pos3 = str2.find(";"); //posi�ao 3
			string str3 = str2.substr(pos3 + 1); //stopEnd+date+horaStart+horaEnd
			size_t pos4 = str3.find(";"); //posi�ao 4
			string str4 = str3.substr(pos4 + 1); //date+horaStart+horaEnd
			size_t pos5 = str4.find(";"); //posi�ao 5
			string str5 = str4.substr(pos5 + 1); //horaStart+horaEnd
			size_t pos6 = str5.find(";"); //posi�ao 6

			string idT_s = line.substr(0, pos1); //string id trip
			string idD_s = str1.substr(0, pos2); //string id driver
			string stopStart_s = str2.substr(0, pos3);
			string stopEnd_s = str3.substr(0, pos4);
			string date_s = str4.substr(0, pos5);
			string horaStart_s = str5.substr(0, pos6);
			string horaEnd_s = str5.substr(pos6 + 1);

			int idT_i = stoi(idT_s, nullptr, 10); //passa o idT de string para int
			int idD_i = stoi(idD_s, nullptr, 10); //passa o idD de string para int
			Stop sS(stopStart_s, 0);
			Stop sE(stopEnd_s, 0);
			Date d(date_s);
			Hour hS(horaStart_s);
			Hour hE(horaEnd_s);

			vector <Stop> s = { sS,sE };

			Trip T(idT_i, idD_i, s, d, hS, hE);
			Trips.push_back(T);
		}
		Recfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::saveRecord() {

	ofstream RecordFile("Record.txt", ios::trunc);

	if (RecordFile.is_open())
	{
		for (unsigned int i = 0; i < Trips.size(); i++)
		{
			Trips.at(i).save(RecordFile);
		}
		RecordFile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::extractActive()
{

	ifstream Activefile("ActiveTrips.txt");
	string line;

	if (Activefile.is_open())
	{
		while (getline(Activefile, line))
		{

			size_t pos1 = line.find(";"); //posi�ao 1
			string str1 = line.substr(pos1 + 1); //driver+stops+date+horaStart+horaEnd
			size_t pos2 = str1.find(";"); //posi�ao 2
			string str2 = str1.substr(pos2 + 1); //stops+date+horaStart+horaEnd
			size_t pos3 = str2.find("["); //posi�ao 3
			size_t pos4 = str2.find("]"); //posi�ao 4
			string str3 = str2.substr(pos4 + 2); //date+horaStart+horaEnd
			size_t pos5 = str3.find(";"); //posi�ao 5
			string str4 = str3.substr(pos5 + 1); //horaStart+horaEnd
			size_t pos6 = str4.find(";"); //posi�ao 6

			string idT_s = line.substr(0, pos1); //string id trip
			string idD_s = str1.substr(0, pos2); //string id driver
			string stops_s = str2.substr(pos3 + 1, pos4 - 1); //string stops
			string date_s = str3.substr(0, pos5); //strind data
			string horaStart_s = str4.substr(0, pos6); //string start
			string horaEnd_s = str4.substr(pos6 + 1); //string end

			int idT_i = stoi(idT_s, nullptr, 10); //passa o idT de string para int
			int idD_i = stoi(idD_s, nullptr, 10); //passa o idD de string para int
			Date d(date_s); //passa a data de string para Date
			Hour hS(horaStart_s); //passa a start de string para Hour
			Hour hE(horaEnd_s); //passa a end de string para Hour

			stops_s.append(";"); //adiciona um ; ao fim da string stop

			vector <Stop> vs;

			while (!(stops_s.empty()))
			{

				size_t pos1 = stops_s.find(";");
				string estaparagem = stops_s.substr(0, pos1);



				size_t pos2 = estaparagem.find(","); //posi�ao 1
				string str2 = estaparagem.substr(pos2 + 1); //nro+passengers
				size_t pos3 = str2.find(","); //posi�ao 2
				string str3 = str2.substr(pos3 + 1);
				size_t pos4 = str3.find(")");

				string code = estaparagem.substr(0, pos2);
				string nro_s = str2.substr(0, pos3);
				string passengers_s = str2.substr(pos3 + 2, str3.length() - 2);


				vector <int> vpassengers;

				int nro = stoi(nro_s, nullptr, 10); // passa o numero de lugares de string para int

				if (!passengers_s.empty()) {
					passengers_s.append(",");

					while (!(passengers_s.empty()))
					{
						int pass = stoi(passengers_s.substr(0, passengers_s.find_first_of(",")), nullptr, 10);
						vpassengers.push_back(pass);
						passengers_s.erase(0, passengers_s.find_first_of(",") + 1);
					}
				}

				Stop s(code, nro, vpassengers);
				vs.push_back(s);

				stops_s.erase(0, pos1 + 1); //apaga essa stop e o ; seguinte da lista de stops
			}

			Trip T(idT_i, idD_i, vs, d, hS, hE);
			ActiveTrips.push_back(T);
		}

		Activefile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::saveActive()
{

	ofstream ActiveFile("ActiveTrips.txt", ios::trunc);

	if (ActiveFile.is_open())
	{
		for (unsigned int i = 0; i < ActiveTrips.size(); i++)
		{
			ActiveTrips.at(i).saveAT(ActiveFile);
		}
		ActiveFile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }

}

void Agency::extractVehicles() {
	ifstream Vehiclesfile("Vehicles.txt");
	string line;

	int i = 0;

	if (Vehiclesfile.is_open())
	{
		if (!Cars.empty()) Cars.clear();

		while (getline(Vehiclesfile, line))
		{

			size_t pos1 = line.find(";"); //posicao 1
			string str1 = line.substr(pos1 + 1); //brand+model+seats+year+avai
			size_t pos2 = str1.find(";"); //posicao 2
			string str2 = str1.substr(pos2 + 1); //model+seats+year+avai
			size_t pos3 = str2.find(";"); //posicao 3
			string str3 = str2.substr(pos3 + 1); //seats+year+avai
			size_t pos4 = str3.find(";"); //posicao 4
			string str4 = str3.substr(pos4 + 1); //year+avai
			size_t pos5 = str4.find(";"); //posicao 5


			string brand = line.substr(0, pos1);
			string model = str1.substr(0, pos2);
			string seats = str2.substr(0, pos3);
			string year = str3.substr(0, pos4);
			string numCars = str4.substr(0, pos5);

			int numSeats = stoi(seats, nullptr, 10);
			int yr = stoi(year, nullptr, 10);
			int available = stoi(numCars, nullptr, 10);

			cars someCar;
			someCar.brand = brand;
			someCar.model = model;
			someCar.seats = numSeats;
			someCar.year = yr;
			someCar.available = available;

			Cars.push_back(someCar); //cria um novo elemento no vector
			i++;
		}

		Vehiclesfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

/*/////////
FUNCOES
////////*/

bool Agency::validUser(string username) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (username == Users.at(i)->getUsername())
			return true;
	}
	return false;
}

bool Agency::validPassword(int pos, string password) {
	if (password == Users.at(pos)->getPassword())
		return true;
	return false;
}

int Agency::findID(string username) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (username == Users.at(i)->getUsername())
			return Users.at(i)->getID();
	}
	return -1;
}

int Agency::getPos(int id) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (id == Users.at(i)->getID())
			return i;
	}
	return -1;
}

int Agency::getLastId()
{
	return Users.at(Users.size() - 1)->getID();
}

bool Agency::checkStop(string s) {

	for (size_t i = 0; i < stopsAvailable.size(); i++)
	{
		if (stopsAvailable.at(i).code == s)
			return true;
	}

	return false;
}

bool Agency::notBuddy(string bUsername)
{
	int buddyID = findID(bUsername);

	for (unsigned int i = 0; i < Users.at(sessionPos)->getBuddies().size(); i++) {
		if (buddyID == Users.at(sessionPos)->getBuddies().at(i)->getID())
			return false;
	}
	return true;
}



void Agency::addUser(User * u)
{
	Users.push_back(u);
}

void Agency::addBuddy() {
	string buddyUsername, type;

	yellow(); cout << "\n > "; grey(); cout << "Please enter the username of the user\n   you want to add as buddy: "; white(); cin >> buddyUsername;

	//caso o username inserido: nao exista OU seja o proprio OU ja seja buddy -> NAO ADICIONA
	if ((!validUser(buddyUsername)) || (buddyUsername == Users.at(sessionPos)->getUsername()) || (notBuddy(buddyUsername) == false)) {
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		red();
		if (buddyUsername == Users.at(sessionPos)->getUsername())
			cout << "\n Sorry, you can't add yourself!\n";
		else {
			if (notBuddy(buddyUsername) == false)
				cout << "\n This user already is your buddy!\n";
			else
				cout << "\n Sorry, user not found!\n";
		}
		white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}

	//tudo ok
	else {
		green(); cout << "\n The following user was found:\n\n";
		grey(); cout << setw(10) << "ID" << setw(20) << "User" << setw(20) << "Name" << endl;
		blue(); cout << "-----------------------------------------------------------" << endl; white();
		cout << setw(10) << Users.at(getPos(findID(buddyUsername)))->getID() << setw(20) << Users.at(getPos(findID(buddyUsername)))->getUsername() << setw(23) <<
			Users.at(getPos(findID(buddyUsername)))->getName() << endl;

		yellow(); cout << "\n > "; grey(); cout << "You want to add this user as your buddy? (y/n) "; white(); cin >> type; cout << endl;

		while (cin.fail() || ((type != "y") && (type != "Y") && (type != "n") && (type != "N")))
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			red(); cout << "> Invalid choice!" << endl;
			white(); cout << "Please try again: ";
			cin >> type; cout << endl;
		}

		if (type == "Y" || type == "y") {

			Users.at(sessionPos)->addBuddy(Users.at(getPos(findID(buddyUsername)))); //adiciona buddy ao user
			Users.at(getPos(findID(buddyUsername)))->addBuddy(Users.at(sessionPos));//adiciona user como buddy ao buddy 
			yellow(); cout << " Success! This user is now your buddy!\n"; white();
			Sleep(2000);
			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}
		else {
			red(); cout << " You did not add a new buddy...\n"; white();
			Sleep(2000);
			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}
	}
	return;
}

void Agency::deposit()
{
	float value;
	yellow(); cout << "\n > "; grey(); cout << "Insert the amount of money you want to deposit in your account (max 200): "; white();
	cin >> value;

	if (cin.eof())
	{
		cin.clear();
		return;
	}

	if ((value > 0) && (value < 201)) {
		Users.at(sessionPos)->deposit(value);
		yellow(); cout << "\n Success!"; white();
	}
	else {
		red(); cout << "\n Not a valid value!"; white();
	}
	Sleep(2000);
	cin.clear();
	cin.ignore(1000, '\n');
	return;
}

void Agency::endMonth() {

	typename vector<User *>::iterator it;
	float totalMonth = 0;

	for (it = Users.begin(); it != Users.end(); it++) {

		totalMonth += (*it)->payment();

		//criar e adicionar transacao
		int id = (*it)->getID();
		Date currentDate;
		currentDate.setCurrent();

		Transaction trans(id, currentDate, totalMonth);
		Transactions.push_back(trans);
		(*it)->resetTrips();
		totalMonth = 0;
	}

	yellow(); cout << "\n Success! All the transactions were made!\n"; white();
	Sleep(2000);
	cin.clear();
	cin.ignore(1000, '\n');
	return;
}

void Agency::handleInput()
{
	cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	throw Error(0);
}

time_t Agency::getUnixCode(Date &d, Hour &h) {

	time_t ret;
	struct tm info;

	info.tm_year = d.getYear() - 1900;
	info.tm_mon = d.getMonth() - 1;
	info.tm_mday = d.getDay();
	info.tm_hour = h.getHour();
	info.tm_min = h.getMinutes();
	info.tm_sec = 0;
	info.tm_isdst = -1;

	ret = (int)mktime(&info);
	return ret;
}


/*/////////////
TRIP RELATED
/////////////*/

void Agency::addTrip() {

	time_t startUnix, endUnix;
	vector<Stop> tripPlan;
	vector<string> stopCodes;
	string stopCode;
	Date tripDate, currentDate;
	//initialize current system's date
	currentDate.setCurrent();
	Hour endHour, startHour, currentHour;
	//initialize current system's date
	currentHour.setCurrent();
	BSTItrIn<Vehicle> it(vehicles);
	int numSeats;

	if (hasCar() == 0) {
		red(); cout << "\n WARNING: "; white();
		cout << "You can't create a trip! Please add a car first!\n";
		cout << " To do so, go to 'Car Details' in the main menu.\n";
		cout << "\n Press enter to go back.\n";
		getEnter();
	}
	else {

		if (hasCar() != 1) {
			white(); cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			grey(); cout << setw(15) << "Brand" << setw(18) << "Model" << setw(20) << "Year" << endl;
			blue(); cout << "-----------------------------------------------------------" << endl;
			white();
		}

		while (!it.isAtEnd()) {
			Vehicle v1 = it.retrieve();

			if (v1.getUser()->getID() == sessionID) {
				if (hasCar() == 1) {
					numSeats = getNumSeats(v1.getModel(), v1.getYear()) - 1;
				}
				else {
					cout << setw(15) << v1.getBrand() << setw(18) << v1.getModel() << setw(20) << v1.getYear() << endl;
				}
			}

			it.advance();
		}

		if (hasCar() != 1) {
			yellow(); cout << "\n > "; grey(); cout << "Choose your vehicle.\n ";
			yellow(); cout << "\n > "; grey(); cout << "Vehicle's model: "; white();

			string model;
			cin.ignore(); getline(cin, model);

			yellow(); cout << "\n > "; grey(); cout << "Vehicle's year: "; white();
			int year;
			cin >> year;

			it = vehicles;
			int flag = 0;

			while (!it.isAtEnd()) {
				Vehicle v1 = it.retrieve();

				if (v1.getModel() == model && v1.getYear() == year && v1.getUser()->getID() == sessionID) {
					numSeats = getNumSeats(v1.getModel(), v1.getYear()) - 1;
					flag = 1;
					break;
				}
				it.advance();
			}

			if (!flag)
				throw NonexistentCar();
		}

		int stopNumber = 1;

		yellow(); cout << "\n > "; grey(); cout << "Please enter your stops (CTRL + Z to END):\n"; white();


		while (1)
		{
			cout << " Stop # " << stopNumber << " : ";

			cin >> stopCode;
			stopCode = convertUpper(stopCode);

			//enquanto o utilizador nao inserir ctrl+z
			if (!cin.eof())
			{
				try
				{
					//se a paragem existe
					if (checkStop(stopCode)) {
						//se a paragem ja foi inserida lanca a excecao
						if (find(stopCodes.begin(), stopCodes.end(), stopCode) != stopCodes.end()) {
							throw RepeatedStop(stopCode);
						}
						//caso corra tudo bem, adiciona ao vetor
						else {
							stopCodes.push_back(stopCode);
							stopNumber++;
						}
					}
					//se nao existe lanca a excecao
					else
						throw NonexistentStop(stopCode);

				}
				catch (const NonexistentStop &e)
				{
					red(); cout << e; white();
				}
				catch (const RepeatedStop &e)
				{
					red(); cout << e; white();
				}
			}

			//fim da introducao das paragens
			else {

				if (stopCodes.size() < 2)
				{
					red(); cout << "ERROR: You did not enter at least 2 distinct stops.\n"; white();
					Sleep(2500);
					clearScreen();
				}
				else
				{
					//id da nova viagem a ser criada
					int idTrip = (int)Trips.size() + 1;

					//vetor de estrutura STOP
					for (unsigned int i = 0; i < stopCodes.size(); i++) {
						tripPlan.push_back(Stop(stopCodes.at(i), numSeats));
					}

					while (1) {

						try
						{
							//data da viagem
							int day, month, year;
							yellow(); cout << "\n > "; grey(); cout << "Enter your trip's date:\n "; cin.clear(); white();
							cout << "> Day: "; cin >> day; if (cin.fail()) handleInput();
							cout << " > Month: "; cin >> month; if (cin.fail()) handleInput();
							cout << " > Year: "; cin >> year; if (cin.fail()) handleInput();

							tripDate.setDay(day); tripDate.setMonth(month); tripDate.setYear(year);

							if (cin.eof())
							{
								cin.clear();
								return;
							}

							//se a data nao � valida
							if (!tripDate.valid())
							{
								throw InvalidDate(tripDate);
							}
							else if (tripDate < currentDate)
							{
								throw PassedDate(day, month, year);
							}
							else if (currentDate.daysBetween(tripDate) > 365)
							{
								throw TooLong(day, month, year);
							}
							else
							{
								break;
							}

						}
						catch (const InvalidDate &e)
						{
							red(); cout << e; white();
						}
						catch (const PassedDate &e)
						{
							red(); cout << e; white();
						}
						catch (const TooLong &e)
						{
							red(); cout << e; white();
						}
						catch (const Error &e)
						{
							red(); cout << e; white();
						}

					}

					while (1) {

						time_t actualTime = getUnixCode(currentDate, currentHour);

						try
						{

							//hora inicio
							int hourS, minutesS;
							yellow(); cout << "\n > "; grey(); cout << "Enter starting time:\n "; cin.clear(); white();
							cout << "> Hour: "; cin >> hourS; if (cin.fail()) handleInput();
							cout << " > Minutes: "; cin >> minutesS; if (cin.fail()) handleInput();

							if (cin.eof())
							{
								cin.clear();
								return;
							}

							startHour.setHour(hourS); startHour.setMinutes(minutesS);

							startUnix = getUnixCode(tripDate, startHour);

							if (startHour.validHour() == false)
							{
								throw InvalidHour(startHour.getHour(), startHour.getMinutes());
							}
							else if (startUnix <= actualTime + 3600 && startUnix >= actualTime)	//if entered time is in less than 1 hour = 3600 seconds
							{
								red(); cout << "ERROR: Departure time must be at least 1 hour from now.\n"; white();
							}
							else if (startUnix < actualTime)
							{
								throw PassedHour(startHour.getHour(), startHour.getMinutes());
							}
							else
							{
								break;
							}
						}
						catch (const InvalidHour &e)
						{
							red(); cout << e; white();
						}
						catch (const PassedHour &e)
						{
							red(); cout << e; white();
						}
						catch (const Error &e)
						{
							red(); cout << e; white();
						}
					}

					while (1) {

						try
						{
							//hora fim
							int hourE, minutesE;
							yellow(); cout << "\n > "; grey(); cout << "Please enter finish time:\n "; cin.clear(); white();

							cout << "> Hour: "; cin >> hourE; if (cin.fail()) handleInput();
							cout << " > Minutes: "; cin >> minutesE; if (cin.fail()) handleInput();

							if (cin.eof())
							{
								cin.clear();
								return;
							}

							endHour.setHour(hourE); endHour.setMinutes(minutesE);

							endUnix = getUnixCode(tripDate, endHour);

							if (!endHour.validHour())
							{
								throw InvalidHour(endHour.getHour(), endHour.getMinutes());
							}
							else if (endUnix < startUnix)
							{
								red(); cout << "ERROR: The finish time can not be previous to the departure time.\n"; white();
							}
							else
							{
								break;
							}
						}
						catch (const InvalidHour &e)
						{
							red(); cout << e; white();
						}
					}


					//criacao do objeto trip
					Trip trp(idTrip, sessionID, tripPlan, tripDate, startHour, endHour);
					Trips.push_back(trp);
					ActiveTrips.push_back(trp);

					Users.at(sessionPos)->setNtrips(); //adiciona uma viagem

					green();  cout << "\n\nStops and number of seats successfully added to your trip.\n\n"; white();
					Sleep(2500);
				}
				break;
			}
		}







	}

	return;
}

void Agency::joinTrip()
{
	vector<string> stopCodes;
	string stopCode;
	Date tripDate, currentDate;
	vector<Trip> possibleTrips; // que verificam data, origem e destino
	vector<Trip> recTrips; //trips recomendadas, que tem espaco (originam da de cima)
	vector<Trip> buddieTrips; //trips recomendadas com buddies
							  //initialize current system's date
	currentDate.setCurrent();
	Hour endHour, startHour, currentHour;
	//initialize current system's date
	currentHour.setCurrent();

	int stopNumber = 1;

	yellow(); cout << " > "; grey(); cout << "Please enter your trip:\n"; white();

	while (1)
	{
		if (stopNumber == 1) {
			cout << " From: ";
			cin >> stopCode;
			stopCode = convertUpper(stopCode);
		}
		else if (stopNumber == 2) {
			cout << " To: ";
			cin >> stopCode;
			stopCode = convertUpper(stopCode);
		}

		if (cin.eof())
		{
			cin.clear();
			return;
		}

		//enquanto nao tiver sido inserido o inicio e o fim (duas stops)
		if (stopCodes.size() != 2)
		{
			try
			{
				//se a paragem existe
				if (checkStop(stopCode)) {
					//se a paragem ja foi inserida lanca a excecao
					if (find(stopCodes.begin(), stopCodes.end(), stopCode) != stopCodes.end()) {
						throw RepeatedStop(stopCode);
					}
					//caso corra tudo bem, adiciona ao vetor
					else {
						stopCodes.push_back(stopCode);
						stopNumber++;
					}
				}
				//se nao existe lan�a a exce�ao
				else
					throw NonexistentStop(stopCode);

			}
			catch (const NonexistentStop &e)
			{
				red(); cout << e; white();
			}
			catch (const RepeatedStop &e)
			{
				red(); cout << e; white();
			}
		}

		//fim da introducao das paragens
		else {

			while (1) {

				try
				{
					//data da viagem
					int day, month, year;
					yellow(); cout << "\n > "; grey(); cout << "Enter your trip's date:\n "; cin.clear(); white();
					cout << "> Day: "; cin >> day; if (cin.fail()) handleInput();
					cout << " > Month: "; cin >> month; if (cin.fail()) handleInput();
					cout << " > Year: "; cin >> year; if (cin.fail()) handleInput();

					if (cin.eof())
					{
						cin.clear();
						return;
					}

					tripDate.setDay(day); tripDate.setMonth(month); tripDate.setYear(year);

					//se a data nao � valida
					if (!tripDate.valid())
					{
						throw InvalidDate(tripDate);
					}
					else if (tripDate < currentDate)
					{
						throw PassedDate(day, month, year);
					}
					else if (currentDate.daysBetween(tripDate) > 365)
					{
						throw TooLong(day, month, year);
					}
					else
					{
						break;
					}

				}
				catch (const InvalidDate &e)
				{
					red(); cout << e; white();
				}
				catch (const PassedDate &e)
				{
					red(); cout << e; white();
				}
				catch (const TooLong &e)
				{
					red(); cout << e; white();
				}
				catch (const Error &e)
				{
					red(); cout << e; white();
				}

			}

			possibleTrips = searchTrip(stopCodes, tripDate); //vetor de viagens possiveis (tendo em conta data, origem e destino APENAS

			if (possibleTrips.size() == 0) { //caso nao haja viagens possiveis
				red(); cout << "\n Sorry, no trip found!\n"; white();
				Sleep(2000);
				cin.clear();
				cin.ignore(1000, '\n');
				return;
			}
			else { //caso haja viagens, verificar se ha lugares disponiveis

				recTrips = availableTrips(possibleTrips, stopCodes);
				if (recTrips.size() == 0) { //caso todos os lugares ja estejam ocupados
					red(); cout << "\n Sorry, there is no space left in any trip!\n"; white();
					Sleep(2000);
					cin.clear();
					cin.ignore(1000, '\n');
					return;
				}
				else { //caso haja lugares

					for (unsigned int i = 0; i < recTrips.size(); i++) { //verificar se ha buddies em comum
						if (hasBuddies(recTrips.at(i)) == true) { //divide trips em recomendadas com buddies e sem buddies
							buddieTrips.push_back(recTrips.at(i));
							recTrips.erase(recTrips.begin() + i);
							i--;
						}
					}
					showRecTrips(recTrips, buddieTrips, stopCodes); //mostra trips recomendadas, com buddies e sem
				}
			}
			break;
		}
	}
	return;
}

vector<Trip> Agency::searchTrip(vector<string> stopCodes, Date tripDate)
{
	vector<Trip> possibleTrips;
	string first = stopCodes.at(0); //origem pretendida
	string last = stopCodes.at(1); //destino pretendido

	for (unsigned int i = 0; i < ActiveTrips.size(); i++) {
		if (ActiveTrips.at(i).getDate() == tripDate) { //caso seja a data prentendida
			for (unsigned int j = 0; j < ActiveTrips.at(i).getStops().size(); j++) { //procurar origem
				if (first == ActiveTrips.at(i).getStops().at(j).getCode()) { //encontrou origem
					for (unsigned int k = j + 1; k < ActiveTrips.at(i).getStops().size(); k++) { //procurar destino
						if (last == ActiveTrips.at(i).getStops().at(k).getCode()) //encontrou destino
							possibleTrips.push_back(ActiveTrips.at(i)); // adiciona viagem possivel ao vetor possibleTrips
					}
				}
			}
		}
	}

	return possibleTrips; //vetor nulo caso nao haja viagens
}

vector<Trip> Agency::availableTrips(vector<Trip> possibleTrips, vector<string> stopCodes)
{
	vector<Trip> spaceTrips; // vetor de trips com espaco suficiente para juntar passageiro

	for (unsigned int i = 0; i < possibleTrips.size(); i++) {
		if (availableSpace(possibleTrips.at(i), stopCodes) == true)
			spaceTrips.push_back(possibleTrips.at(i));
	}
	return spaceTrips;
}

bool Agency::availableSpace(Trip possibleTrip, vector<string> stopCodes) { //recebe uma viagem e trajeto do user, e ve se ha lugares disponiveis
	int idi, idf, stopCounter, a = 0;
	string first = stopCodes.at(0); //origem pretendida
	string last = stopCodes.at(1); //destino pretendido

	for (unsigned int j = 0; j < possibleTrip.getStops().size(); j++) {
		if (first == possibleTrip.getStops().at(j).getCode()) //obtem id inicial ; idi
			idi = j;
		if (last == possibleTrip.getStops().at(j).getCode()) //obtem id final ; idf
			idf = j;
	}

	stopCounter = idf - idi;
	for (idi; idi < idf; idi++) { //verifica se ha lugares disponiveis em cada paragem, menos na final, visto que user sai nessa
		if (possibleTrip.getStops().at(idi).getAvailableSeats() > 0)
			a++;
	}

	if (a == stopCounter)
		return true;
	else return false;
}

bool Agency::hasBuddies(Trip recTrip)
{
	vector<int> userBuddies; //ids de todos os buddies do user
	vector<int> tripids; //ids do driver e passageiros presentes em toda a viagem
	int numBuddies = 0;

	for (unsigned int i = 0; i < Users.at(sessionPos)->getBuddies().size(); i++) {
		userBuddies.push_back(Users.at(sessionPos)->getBuddies().at(i)->getID());
	}

	for (unsigned int i = 0; i < recTrip.getStops().size(); i++) {
		for (unsigned int j = 0; j < recTrip.getStops().at(i).getPassengers().size(); j++) {
			if (find(tripids.begin(), tripids.end(), recTrip.getStops().at(i).getPassengers().at(j)) != tripids.end())
				tripids.push_back(recTrip.getStops().at(i).getPassengers().at(j));
		}
	}

	tripids.push_back(recTrip.getDriver());

	for (unsigned int i = 0; i < userBuddies.size(); i++) {
		if (find(tripids.begin(), tripids.end(), userBuddies.at(i)) != tripids.end())
			numBuddies++;
	}

	if (numBuddies > 0)
		return true;
	else return false;
}

void Agency::chooseTrip(vector<Trip> recTrips, vector<Trip> buddieTrips, vector<string> stopCodes)
{
	int idi, idf;
	vector<int> allTrips; //vetor com ids de todas as trips disponiveis como opcao
	int id;

	string first = stopCodes.at(0); //origem pretendida
	string last = stopCodes.at(1); //destino pretendido

	yellow(); cout << "\n > "; grey(); cout << "Enter the id of the trip you would like to join: "; white(); cin >> id; cout << endl;

	for (unsigned int i = 0; i < recTrips.size(); i++) {
		allTrips.push_back(recTrips.at(i).getID());
	}
	for (unsigned int i = 0; i < buddieTrips.size(); i++) {
		allTrips.push_back(buddieTrips.at(i).getID());
	}

	while (cin.fail() || find(allTrips.begin(), allTrips.end(), id) == allTrips.end())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> id;
	}

	for (unsigned int i = 0; i < ActiveTrips.size(); i++) {
		if (id == ActiveTrips.at(i).getID()) {
			for (unsigned int j = 0; j < ActiveTrips.at(i).getStops().size(); j++) {
				if (first == ActiveTrips.at(i).getStops().at(j).getCode()) //obtem id inicial ; idi
					idi = j;
				if (last == ActiveTrips.at(i).getStops().at(j).getCode()) //obtem id final ; idf
					idf = j;
			}

			for (idi; idi < idf; idi++) { //verifica se ha lugares disponiveis em cada paragem, menos na final, visto que user sai nessa
				ActiveTrips.at(i).setStops(idi, sessionID); //decrementa e adiciona user a viagem nas stops
			}
		}
	}

	Users.at(sessionPos)->setNtrips(); //adiciona uma viagem
	yellow(); cout << "\n Success! You were added to the trip!\n"; white();
	Sleep(2000);
	cin.clear();
	cin.ignore(1000, '\n');
	return;
}

void Agency::joinTripGuest() {

	vector<string> stopCodes;
	string stopCode;
	Date tripDate, currentDate;
	vector<Trip> possibleTrips; // que verificam data, origem e destino
	vector<Trip> recTrips; //trips recomendadas, que tem espaco (originam da de cima)
						   //initialize current system's date
	currentDate.setCurrent();
	Hour endHour, startHour, currentHour;
	//initialize current system's date
	currentHour.setCurrent();

	int stopNumber = 1;

	yellow(); cout << " > "; grey(); cout << "Please enter your trip:\n"; white();

	while (1)
	{
		if (stopNumber == 1) {
			cout << " From: ";
			cin >> stopCode;
			stopCode = convertUpper(stopCode);
		}
		else if (stopNumber == 2) {
			cout << " To: ";
			cin >> stopCode;
			stopCode = convertUpper(stopCode);
		}

		if (cin.eof())
		{
			cin.clear();
			clearScreen();
			return;
		}

		//enquanto nao tiver sido inserido o inicio e o fim (duas stops)
		if (stopCodes.size() != 2)
		{
			try
			{
				//se a paragem existe
				if (checkStop(stopCode)) {
					//se a paragem ja foi inserida lanca a excecao
					if (find(stopCodes.begin(), stopCodes.end(), stopCode) != stopCodes.end()) {
						throw RepeatedStop(stopCode);
					}
					//caso corra tudo bem, adiciona ao vetor
					else {
						stopCodes.push_back(stopCode);
						stopNumber++;
					}
				}
				//se nao existe lan�a a exce�ao
				else
					throw NonexistentStop(stopCode);

			}
			catch (const NonexistentStop &e)
			{
				red(); cout << e; white();
			}
			catch (const RepeatedStop &e)
			{
				red(); cout << e; white();
			}
		}

		//fim da introducao das paragens
		else {

			while (1) {

				try
				{
					//data da viagem
					int day, month, year;
					yellow(); cout << "\n > "; grey(); cout << "Enter your trip's date:\n "; cin.clear(); white();
					cout << "> Day: "; cin >> day; if (cin.fail()) handleInput();
					cout << " > Month: "; cin >> month; if (cin.fail()) handleInput();
					cout << " > Year: "; cin >> year; if (cin.fail()) handleInput();

					if (cin.eof())
					{
						cin.clear();
						clearScreen();
						return;
					}

					tripDate.setDay(day); tripDate.setMonth(month); tripDate.setYear(year);

					//se a data nao � valida
					if (!tripDate.valid())
					{
						throw InvalidDate(tripDate);
					}
					else if (tripDate < currentDate)
					{
						throw PassedDate(day, month, year);
					}
					else if (currentDate.daysBetween(tripDate) > 365)
					{
						throw TooLong(day, month, year);
					}
					else
					{
						break;
					}

				}
				catch (const InvalidDate &e)
				{
					red(); cout << e; white();
				}
				catch (const PassedDate &e)
				{
					red(); cout << e; white();
				}
				catch (const TooLong &e)
				{
					red(); cout << e; white();
				}
				catch (const Error &e)
				{
					red(); cout << e; white();
				}

			}

			possibleTrips = searchTrip(stopCodes, tripDate); //vetor de viagens possiveis (tendo em conta data, origem e destino APENAS

			if (possibleTrips.size() == 0) { //caso nao haja viagens possiveis
				red(); cout << "\n Sorry, no trip found!\n"; white();
				Sleep(2000);
				cin.clear();
				cin.ignore(1000, '\n');
				return;
			}
			else { //caso haja viagens, verificar se ha lugares disponiveis

				recTrips = availableTrips(possibleTrips, stopCodes);
				if (recTrips.size() == 0) { //caso todos os lugares ja estejam ocupados
					red(); cout << "\n Sorry, there is no space left in any trip!\n"; white();
					Sleep(2000);
					cin.clear();
					cin.ignore(1000, '\n');
					return;
				}
				else { //caso haja lugares
					showRecTripsGuest(recTrips, stopCodes); //mostra trips recomendadas
				}
			}
			break;
		}
	}
	return;
}

void Agency::chooseTripGuest(vector<Trip> recTrips, vector<string> stopCodes)
{
	int posI, posF, tripID, stopCounter;
	int guestID = -1;
	float payment;
	vector<int> allTrips; //vetor com ids de todas as trips disponiveis como opcao

	string first = stopCodes.at(0); //origem pretendida
	string last = stopCodes.at(1); //destino pretendido

	yellow(); cout << "\n > "; grey(); cout << "Enter the id of the trip you would like to join: "; white(); cin >> tripID; cout << endl;

	for (unsigned int i = 0; i < recTrips.size(); i++) {
		allTrips.push_back(recTrips.at(i).getID());
	}

	while (cin.fail() || find(allTrips.begin(), allTrips.end(), tripID) == allTrips.end())
	{
		if (cin.eof())
		{
			clearScreen();
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> tripID;
	}

	for (unsigned int i = 0; i < ActiveTrips.size(); i++) {
		if (tripID == ActiveTrips.at(i).getID()) {
			for (unsigned int j = 0; j < ActiveTrips.at(i).getStops().size(); j++) {
				if (first == ActiveTrips.at(i).getStops().at(j).getCode()) //obtem id inicial ; idi
					posI = j;
				if (last == ActiveTrips.at(i).getStops().at(j).getCode()) //obtem id final ; idf
					posF = j;
			}

			stopCounter = posF - posI;

			for (posI; posI < posF; posI++) { //verifica se ha lugares disponiveis em cada paragem, menos na final, visto que user sai nessa
				ActiveTrips.at(i).setStops(posI, guestID); //decrementa e adiciona guest a viagem nas stops
			}
		}
	}

	payment = stopCounter * (float)1.5;
	green(); cout << "\n You'll have to pay: "; white(); cout << payment << endl;
	Sleep(2000);

	//criar e adicionar transacao
	Date currentDate;
	currentDate.setCurrent();

	Transaction trans(guestID, currentDate, payment);
	Transactions.push_back(trans);

	yellow(); cout << "\n Success! You were added to the trip!\n"; white();
	Sleep(2000);
	cin.clear();
	cin.ignore(1000, '\n');
	clearScreen();
	return;
}


void Agency::runTrip(int tripID) {

	Trip t;
	int tripIndex;
	vector<int> usersWhoExited;
	vector<int> usersWhoExitedAfter;

	for (unsigned int i = 0; i < ActiveTrips.size(); i++)
	{
		if (ActiveTrips[i].getID() == tripID) {
			t = ActiveTrips[i];
			tripIndex = i;
		}
	}

	vector<Stop> stops = ActiveTrips.at(tripIndex).getStops();

	for (size_t stopIt = 0; stopIt < stops.size(); stopIt++)
	{
		usersWhoExited = usersWhoExitedAfter;
		usersWhoExitedAfter.clear();

		string currentStop = stops.at(stopIt).getCode();

		clearScreen();
		menuHeader();
		cout << "|                     ";  grey(); cout << "RUNNING TRIP #" << ActiveTrips[tripIndex].getID();  white(); cout << "                     |" << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		grey(); cout << setw(10) << "Origin" << setw(20) << "Destiny" << setw(20) << "Driver" << setw(11) << endl;
		blue(); cout << "-----------------------------------------------------------" << endl;
		white(); cout << setw(9) << ActiveTrips[tripIndex].getOrigin() << setw(19) << ActiveTrips.at(tripIndex).getDestination() << setw(25) << Users[getPos(t.getDriver())]->getName() << setw(11) << endl;
		blue(); cout << "-----------------------------------------------------------" << endl;

		yellow(); cout << "\n > "; grey(); cout << "CURRENT STOP: "; white(); cout << currentStop << endl;



		if (stopIt == stops.size() - 1)
		{
			yellow(); cout << "\n\n > Final destination reached!\n"; white();
		}
		else {

			vector<int> usersNextStop = stops.at(stopIt + 1).getPassengers();

			//saida de passageiros
			unsigned int indice = 0;
			for (unsigned int indice = 0; indice < stops.at(stopIt).getPassengers().size(); indice++)
			{
				int id = stops.at(stopIt).getPassengers().at(indice);
				unsigned int vectorPos = getPos(id);
				int CHECK = sequentialSearchNoPointer(usersNextStop, id);  //verifica que se esta na proxima paragem

																		   //se o ID � positivo, procura-se no vetor Users
				if (id > 0)
				{

					//se esta na proxima paragem nao acontece nada
					if (CHECK == -1)
					{	//se nao esta é porque saiu nesta
						usersWhoExitedAfter.push_back(id);
					}
				}

				//se o ID � negativo, procura-se no vetor de Guest
				if (id < 0)
				{
					//se está na proxima paragem continua e atualiza-se o numero de stops do guest
					if (CHECK == -1)
					{
						//se nao esta é porque saiu nesta
						usersWhoExitedAfter.push_back(id);
					}

				}
			}

			//se houve alguma saida de passageiros
			if (usersWhoExited.size() != 0)
			{
				yellow(); cout << "\n > "; grey(); cout << "Passengers who left: "; white();
				for (size_t j = 0; j < usersWhoExited.size(); j++)
				{
					int id = usersWhoExited.at(j);

					if (id > 0)
					{
						cout << Users[getPos(usersWhoExited[j])]->getName();
					}
					else
					{
						cout << "Guest";
					}

					if (j != usersWhoExited.size() - 1)
					{
						cout << ", ";
					}
				}

				cout << endl;

			}

			int newPass = 0;
			if (stopIt != 0) {

				vector<int> usersPreviousStop = stops[stopIt - 1].getPassengers();

				///entrada de passageiros///
				vector<int> usersOnBoard;

				for (size_t k = 0; k < stops[stopIt].getPassengers().size(); k++)
				{
					int id = stops[stopIt].getPassengers()[k];
					unsigned int vectorPos = getPos(id);

					int CHECK = sequentialSearchNoPointer(usersPreviousStop, id);

					//se o ID � positivo, procura-se no vetor Users
					if (id > 0)
					{
						if (CHECK == -1)
						{
							//se nao estava é porque entrou nesta
							usersOnBoard.push_back(id);
						}
					}

					//se o ID � negativo, procura-se no vetor de Guest
					if (id < 0)
					{
						if (CHECK == -1)
						{
							//se nao esta é porque entrou nesta
							usersOnBoard.push_back(id);
						}

					}
				}
				newPass = (int)usersOnBoard.size();
				//se houve alguma entrada de passageiros

				yellow(); cout << "\n > "; grey(); cout << "Passengers who got in: "; white();

				if (usersOnBoard.size() != 0)
				{
					for (size_t l = 0; l < usersOnBoard.size(); l++)
					{
						if (usersOnBoard[l] > 0)
						{
							cout << Users[getPos(usersOnBoard[l])]->getName();
						}
						else
						{
							cout << "Guest";
						}

						if (l != usersOnBoard.size() - 1)
						{
							cout << ", ";
						}
					}
				}
				else {
					cout << "none.";
				}
				cout << endl;

				if (usersWhoExited.size() == 0 && newPass == 0)
				{
					yellow(); cout << "\n\n > "; grey(); cout << "No passengers exited or entered at this stop.\n"; white();
				}
			}

			if (stops.at(stopIt).getPassengers().size() != 0)
			{
				yellow(); cout << "\n > "; grey(); cout << "Passengers onboard: "; white();

				for (size_t i = 0; i < stops.at(stopIt).getPassengers().size(); i++)
				{
					if (stops.at(stopIt).getPassengers()[i] == -1)
					{
						cout << "Guest";
					}
					else
					{
						cout << Users[getPos(stops.at(stopIt).getPassengers().at(i))]->getName();
					}

					if (i != stops.at(stopIt).getPassengers().size() - 1)
					{
						cout << ", ";
					}
				}
			}
			else
			{
				grey(); cout << "\n\n > No passengers onboard.\n"; white();
			}

			//espera pelo input da tecla Enter para passar a proxima paragem
			green(); cout << "\n\n -> ENTER to go to the next stop <-"; white();
			getEnter();
		}
	}

	ActiveTrips.erase(ActiveTrips.begin() + tripIndex);
	Sleep(2000);
	cin.clear();
	cin.ignore(1000, '\n');
	return;
}

/*/////////
DISPLAYS
/////////*/

void Agency::displayUsers() {

	for (unsigned int i = 0; i < Users.size(); i++)
	{
		cout << setw(5) << Users.at(i)->getID();
		cout << setw(10) << Users.at(i)->getUsername();
		cout << setw(20) << Users.at(i)->getName();
		cout << setw(10) << setprecision(2) << fixed << Users.at(i)->getBalance();

		if (Users.at(i)->car())
			cout << setw(10) << "[X]" << endl;
		else cout << setw(10) << "[ ]" << endl;
	}

	return;
}

void Agency::displayBuddies() {

	for (unsigned int i = 0; i < Users.size(); i++)
	{
		grey(); cout << setw(10) << "   USER"; blue(); cout << " | ";
		white(); cout << Users.at(i)->getName() << endl;
		grey(); cout << setw(10) << "BUDDIES"; blue(); cout << " | ";
		white();
		for (unsigned int j = 0; j < Users.at(i)->getBuddies().size(); j++)
		{
			cout << Users.at(i)->getBuddies().at(j)->getName();

			if (j != Users.at(i)->getBuddies().size() - 1)
			{
				cout << ", ";
			}

		}

		cout << endl << endl;
	}

	return;
}

void Agency::displayTransactions() {

	sort(Transactions.begin(), Transactions.end(), [](Transaction &a, Transaction &b) {return a.GetDate() < b.GetDate(); });

	for (unsigned int i = 0; i < Transactions.size(); i++)
	{
		cout << Transactions.at(i);
	}

	return;
}

void Agency::displayStops() {
	for (unsigned int i = 0; i < stopsAvailable.size(); i++)
	{
		cout << setw(15) << stopsAvailable.at(i).code;
		cout << setw(35) << stopsAvailable.at(i).name;
		cout << endl;
	}
	return;
}

void Agency::displayRecord()
{
	for (unsigned int i = 0; i < Trips.size(); i++)
	{
		cout << Trips.at(i);
	}
}
void Agency::displayActiveTrips()
{
	for (size_t i = 0; i < ActiveTrips.size(); i++)
	{
		cout << ActiveTrips.at(i);
	}
}

void Agency::optionsMenuCar()
{
	unsigned short int option;

	try {
		while (option = MenuCar())
			switch (option)
			{
			case 1:
				rentCar();
				break;
			case 2:
				discardCar();
				break;
			case 3:
				tradeCar();
				break;
			case 4:
				searchCar();
				break;
			}
	}
	catch (const NonexistentCar &e)
	{
		cout << endl;
		red(); cout << e; white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
	}

	return;
}

int Agency::MenuCar()
{
	clearScreen();
	menuHeader();
	cout << "|                       ";  grey(); cout << "CAR DETAILS";  white(); cout << "                       |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;

	grey(); cout << setw(15) << "Brand" << setw(18) << "Model" << setw(20) << "Year" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayCar();
	blue(); cout << "-----------------------------------------------------------" << endl;  grey();
	cout << setw(21) << "1. Rent Car" << setw(29) << "3. Trade Car" << endl;
	cout << setw(24) << "2. Discard Car" << setw(27) << "4. Search Car" << endl;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  grey(); cout << "< 0. Return >";  white(); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option < 0) || ((option > 4)))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}
	return option;
}

void Agency::displayCar() {
	int counter = 0;
	BSTItrIn<Vehicle> it(vehicles);

	while (!it.isAtEnd()) {
		Vehicle v1 = it.retrieve();
		User *driver = v1.getUser();

		if (driver->getID() == sessionID) {
			cout << setw(15) << v1.getBrand() << setw(18) << v1.getModel() << setw(20) << v1.getYear() << endl;
			counter++;
		}
		it.advance();
	}

	if (counter == 0) {
		red();
		cout << setw(13) << "Warning: "; white();
		cout << "You have no cars! Please add one!\n";
	}

	return;
}

void Agency::displayCars() {
	for (unsigned int i = 0; i < Cars.size(); i++) {
		if (Cars.at(i).available > 0)
			cout << setw(12) << Cars.at(i).brand << setw(20) << Cars.at(i).model << setw(10) << Cars.at(i).seats << setw(11) << Cars.at(i).year << endl;
	}
	return;
}

bool Agency::carExists(string model, int year) {
	for (unsigned int i = 0; i < Cars.size(); i++) {
		if (model == Cars.at(i).model && year == Cars.at(i).year) {
			if (Cars.at(i).available > 0)
				return true;
			else return false;
		}
	}
	return false;
}

int Agency::hasCar()
{
	BSTItrIn<Vehicle> it(vehicles);
	int counter = 0;

	while (!it.isAtEnd()) {
		Vehicle v1 = it.retrieve();

		if (v1.getUser()->getID() == sessionID) {
			counter++;
		}
		it.advance();
	}

	return counter;
}

void Agency::rentCar() {
	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "VEHICLES";  white(); cout << "                      ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(12) << "Brand" << setw(18) << "Model" << setw(14) << "Seats" << setw(9) << "Year" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayCars();
	blue(); cout << "-----------------------------------------------------------" << endl << endl;

	yellow(); cout << " > "; grey(); cout << "Please enter vehicle's model: "; white();

	string model;
	cin.ignore(); getline(cin, model);

	yellow(); cout << " > "; grey(); cout << "Please enter vehicle's year: "; white();
	int year;
	cin >> year;

	BSTItrIn<Vehicle> it(vehicles);
	int flag = 1;

	while (!it.isAtEnd()) {
		Vehicle v1 = it.retrieve();

		if (v1.getUser()->getID() == sessionID && v1.getModel() == model && v1.getYear() == year) {
			flag = 0;
			break;
		}
		it.advance();
	}

	if (!carExists(model, year) || !flag)
		throw NonexistentCar();
	else {

		string brand;

		for (unsigned int i = 0; i < Cars.size(); i++) {
			if (model == Cars.at(i).model && year == Cars.at(i).year) {
				brand = Cars.at(i).brand;
				Cars.at(i).available--;
			}
		}

		Vehicle v1 = Vehicle(brand, model, year, Users.at(sessionPos));
		addVehicle(v1);

		yellow(); cout << "\n Success!\n"; white();

	}

	Sleep(2000);
	return;
}

void Agency::discardCar()
{
	BSTItrIn<Vehicle> it(vehicles);
	int flag = 0;

	yellow(); cout << "\n > "; grey(); cout << "In order to remove, we need the following information. ";
	yellow(); cout << "\n > "; grey(); cout << "Vehicle's model: "; white();

	string model;
	cin.ignore(); getline(cin, model);

	yellow(); cout << "\n > "; grey(); cout << "Vehicle's year: "; white();
	int year;
	cin >> year;

	while (!it.isAtEnd()) {
		Vehicle v1 = it.retrieve();

		if (v1.getModel() == model && v1.getYear() == year) {
			vehicles.remove(v1);

			for (unsigned int i = 0; i < Cars.size(); i++) {
				if (Cars.at(i).model == model && Cars.at(i).year == year)
					Cars.at(i).available++;
			}

			flag = 1;
			break;
		}
		it.advance();
	}

	if (!flag)
		throw NonexistentCar();
	else {
		yellow(); cout << "\n Success!\n"; white();
	}

	Sleep(2000);
	return;
}

void Agency::tradeCar()
{
	string username, type;
	BSTItrIn<Vehicle> it(vehicles);

	yellow(); cout << "\n > "; grey(); cout << "Please enter the username of the user\n   you want to trade cars with: "; white(); cin >> username;

	//caso o username inserido: nao exista OU seja o proprio OU nao seja driver -> NAO ADICIONA
	if ((!validUser(username)) || (username == Users.at(sessionPos)->getUsername()) || (Users.at(getPos(findID(username)))->car() == false)) {
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		red();
		if (username == Users.at(sessionPos)->getUsername())
			cout << "\n Sorry, you can't trade with yourself!\n";
		else {
			if (!validUser(username))
				cout << "\n Sorry, user not found!\n";
			else
				cout << "\n This user isn't a driver!\n";

		}
		white();
		Sleep(2000);
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}

	//tudo ok
	else {
		green(); cout << "\n The following user was found:\n\n";
		grey(); cout << setw(10) << "ID" << setw(20) << "User" << setw(20) << "Name" << endl;
		blue(); cout << "-----------------------------------------------------------" << endl; white();
		cout << setw(10) << Users.at(getPos(findID(username)))->getID() << setw(20) << Users.at(getPos(findID(username)))->getUsername() << setw(23) <<
			Users.at(getPos(findID(username)))->getName() << endl;

		yellow(); cout << "\n > "; grey(); cout << "You want to trade your car with this user? (y/n) "; white(); cin >> type; cout << endl;

		while (cin.fail() || ((type != "y") && (type != "Y") && (type != "n") && (type != "N")))
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			red(); cout << "> Invalid choice!" << endl;
			white(); cout << "Please try again: ";
			cin >> type; cout << endl;
		}

		if (type == "Y" || type == "y") {

			int flag = 0;

			yellow(); cout << "\n > "; grey(); cout << "In order to trade, we need the following information. ";
			yellow(); cout << "\n > "; grey(); cout << "Vehicle's model: "; white();

			string model;
			cin.ignore(); getline(cin, model);

			yellow(); cout << "\n > "; grey(); cout << "Vehicle's year: "; white();
			int year;
			cin >> year;

			while (!it.isAtEnd()) {
				Vehicle v1 = it.retrieve();

				if (v1.getModel() == model && v1.getYear() == year) {
					vehicles.remove(v1);
					v1.setUser(Users.at(getPos(findID(username))));
					vehicles.insert(v1);
					flag = 1;
					break;
				}
				it.advance();
			}

			if (!flag)
				throw NonexistentCar();
			else {
				yellow(); cout << "\n Success!\n"; white();
			}

			Sleep(2000);
			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}
		else {
			red(); cout << " Trade cancelled...\n"; white();
			Sleep(2000);
			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}
	}
	return;
}

void Agency::searchCar()
{
	BSTItrIn<Vehicle> it(vehicles);
	int flag = 0;
	string brand, model;

	yellow(); cout << "\n > "; grey(); cout << "Vehicle's brand: "; white();
	cin.ignore(); getline(cin, brand);

	yellow(); cout << "\n > "; grey(); cout << "Vehicle's model: "; white();
	getline(cin, model);

	yellow(); cout << "\n > "; grey(); cout << "Vehicle's year: "; white();
	int year;
	cin >> year;

	while (!it.isAtEnd()) {
		Vehicle v1 = it.retrieve();

		if (v1.getBrand() == brand && v1.getModel() == model && v1.getYear() == year) {
			flag = 1;
			break;
		}
		it.advance();
	}

	if (flag) {
		it = vehicles;
		cout << endl << endl;
		grey(); cout << setw(10) << "Brand" << setw(10) << "Model" << setw(10) << "Year" << setw(15) << "User" << endl;
		blue(); cout << "-----------------------------------------------------------" << endl; white();

		while (!it.isAtEnd()) {
			Vehicle v1 = it.retrieve();

			if (v1.getBrand() == brand && v1.getModel() == model && v1.getYear() == year) {

				cout << setw(10) << v1.getBrand() << setw(10) << v1.getModel() << setw(10) << v1.getYear() << setw(20) << v1.getUser()->getName() << endl;
			}
			it.advance();
		}

		blue(); cout << "-----------------------------------------------------------" << endl;
		red(); cout << "\n Press enter to go back."; white(); getEnter();
	}
	else
		throw NonexistentCar();

	return;
}


void Agency::addInactive(User *us1)
{
	userPtr ptr1;
	ptr1.user = us1;
	inactiveUsers.insert(ptr1);
}

void Agency::generateTable()
{
	Date today; today.setCurrent();

	for (size_t i = 0; i < Users.size(); i++)
	{
		if (Users[i]->getLastAccess().daysBetween(today) > 5)
			addInactive(Users[i]);
	}
}

tabHInactive Agency::getInactive() const
{
	return tabHInactive();
}
int Agency::getNumSeats(string model, int year)
{
	for (unsigned int i = 0; i < Cars.size(); i++) {
		if (model == Cars.at(i).model && year == Cars.at(i).year)
			return Cars.at(i).seats;
	}
	return 0;
}

void Agency::extractVehiclesTree() {
	ifstream Vehiclesfile("VehiclesTree.txt");
	string line;

	if (Vehiclesfile.is_open())
	{
		if (!vehicles.isEmpty()) vehicles.makeEmpty();

		while (getline(Vehiclesfile, line))
		{

			size_t pos1 = line.find(";"); //posicao 1
			string str1 = line.substr(pos1 + 1); //brand+model+year+driver
			size_t pos2 = str1.find(";"); //posicao 2
			string str2 = str1.substr(pos2 + 1); //model+year+driver
			size_t pos3 = str2.find(";"); //posicao 3
			string str3 = str2.substr(pos3 + 1); //year+driver
			size_t pos4 = str3.find(";"); //posicao 4


			string brand = line.substr(0, pos1);
			string model = str1.substr(0, pos2);
			string year = str2.substr(0, pos3);
			string driver = str3.substr(0, pos4);

			int yr = stoi(year, nullptr, 10);
			int id = stoi(driver, nullptr, 10);

			User *someDriver = new User;

			for (unsigned int i = 0; i < Users.size(); i++) {
				if (Users.at(i)->getID() == id) {
					someDriver = Users.at(i);
					break;
				}
			}

			Vehicle v1 = Vehicle(brand, model, yr, someDriver);
			addVehicle(v1);
		}

		Vehiclesfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::saveTree() {
	ofstream File("VehiclesTree.txt", ios::trunc);
	BSTItrIn<Vehicle> it(vehicles);

	if (File.is_open())
	{

		while (!it.isAtEnd()) {
			Vehicle v1 = it.retrieve();
			User *driver = v1.getUser();

			File << v1.getBrand() << ";" << v1.getModel() << ";" << v1.getYear() << ";" << driver->getID() << endl;

			it.advance();
		}
		File.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }

	return;
}

void Agency::saveVehicles()
{
	ofstream File("Vehicles.txt", ios::trunc);

	if (File.is_open())
	{
		for (unsigned int i = 0; i < Cars.size(); i++) {

			File << Cars.at(i).brand << ";" << Cars.at(i).model << ";" << Cars.at(i).seats << ";" << Cars.at(i).year << ";" << Cars.at(i).available << endl;
		}
		File.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }

	return;
}

void Agency::changeAddress()
{
	yellow(); cout << "\n Current Address: "; grey(); cout << Users.at(getPos(sessionID))->getAddress() << endl;
	cin.clear();
	cin.ignore(1000, '\n');
	string address;
	yellow(); cout << "\n > "; grey(); cout << "Insert your new address: "; white();
	cin >> address;
	address = convertUpper(address);

	while (cin.fail() || !checkStop(address)) {

		if (cin.eof())
		{
			cin.clear();
			clearScreen();
			return;
		}
		cin.clear();
		red(); cout << "\n Not valid for our operation zone!" << endl;
		white(); cout << " Please type another one: ";
		cin >> address;
	}

	Users.at(sessionPos)->setAdress(address);

	typedef
		unordered_set<userPtr, inactivePtr, inactivePtr>::iterator iteratorH;

	userPtr u1;
	u1.user = Users.at(getPos(sessionID));
	pair<iteratorH, bool> res = inactiveUsers.insert(u1);

	if (!res.second) {	//nao inseriu, já existia
		iteratorH it = res.first;
		inactiveUsers.erase(it);
	}
	else {
		iteratorH it = res.first;
		inactiveUsers.erase(it);
	}

	Date t; t.setCurrent();
	Users.at(sessionPos)->setLastAccess(t);

	yellow(); cout << "\n Success!\n"; white();
	Sleep(2000);
	return;
}

void Agency::changeUsername()
{
	cin.clear();
	cin.ignore(1000, '\n');
	string username;
	yellow(); cout << "\n > "; grey(); cout << "Insert your new username: "; white();
	getline(cin, username);

	while (cin.fail() || validUser(username)) {

		if (cin.eof())
		{
			cin.clear();
			clearScreen();
			return;
		}
		cin.clear();
		red(); cout << "\n Username taken!" << endl;
		white(); cout << " Please type another one: ";
		cin >> username;
	}

	Users.at(sessionPos)->setUsername(username);
	yellow(); cout << "\n Success!\n"; white();
	Sleep(2000);
	return;
}

void Agency::changePassword()
{
	cin.clear();
	cin.ignore(1000, '\n');
	string password;
	bool a = false;
	while (!a) {
		red(); cout << "\n WARNING: "; grey(); cout << "Password lenght should be at least 5.\n\n";
		yellow(); cout << "    > "; grey(); cout << "Enter password: "; white();
		password = insertPassword();
		yellow(); cout << "\n    > "; grey(); cout << "Confirm password: "; white();
		if (sameString(password, insertPassword()))
			a = true;
		else { red(); cout << "\n Password does not match! Try again.\n\n"; }
	}

	Users.at(sessionPos)->setPassword(password);

	yellow(); cout << "\n Success!\n"; white();
	Sleep(2000);
	return;
}

void Agency::deleteAccount()
{
	string type;

	red(); cout << "\n WARNING: "; grey(); cout << "Do you really want to delete your account? (y/n)\n";
	yellow(); cout << "    > "; white(); cin >> type;

	while (cin.fail() || ((type != "y") && (type != "Y") && (type != "n") && (type != "N")))
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> type; cout << endl;
	}

	if (type == "Y" || type == "y") {

		//delete cars from data and free them
		if (hasCar() > 0) {

			BSTItrIn<Vehicle> it(vehicles);

			while (!it.isAtEnd()) {
				Vehicle v1 = it.retrieve();

				if (v1.getUser()->getID() == sessionID) {

					for (unsigned int i = 0; i < Cars.size(); i++) {
						if (Cars.at(i).model == v1.getModel() && Cars.at(i).year == v1.getYear())
							Cars.at(i).available++;
					}

					vehicles.remove(v1);
					it = vehicles;
				}
				else
					it.advance();
			}
		}

		//delete as buddy
		for (unsigned int i = 0; i < Users.size(); i++) {
			Users.at(i)->removeBuddy(sessionID);
		}

		//TODO: ELIMINAR USER - tanto pode ser driver como nao - da candidates queue or wtv

		//caso seja driver, elimina viagens ativas
		if (Users.at(sessionPos)->car()) {
			for (unsigned int i = 0; i < ActiveTrips.size(); i++) {
				if (ActiveTrips.at(i).getDriver() == sessionID) {
					ActiveTrips.erase(ActiveTrips.begin() + i);
					i--;
				}
			}
		}

		//por fim, elimina user
		Users.erase(Users.begin() + sessionPos);

		throw userGone();
	}

	return;
}


void Agency::extractDistances() {

	ifstream Distancesfile("Distances.txt");
	string line;

	if (Distancesfile.is_open())
	{

		while (getline(Distancesfile, line))
		{

			size_t pos1 = line.find(";"); //posi?ao 1
			string str1 = line.substr(pos1 + 1); //pnt2 + km
			size_t pos2 = str1.find(";"); //posi?ao 1

			string pnt1 = line.substr(0, pos1);
			string pnt2 = str1.substr(0, pos2);
			string skm = str1.substr(pos2 + 1); //string de km


			float fkm = stof(skm, NULL); //passa os km de string para float 

			distanceStruct d;
			d.pnt1 = pnt1;
			d.pnt2 = pnt2;
			d.km = fkm;
			distancesVec.push_back(d);
		}
		Distancesfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }
}

void Agency::extractCandidatesQueues() {

	ifstream Queuesfile("CandidatesQueues.txt");
	string line;

	if (Queuesfile.is_open())
	{
		while (getline(Queuesfile, line))
		{

			size_t pos1 = line.find(";"); //posi�ao 1
			string str1 = line.substr(pos1 + 1); //id do driver + (id , distance)*
			size_t pos2 = str1.find(";"); //posi�ao 2
			string str2 = str1.substr(pos2 + 1);//(id , distance)*

			string sidtrip = line.substr(0, pos1); //string id da trip
			string siddriver = str1.substr(0, pos2); //string id do driver

			string spasseng = str2;

			int iidtrip = stoi(sidtrip, nullptr, 10); //passa o id de string para int
			int iiddriver = stoi(siddriver, nullptr, 10); //passa o id de string para int

			spasseng.append(";");

			vector <CandidateTrip> v1;

			while (!spasseng.empty()) {

				size_t pos0 = spasseng.find(";");

				size_t pos3 = spasseng.find(",");
				string str3 = spasseng.substr(pos3 + 1);//distance+init+end
				size_t pos4 = str3.find(",");
				string str4 = str3.substr(pos4 + 1); //init+end
				size_t pos5 = str4.find(",");
				string str5 = str4.substr(pos5 + 1); //end+....
				size_t pos6 = str5.find(";");

				string sidpass = spasseng.substr(0, pos3);
				string distance = str3.substr(0, pos4);
				string initS = str4.substr(0, pos5);
				string endS = str5.substr(0, pos6);


				int idpass = stoi(sidpass);
				float dist = stof(distance, NULL);

				spasseng.erase(0, pos0 + 1);

				for (int i = 0; i < Users.size(); i++) {

					if (Users.at(i)->getID() == iiddriver) { // encontra o driver

						if (idpass == -1) {

							CandidateTrip ct1(NULL, Users.at(i), dist, initS, endS);
							v1.push_back(ct1);

						}
						else {

							for (int k = 0; k < Users.size(); k++) {

								if (Users.at(k)->getID() == idpass) { // encontra o passenger
									CandidateTrip ct1(Users.at(k), Users.at(i), dist, initS, endS);
									v1.push_back(ct1);

								}
							}
						}
					}
				}
			}

			for (int m = 0; m < ActiveTrips.size(); m++) {

				if (ActiveTrips.at(m).getID() == iidtrip) { // encontra a viagem
					for (int j = 0; j < v1.size(); j++) {
						ActiveTrips.at(m).addCandidate(v1.at(j));
					}
				}
			}

		}

		Queuesfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }

}

void Agency::saveCandidatesQueues() {

	ofstream Queuesfile("CandidatesQueues.txt");

	if (Queuesfile.is_open())
	{
		for (unsigned int i = 0; i < ActiveTrips.size(); i++)
		{
			priority_queue <CandidateTrip> temp = ActiveTrips.at(i).getCandidateQueue();

			if (!temp.empty()) { //se nao está inicialmente vazia


				Queuesfile << ActiveTrips.at(i).getID() << ";" << temp.top().getDriver()->getID();

				while (!temp.empty()) {

					Queuesfile << ";";

					if (temp.top().getPassanger() == NULL)
						Queuesfile << "-1";
					else Queuesfile << temp.top().getPassanger()->getID();

					Queuesfile << "," << temp.top().getDistance() << "," << temp.top().getInitStop() << "," << temp.top().getEndStop();
					temp.pop();
				}
				Queuesfile << endl;
			}
		}
		Queuesfile.close();
	}
	else { red(); cerr << "ERROR: unable to open file." << endl; white(); }

}

float Agency::distanceBetweenTwoPoints(string pnt1, string pnt2) {

	for (int i = 0; i < distancesVec.size(); i++) {

		if ((distancesVec.at(i).pnt1 == pnt1 && distancesVec.at(i).pnt2 == pnt2) ||
			(distancesVec.at(i).pnt1 == pnt2 && distancesVec.at(i).pnt2 == pnt1))
		{
			return distancesVec.at(i).km;
		}
	}

	return 0;

}

float Agency::distanceRide(vector<string> v1, string pnt1) {

	int j;

	for (int i = 0; i < v1.size(); i++) {
		if (v1.at(i) == pnt1) {
			j = i;
			break;
		}
	}

	float sum = 0;

	for (int k = 0; k + 1 <= j; k++) {
		sum = sum + distanceBetweenTwoPoints(v1.at(k), v1.at(k + 1));
	}

	return sum;

}

void Agency::candidateTrip(vector<Trip> recTrips, vector<Trip> buddieTrips, vector<string> stopCodes) {

	//int idi, idf;
	vector<int> allTrips; //vetor com ids de todas as trips disponiveis como opcao
	int id;

	string first = stopCodes.at(0); //origem pretendida
	string last = stopCodes.at(1); //destino pretendido

	yellow(); cout << "\n > "; grey(); cout << "Enter the id of the trip you would like to candidate: "; white(); cin >> id; cout << endl;

	for (unsigned int i = 0; i < recTrips.size(); i++) {
		allTrips.push_back(recTrips.at(i).getID());
	}
	for (unsigned int i = 0; i < buddieTrips.size(); i++) {
		allTrips.push_back(buddieTrips.at(i).getID());
	}

	while (cin.fail() || find(allTrips.begin(), allTrips.end(), id) == allTrips.end())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> id;
	}

	for (unsigned int i = 0; i < Users.size(); i++) {
		if (Users.at(i)->getID() == sessionID) { //encontra passenger

			for (unsigned int j = 0; j < ActiveTrips.size(); j++) {
				if (ActiveTrips.at(j).getID() == id) { //encontra trip

					for (unsigned int k = 0; k < Users.size(); k++) {
						if (Users.at(k)->getID() == ActiveTrips.at(j).getDriver()) { //encontra driver

							vector <int> IDqueue;
							priority_queue <CandidateTrip> temp = ActiveTrips.at(j).getCandidateQueue();
							while (!temp.empty()) {
								IDqueue.push_back(temp.top().getPassanger()->getID());
								temp.pop();
							}
							if (find(IDqueue.begin(), IDqueue.end(), sessionID) != IDqueue.end()) {
								red(); cout << "> You have already candidated to this trip!" << endl; grey();
								Sleep(2000);
								cin.clear();
								cin.ignore(1000, '\n');
								return;
							}

							vector <string> v1;

							for (unsigned int m = 0; m < ActiveTrips.at(j).getStops().size(); m++) {
								v1.push_back(ActiveTrips.at(j).getStops().at(m).getCode());
							}

							float dist = distanceRide(v1, first);

							CandidateTrip ct1(Users.at(i), Users.at(k), dist, first, last);

							ActiveTrips.at(j).addCandidate(ct1);

						}
					}
				}
			}
		}
	}

	yellow(); cout << "\n Success! You were added to the trip candidates queue!\n"; white();


	Sleep(2000);
	cin.clear();
	cin.ignore(1000, '\n');
	return;

}

void Agency::candidateTripGuest(vector<Trip> recTrips, vector<string> stopCodes) {


	int posI, posF, stopCounter;
	int guestID = -1;
	float payment;
	//int idi, idf;
	vector<int> allTrips; //vetor com ids de todas as trips disponiveis como opcao
	int id;

	string first = stopCodes.at(0); //origem pretendida
	string last = stopCodes.at(1); //destino pretendido

	yellow(); cout << "\n > "; grey(); cout << "Enter the id of the trip you would like to candidate: "; white(); cin >> id; cout << endl;

	for (unsigned int i = 0; i < recTrips.size(); i++) {
		allTrips.push_back(recTrips.at(i).getID());
	}

	while (cin.fail() || find(allTrips.begin(), allTrips.end(), id) == allTrips.end())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> id;
	}


	for (unsigned int j = 0; j < ActiveTrips.size(); j++) {
		if (ActiveTrips.at(j).getID() == id) { //encontra trip

			for (unsigned int k = 0; k < Users.size(); k++) {
				if (Users.at(k)->getID() == ActiveTrips.at(j).getDriver()) { //encontra driver

					vector <string> v1;

					for (unsigned int m = 0; m < ActiveTrips.at(j).getStops().size(); m++) {
						v1.push_back(ActiveTrips.at(j).getStops().at(m).getCode());

						if (first == ActiveTrips.at(j).getStops().at(m).getCode())
							posI = m;
						if (last == ActiveTrips.at(j).getStops().at(m).getCode())
							posF = m;
					}

					stopCounter = posF - posI;

					float dist = distanceRide(v1, first);

					CandidateTrip ct1(NULL, Users.at(k), dist, first, last);

					ActiveTrips.at(j).addCandidate(ct1);

				}
			}
		}
	}


	payment = stopCounter*(float)1.5;
	//payment = 6.5;
	green(); cout << "\n You'll have to pay: "; white(); cout << payment << endl;
	Sleep(2000);

	//criar e adicionar transacao
	Date currentDate;
	currentDate.setCurrent();

	Transaction trans(guestID, currentDate, payment);
	Transactions.push_back(trans);

	yellow(); cout << "\n Success! You were added to the trip candidates queue!\n"; white();
	Sleep(2000);
	cin.clear();
	cin.ignore(1000, '\n');
	clearScreen();
	return;

}

void Agency::scheduledTripsMenu() {

	clearScreen();
	menuHeader();
	cout << "|                       ";  grey(); cout << "YOUR TRIPS";  white(); cout << "                      |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(9) << "Trip ID" << setw(15) << "From" << setw(15) << "To" << setw(15) << "Date" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();

	vector <int> driverTrips; //vetor de id de trips deste driver

	for (int i = 0; i < ActiveTrips.size(); i++) {
		if (ActiveTrips.at(i).getDriver() == sessionID) {

			driverTrips.push_back(ActiveTrips.at(i).getID());

			cout << setw(7) << ActiveTrips.at(i).getID() << setw(17) <<
				ActiveTrips.at(i).getStops().at(0).getCode() << setw(15) <<
				ActiveTrips.at(i).getStops().at(ActiveTrips.at(i).getStops().size() - 1).getCode() << setw(10) <<
				ActiveTrips.at(i).getDate().getDay() << "/" << ActiveTrips.at(i).getDate().getMonth() << "/" << ActiveTrips.at(i).getDate().getYear() << endl;
		}
	}

	blue(); cout << "-----------------------------------------------------------" << endl; white();

	int idtrip;
	yellow(); cout << "\n > "; grey(); cout << "Type the ID of the trip you want to manage: "; white();
	cin >> idtrip;

	while (cin.fail() || (find(driverTrips.begin(), driverTrips.end(), idtrip) == driverTrips.end()))
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> idtrip;
	}

	clearScreen();
	menuHeader();
	cout << "|                       ";  grey(); cout << "TRIP MANAGER";  white(); cout << "                      |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(9) << "Trip ID" << setw(15) << "From" << setw(15) << "To" << setw(15) << "Date" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();

	for (int i = 0; i < ActiveTrips.size(); i++) {
		if (ActiveTrips.at(i).getID() == idtrip) {
			cout << setw(7) << ActiveTrips.at(i).getID() << setw(17) <<
				ActiveTrips.at(i).getStops().at(0).getCode() << setw(15) <<
				ActiveTrips.at(i).getStops().at(ActiveTrips.at(i).getStops().size() - 1).getCode() << setw(10) <<
				ActiveTrips.at(i).getDate().getDay() << "/" << ActiveTrips.at(i).getDate().getMonth() << "/" << ActiveTrips.at(i).getDate().getYear() << endl;
			break;
		}
	}

	blue(); cout << "-----------------------------------------------------------" << endl;  grey();
	cout << setw(21) << "1. Cancel Trip" << setw(29) << "2. Choose Passengers" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;  grey();
	cout << endl << "Attention: you can only choose passangers once.\n"; white();

	int option;
	cout << endl << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option < 1) || ((option > 2)))
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		red(); cout << "> Invalid choice!" << endl;
		white(); cout << "Please try again: ";
		cin >> option;
	}

	if (option == 1) {

		string type;
		yellow(); cout << "\n > "; grey(); cout << "Are you sure you want to cancel this trip? (y/n) "; white(); cin >> type; cout << endl;

		while (cin.fail() || ((type != "y") && (type != "Y") && (type != "n") && (type != "N")))
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			red(); cout << "> Invalid choice!" << endl;
			white(); cout << "Please try again: ";
			cin >> type; cout << endl;
		}

		if (type == "Y" || type == "y") {

			for (int i = 0; i < ActiveTrips.size(); i++) {
				if (ActiveTrips.at(i).getID() == idtrip) {
					ActiveTrips.erase(ActiveTrips.begin() + i);
				}
			}
			yellow(); cout << "\n Trip canceled with success!\n"; white();
			blue(); cout << "-----------------------------------------------------------" << endl;
			red(); cout << "\n Press enter to go back."; white(); getEnter();
			return;
		}

		else {
			blue(); cout << "-----------------------------------------------------------" << endl;
			red(); cout << "\n Press enter to go back."; white(); getEnter();
			return;
		}

	}

	if (option == 2) {


		for (int i = 0; i < ActiveTrips.size(); i++) {
			if (ActiveTrips.at(i).getID() == idtrip) {

				if (ActiveTrips.at(i).getCandidateQueue().empty()) { //nao ha candidatos
					yellow(); cout << "\n There's no candidates for this trip yet!\n"; white();
					blue(); cout << "-----------------------------------------------------------" << endl;
					red(); cout << "\n Press enter to go back."; white(); getEnter();
					return;
				}

				for (int j = 0; j < ActiveTrips.at(i).getStops().size(); j++) {
					if (!ActiveTrips.at(i).getStops().at(j).getPassengers().empty()) { //ja ha candidatos em stops
						yellow(); cout << "\n You already chose candidates for this trip!\n"; white();
						blue(); cout << "-----------------------------------------------------------" << endl;
						red(); cout << "\n Press enter to go back."; white(); getEnter();
						return;
					}
				}
			}
		}

		clearScreen();
		menuHeader();
		cout << "|                       ";  grey(); cout << "CANDIDADE QUEUE";  white(); cout << "                   |" << endl
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		grey(); cout << setw(4) << "ID" << setw(12) << "Is Buddy" << setw(12) << "First Stop" << setw(12) << "Last Stop" << setw(15) << "Distance" << endl;
		blue(); cout << "-----------------------------------------------------------" << endl;
		white();


		priority_queue <CandidateTrip> coutQueue; //fila para fazer display
		vector <CandidateTrip> vectorQueue; //vetor com a mesma ordem da fila
		vector <int> candidatesIDs; //vetor com os IDs dos candidatos


		for (int i = 0; i < ActiveTrips.size(); i++) {
			if (ActiveTrips.at(i).getID() == idtrip) {

				coutQueue = ActiveTrips.at(i).getCandidateQueue();

				while (!coutQueue.empty()) {

					if (coutQueue.top().getPassanger() == NULL) {

						candidatesIDs.push_back(-1);
					}
					else candidatesIDs.push_back(coutQueue.top().getPassanger()->getID());

					vectorQueue.push_back(coutQueue.top());

					if (coutQueue.top().getPassanger() == NULL) {

						cout << setw(4) << "-1" << setw(9);
					}

					else cout << setw(4) << coutQueue.top().getPassanger()->getID() << setw(9);

					if (coutQueue.top().areBuddies())
						cout << "[X]";
					else cout << "[ ]";

					cout << setw(12) << coutQueue.top().getInitStop() << setw(12) << coutQueue.top().getEndStop() << setw(15) << coutQueue.top().getDistance() << endl;

					coutQueue.pop();

				}
			}
		}

		int availableSeats; //lugares do carro

		for (int i = 0; i < ActiveTrips.size(); i++) {

			if (ActiveTrips.at(i).getID() == idtrip) {
				availableSeats = ActiveTrips.at(i).getStops().at(0).getAvailableSeats() + ActiveTrips.at(i).getStops().at(0).getPassengers().size();
			}
		}

		blue(); cout << "-----------------------------------------------------------" << endl;  grey();
		cout << "Attention: the max number of passengers is the numbers";
		cout << endl << "of available seats in your car\n"; white();
		yellow(); cout << " > "; grey(); cout << "Available seats in your car: "; white(); cout << availableSeats << endl;



		grey();  cout << endl << " Insert the passengers you want in your trip (CTRL + Z to END): " << endl << endl;

		int candidateNumber = 1;
		int idcand;
		vector <int> candidatesIDS;

		while (!cin.eof() && availableSeats >= candidateNumber)
		{
			cout << " Passenger # " << candidateNumber << " : ";

			cin >> idcand;

			//enquanto o utilizador nao inserir ctrl+z
			if (!cin.eof())
			{
				if (find(candidatesIDS.begin(), candidatesIDS.end(), idcand) != candidatesIDS.end()) {
					red(); cout << "> Passenger already chosen!" << endl; grey();
				}

				else if (find(candidatesIDs.begin(), candidatesIDs.end(), idcand) == candidatesIDs.end()) {
					red(); cout << "> Invalid choice!" << endl; grey();
				}

				else {
					candidatesIDS.push_back(idcand);
					candidateNumber++;
				}

			}

		}
		cin.clear();

		yellow();  cout << "\nPassengers you have chosen: ";

		for (int i = 0; i < candidatesIDS.size(); i++) {
			yellow(); cout << "\n > "; grey(); cout << candidatesIDS.at(i);
		}

		white();

		cout << endl << endl;


		string type2;
		yellow(); cout << "\n > "; grey(); cout << "Are you sure you want to add these candidates to your trip?  (y/n) "; white(); cin >> type2; cout << endl;

		while (cin.fail() || ((type2 != "y") && (type2 != "Y") && (type2 != "n") && (type2 != "N")))
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			red(); cout << "> Invalid choice!" << endl;
			white(); cout << "Please try again: ";
			cin >> type2; cout << endl;
		}

		if (type2 == "Y" || type2 == "y") {


			//adicionar passageriros à Active Trip

			int idi, idf;

			for (int k = 0; k < candidatesIDS.size(); k++) {

				if (candidatesIDS.at(k) == -1) { //caso guest

					for (int d = 0; d < vectorQueue.size(); d++) {

						if (vectorQueue.at(d).getPassanger() == NULL) {

							for (unsigned int i = 0; i < ActiveTrips.size(); i++) {

								if (idtrip == ActiveTrips.at(i).getID()) {

									for (unsigned int j = 0; j < ActiveTrips.at(i).getStops().size(); j++) {
										if (vectorQueue.at(d).getInitStop() == ActiveTrips.at(i).getStops().at(j).getCode()) //obtem id inicial ; idi
											idi = j;
										if (vectorQueue.at(d).getEndStop() == ActiveTrips.at(i).getStops().at(j).getCode()) //obtem id final ; idf
											idf = j;
									}

									for (idi; idi < idf; idi++) { //verifica se ha lugares disponiveis em cada paragem, menos na final, visto que user sai nessa

										ActiveTrips.at(i).setStops(idi, candidatesIDS.at(k)); //decrementa e adiciona user a viagem nas stops
									}
								}
							}

						}
					}

				}
				else { //caso cliente registado
					for (int d = 0; d < vectorQueue.size(); d++) {

						if (vectorQueue.at(d).getPassanger()->getID() == candidatesIDS.at(k)) {

							for (unsigned int i = 0; i < ActiveTrips.size(); i++) {

								if (idtrip == ActiveTrips.at(i).getID()) {

									for (unsigned int j = 0; j < ActiveTrips.at(i).getStops().size(); j++) {
										if (vectorQueue.at(d).getInitStop() == ActiveTrips.at(i).getStops().at(j).getCode()) //obtem id inicial ; idi
											idi = j;
										if (vectorQueue.at(d).getEndStop() == ActiveTrips.at(i).getStops().at(j).getCode()) //obtem id final ; idf
											idf = j;
									}

									for (idi; idi < idf; idi++) { //verifica se ha lugares disponiveis em cada paragem, menos na final, visto que user sai nessa

										ActiveTrips.at(i).setStops(idi, candidatesIDS.at(k)); //decrementa e adiciona user a viagem nas stops
									}
								}
							}

							vectorQueue.at(d).getPassanger()->setNtrips(); //adiciona uma viagem
						}
					}
				}
			}

			yellow(); cout << "\n Success! The passangers were added to the trip!\n"; white();
		}


	}

	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getEnter();
	return;


}