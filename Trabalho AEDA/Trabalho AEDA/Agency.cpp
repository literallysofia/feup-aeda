#include "Agency.h"

/////////////////////
// EXCECOES /////
///////////////////

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

/// PRINT DA STRUCT STOP
ostream & operator<<(ostream &out, const stop &e) {
	out << "ERROR: " << e.code << " - " << e.name << endl; return out;
};

Agency::Agency()
{
}

Agency::~Agency()
{
}

/* MENUS */

void Agency::registerUser()
{
	clearScreen();
	string type, name, username, password;

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
		yellow(); cout << "    > "; grey(); cout << "Enter password: "; white();
		password = insertPassword();
		yellow(); cout << "\n    > "; grey(); cout << "Confirm password: "; white();
		if (sameString(password, insertPassword()))
			a = true;
		else { red(); cout << "\n Password does not match! Try again.\n\n"; }
	}

	yellow(); cout << "\n\n    > "; grey(); cout << "Enter name: "; white(); cin.ignore(); getline(cin, name);

	int nID = getLastId() + 1;

	if ((type == "y") || (type == "Y")) {
		User *u1 = new Driver(nID, name, 0.00, username, password, 0);
		addUser(u1);
	}
	else {
		User *u1 = new Passenger(nID, name, 0.00, username, password, 0);
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
		<< setw(26) << "4. Relationships" << setw(30) << endl;
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


	if (option == 0)
		return 0;
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

	if (option == 0)
		return 0;
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
	cout << "|                          ";  grey(); cout << "USERS BY USERNAME";  white(); cout << "                          |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	setcolor(7); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;

	setcolor(15);

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

	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getchar(); getchar();
}

void Agency::menuDisplayUsersByName() {

	clearScreen();
	vector<User*> UsersV = Users;
	sort(UsersV.begin(), UsersV.end(), [](User* a, User* b) {return a->getName() < b->getName(); });

	menuHeader();
	cout << "|                          ";  grey(); cout << "USERS BY NAME";  white(); cout << "                          |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	setcolor(7); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	setcolor(3); cout << "-----------------------------------------------------------" << endl;

	setcolor(15);

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

	setcolor(3); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getchar(); getchar();
}

int Agency::menuSearch() {

	clearScreen();
	menuHeader();
	cout << "|~~~                       ";  grey(); cout << "SEARCH";  white(); cout << "                      ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(18) << "1. Users" << endl
		<< setw(18) << "2. Trips" << endl
		<< setw(25) << "3. Transactions" << endl;
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

	if (option == 0)
		return 0;
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
}

