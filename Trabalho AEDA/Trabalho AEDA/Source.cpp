#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Utilities.h"
#include "Agency.h"

using namespace std;

Agency* Agency::singleton_instance = 0;

Utilities u;

//Abre janela de controlo no meio do ecra
HWND hwnd = GetConsoleWindow();
RECT desktop;
const HWND hDesktop = GetDesktopWindow();
HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
COORD max_size = GetLargestConsoleWindowSize(screen);


int welcomeMenu() {

	//Menu - Welcome
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; u.blue(); cout << "ShareIt"; u.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                       ";  u.grey(); cout << "::WELCOME::";  u.white(); cout << "                       |" << endl;
	u.blue(); cout << "-----------------------------------------------------------" << endl;
	u.grey(); cout << "   Choose one of the following options:\n\n";
	u.white(); cout << setw(36) << "1. Register\n" << setw(33) << "2. Login\n" << setw(33) << "3. Guest\n";
	u.blue(); cout << "-----------------------------------------------------------" << endl;  u.white();
	cout << "|~~~                                ";  u.grey(); cout << "< 0. Close >";  u.white(); cout << "       ~~~|" << endl
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
		u.red(); cout << "> Invalid choice!" << endl;
		u.white(); cout << "Please try again: ";
		cin >> choice;
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
			//TODO register link
			break;
		case 2:
			Agency::instance()->loginUser();
			//TODO login link
			break;
		case 3:
			//TODO guest link
			break;
		case 0:
			Sleep(5000);
			exit(0);
			break;
		}
}

int main()
{
	
	//Janela//
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 310, 150, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Agency::instance()->extractUsers();
	Agency::instance()->extractBuddies();

	optionsWelcomeMenu();
	

	/*
	//testar funçoes ficheiros

	Agency::instance()->extrairUsers();
	for (unsigned int i = 0; i < Agency::instance()->getUsers().size(); i++)
	{
		cout << Agency::instance()->getUsers().at(i)->getID() << " - " << Agency::instance()->getUsers().at(i)->getName() << " - ";
		if (Agency::instance()->getUsers().at(i)->car())
			cout << "1";
		else cout << "0";
		cout << " - " << Agency::instance()->getUsers().at(i)->getPassword() << endl;
	}

	
	Agency::instance()->addUsers(p2);
	Agency::instance()->escreverUsers();

	*/
		
	return 0;
}