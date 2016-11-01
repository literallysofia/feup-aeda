#include "Agency.h"
Utilities ut;

unsigned int Agency::lastID = 1;

Agency::Agency()
{
}

Agency::~Agency()
{
}

//Menu's

void Agency::registerUser()
{
	ut.clearScreen();
	string name, password;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; ut.blue(); cout << "ShareIt"; ut.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                      ";  ut.grey(); cout << "Create Account";  ut.white(); cout << "                     |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.grey(); cout << "       > Enter name: "; ut.white(); cin >> name; cout << endl;
	ut.grey(); cout << "       > Enter password: "; ut.white();  cin >> password; cout << endl;

	//TODO adicionar utilizador
	//TODO sucesso ou nao
	//TODO abrir menu principal
}

void Agency::loginUser()
{
	ut.clearScreen();
	string name, password;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; ut.blue(); cout << "ShareIt"; ut.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                          ";  ut.grey(); cout << "Login";  ut.white(); cout << "                          |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.grey(); cout << "       > Enter id: "; ut.white(); cin >> name; cout << endl;
	ut.grey(); cout << "       > Enter password: "; ut.white();  cin >> password; cout << endl;

	//TODO verificar se existe 
	//TODO abrir menu principal
}



//Functions

unsigned int Agency::getLastID() {

	unsigned int toBeReturned = lastID;
	lastID++;
	return toBeReturned;
}

/*
//retorna o total do mes 
float Agency::endMonth() {

	typename vector<User *>::iterator it;
	float totalMonth = 0;

	for (it = users.begin(); it != users.end(); it++) {

			totalMonth += (*it)->payment();
			(*it)->resetTrips();   //só tem efeito nos passenger
		
	}

	return totalMonth;
}
*/