void Agency::menuDisplayBuddies() {
	clearScreen();
	menuHeader();
	cout << "|                      ";  grey(); cout << "RELATIONSHIPS";  white(); cout << "                     white() |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();  displayBuddies();
	blue(); cout << "-----------------------------------------------------------" << endl;
	red(); cout << "\n Press enter to go back."; white(); getchar(); getchar();
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
	red(); cout << "\n Press enter to go back."; white(); getchar(); getchar();
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
	red(); cout << "\n Press enter to go back."; white(); getchar(); getchar();
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


	if (option == 0)
		return 0;
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

void Agency::menuSearchUserByID() {

	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "SEARCH USER";  white(); cout << "                   ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int id, pos;

	cout << endl << "ID of the user you are searching for: ";  cin >> id;
	cout << endl;

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
	red(); cout << "\n Press any key to go back."; white(); getchar();
	cin.clear();
	cin.ignore(1000, '\n');
	//TODO: VER MELHOR
}

void Agency::menuSearchUserByUsername() {

	clearScreen();
	menuHeader();
	cout << "|~~~                     ";  grey(); cout << "SEARCH USER";  white(); cout << "                   ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int  pos;
	string input;

	cout << endl << "Username of the person you are searching for: ";  cin >> input;
	cout << endl;

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
	red(); cout << "\n Press any key to go back."; white(); getchar();
	cin.clear();
	cin.ignore(1000, '\n');
	//TODO: VER MELHOR
}





int Agency::menuSearchUser() {

	clearScreen();
	menuHeader();

	cout << "|~~~                    ";  grey(); cout << "SEARCH USER";  white(); cout << "                    ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(18) << "1. By ID" << endl
		<< setw(24) << "2. By Username" << endl;
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

	if (option == 0)
		return 0;
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
}

int Agency::menuSearchTrip() {

	clearScreen();
	menuHeader();
	cout << "|~~~                   ";  grey(); cout << "SEARCH TRIPS";  white(); cout << "                    ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(22) << "1. By Driver" << endl
		<< setw(21) << "2. By Month" << endl;
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

	if (option == 0)
		return 0;
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
}

void Agency::menuSearchTripByDriver() {

	clearScreen();
	menuHeader();
	cout << "|~~~              ";  grey(); cout << "SEARCH TRIPS BY DRIVER";  white(); cout << "               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int id;

	cout << endl << "ID of the driver: ";  cin >> id;
	cout << endl;

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
	red(); cout << "\n Press any key to go back."; white();
	getchar();
	cin.clear();
	cin.ignore(1000, '\n');
	//TODO: VER MELHOR
}

void Agency::menuSearchTripByMonth() {

	clearScreen();
	menuHeader();
	cout << "|~~~               ";  grey(); cout << "SEARCH TRIPS BY MONTH";  white(); cout << "               ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int month;

	cout << endl << "Month of the trip you are searching for: ";  cin >> month;
	cout << endl;

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
	red(); cout << "\n Press any key to go back."; white();
	getchar();
	cin.clear();
	cin.ignore(1000, '\n');
	//TODO: VER MELHOR
}


int Agency::menuSearchTransaction() {

	clearScreen();
	menuHeader();

	cout << "|~~~                ";  grey(); cout << "SEARCH TRANSACTION";  white(); cout << "                 ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(20) << "1. By User" << endl
		<< setw(21) << "2. By Month" << endl;
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

	if (option == 0)
		return 0;
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
}

void Agency::menuSearchTransactionByUser() {

	clearScreen();
	menuHeader();
	cout << "|~~~            ";  grey(); cout << "SEARCH TRANSACTION BY USER";  white(); cout << "             ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	int id;

	cout << endl << "User ID: ";  cin >> id;
	cout << endl;

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
	red(); cout << "\n Press any key to go back."; white();
	getchar();
	cin.clear();
	cin.ignore(1000, '\n');
	//TODO: VER MELHOR
}

void Agency::menuSearchTransactionByMonth() {

	clearScreen();
	menuHeader();
	cout << "|~~~            ";  grey(); cout << "SEARCH TRANSACTION BY MONTH";  white(); cout << "            ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	int month;

	cout << endl << "Month: ";  cin >> month;
	cout << endl;

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
	red(); cout << "\n Press any key to go back."; white();
	getchar();
	cin.clear();
	cin.ignore(1000, '\n');
	//TODO: VER MELHOR
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
		cout << setw(23) << "2. Create Trip\n";
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

	if (option == 0) {
		return 0;
	}
	else
		return option;
}

void Agency::optionsMainMenu_User() {
	unsigned short int option;

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
		}
}

int Agency::menuAccount()
{
	clearScreen();
	menuHeader();
	cout << "|                          ";  grey(); cout << "ACCOUNT";  white(); cout << "                          |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	grey(); cout << setw(5) << "ID" << setw(10) << "User" << setw(13) << "Name" << setw(15) << "Balance" << setw(13) << "Num Cars" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	white();

	cout << setw(5) << Users.at(getPos(sessionID))->getID() << setw(10) << Users.at(getPos(sessionID))->getUsername() << setw(15) <<
		Users.at(getPos(sessionID))->getName() << setw(13) << Users.at(getPos(sessionID))->getBalance() << setw(12) << 1 << endl;

	blue(); cout << "-----------------------------------------------------------" << endl;  grey();
	cout << setw(15) << "1. Deposit\n"; white();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  grey(); cout << "< 0. Return >";  white(); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	if (Users.at(getPos(sessionID))->getBalance() <= 0) {
		red(); cout << "WARNING: You need to deposit in your account!\n\n\n"; white();
	}

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option < 0) || ((option > 1)))
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

	if (option == 0)
		return 0;
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

	addTrip();
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

	chooseTrip(recTrips, buddieTrips, stopCodes);
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

	chooseTripGuest(recTrips, stopCodes);
	return;
}

/*FILES*/

/* EXTRACT AND SAVE */
void Agency::extractData() {
	extractUsers();
	extractBuddies();
	extractStops();
	extractTransactions();
	extractRecord();
	extractActive();
}

