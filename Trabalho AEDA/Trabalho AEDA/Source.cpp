#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Utilities.h"
#include "Agency.h"

using namespace std;

Agency* Agency::singleton_instance = 0;

//Abre janela de controlo no meio do ecra
HWND hwnd = GetConsoleWindow();
RECT desktop;
const HWND hDesktop = GetDesktopWindow();
HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
COORD max_size = GetLargestConsoleWindowSize(screen);


int welcomeMenu() {

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; blue(); cout << "ShareIt"; white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                       ";  grey(); cout << "::WELCOME::";  white(); cout << "                       |" << endl;
	blue(); cout << "-----------------------------------------------------------" << endl;
	grey(); cout << "   Choose one of the following options:\n\n";
	white(); cout << setw(36) << "1. Register\n" << setw(33) << "2. Login\n" << setw(33) << "3. Guest\n";
	blue(); cout << "-----------------------------------------------------------" << endl;  white();
	cout << "|~~~                                ";  grey(); cout << "< 0. Close >";  white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int choice;
	cout << "Type your choice: ";
	cin >> choice;

	while (cin.fail() || (choice > 3) || (choice < 0))
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
		cin >> choice;
	}

	if (choice== 0) {
		Agency::instance()->saveData();
		return 0;
	}

	return choice;
}


void optionsWelcomeMenu()
{
	unsigned short int choice;
	
	while (choice = welcomeMenu())

		switch (choice)
		{
		case 1:
			Agency::instance()->registerUser();
			break;
		case 2:
			Agency::instance()->loginUser();
			break;
		case 3:
			Agency::instance()->loginGuest();
			break;
		}
}

int main()
{
	/*
	//Janela//
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 310, 150, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Agency::instance()->extractData();

	optionsWelcomeMenu();
	*/

	//TESTES

	Agency::instance()->extractDistances();

	vector <string> v1;

	v1.push_back("AMR");
	v1.push_back("BAO");
	v1.push_back("MAI");
	v1.push_back("FGR");

	float a = Agency::instance()->distanceRide(v1, "MAI");
	cout << a << endl;

	return 0;
}