void Agency::saveData() {
	saveUsers();
	saveBuddies();
	saveTransactions();
	saveRecord();
	saveActive();
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
			size_t pos6 = str5.find(";"); //posi�ao 5

			string ids = line.substr(0, pos1); //string id
			string nome = str1.substr(0, pos2);
			string scar = str2.substr(0, pos3); //string carro
			string sbalance = str3.substr(0, pos4); //string balance
			string user = str4.substr(0, pos5);
			string pass = str5.substr(0, pos6);
			string nt_s = str5.substr(pos6 + 1); //string nro de trips

			int idi = stoi(ids, nullptr, 10); //passa o id de string para int
			bool bcar;
			if (scar == "1") //passa a tring carro para bool
				bcar = true;
			else bcar = false;

			float balancef = stof(sbalance, NULL); //passa o balance de string para float

			int nt = stoi(nt_s, nullptr, 10); //passa o id de string para int

			if (bcar)
			{
				//se o User tiver carro, adiciona um novo driver
				User *d1 = new Driver(idi, nome, balancef, user, pass, nt);
				Users.push_back(d1);
			}
			else
			{
				//caso contrario adiciona um novo passenger
				User *p1 = new Passenger(idi, nome, balancef, user, pass, nt);
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
			UserFile << Users.at(i)->getID() << ";" << Users.at(i)->getName() << ";";

			if (Users.at(i)->car())
				UserFile << "1";
			else UserFile << "0";

			UserFile << ";" << Users.at(i)->getBalance() << ";" << Users.at(i)->getUsername() << ";" << Users.at(i)->getPassword() << ";" << Users.at(i)->getNtrips() << endl;
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


/* FUNCTIONS */

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

	bool exists = false;

	for (size_t i = 0; i < stopsAvailable.size(); i++)
	{
		if (stopsAvailable.at(i).code == s)
			exists = true;
	}

	return exists;
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

}

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
			cout << Users.at(i)->getBuddies().at(j)->getName() << "   ";
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

	int stopNumber = 1;

	yellow(); cout << " > "; grey(); cout << "Please enter your stops (CTRL + Z to END):\n"; white();


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

		//fim da introdu�ao das paragens
		else {

			if (stopCodes.size() < 2)
			{
				red(); cout << "ERROR: You did not enter at least 2 distinct stops.\n"; white();
				Sleep(2500);
				clearScreen();
			}
			else
			{
				//introducao do numero de lugares disponiveis
				yellow(); cout << "\n > "; grey(); cout << "Enter the number of seats available ( minimun: 1 , maximum: 6):\n"; cin.clear(); white();
				cout << " > "; int numSeats = readInt(1, 6); cin.clear();

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
						cout << "> Day: "; cin >> day; cout << " > Month: "; cin >> month; cout << " > Year: "; cin >> year;
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

				}

				while (1) {

					time_t actualTime = getUnixCode(currentDate, currentHour);

					try
					{

						//hora inicio
						int hourS, minutesS;
						yellow(); cout << "\n > "; grey(); cout << "Enter starting time:\n "; cin.clear(); white();
						cout << "> Hour: "; cin >> hourS; cout << " > Minutes: "; cin >> minutesS;
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
				}

				while (1) {

					try
					{
						//hora fim
						int hourE, minutesE;
						yellow(); cout << "\n > "; grey(); cout << "Please enter finish time:\n "; cin.clear(); white();

						cout << "> Hour: "; cin >> hourE; cout << " > Minutes: "; cin >> minutesE;

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

				/*for (unsigned int i = 0; i < Trips.size(); i++) {
					cout << Trips.at(i).getID() << endl;
					for (unsigned int j = 0; j < Trips.at(i).getStops().size(); j++) {
						cout << Trips.at(i).getStops().at(j).getCode() << endl;
					}
				}
				system("pause");*/
			}
			break;
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
					cout << "> Day: "; cin >> day; cout << " > Month: "; cin >> month; cout << " > Year: "; cin >> year;
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

	/*for (unsigned int i = 0; i < ActiveTrips.size(); i++) {
		if (id == ActiveTrips.at(i).getID()) {
			for (unsigned int j = 0; j < ActiveTrips.at(i).getStops().size(); j++) {
				cout << ActiveTrips.at(i).getStops().at(j).getCode() << "/" << ActiveTrips.at(i).getStops().at(j).getAvailableSeats() << "/" <<
					 ActiveTrips.at(i).getStops().at(j).getPassengers().size() << endl;
			}
		}
	}*/

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
					cout << "> Day: "; cin >> day; cout << " > Month: "; cin >> month; cout << " > Year: "; cin >> year;
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






float Agency::deposit()
{
	float value;
	yellow(); cout << "\n > "; grey(); cout << "Insert the amount of money you want to deposit in your account (max 200): "; white();
	cin >> value;

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
	return 0;
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
