#include "Agency.h"
Utilities ut;
Tools t;

Agency::Agency()
{
}

Agency::~Agency()
{
}


/* MENUS */

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
	int id = 0;
	string output, password;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; ut.blue(); cout << "ShareIt"; ut.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                          ";  ut.grey(); cout << "Login";  ut.white(); cout << "                          |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.grey(); cout << "       > Enter id or name: "; ut.white(); cin >> output; cout << endl;
	ut.grey(); cout << "       > Enter password: "; ut.white();  cin >> password; cout << endl;

	if (output == "admin")
		optionsMainMenu_Admin();

	/*if (t.outputName(output))
	id = stoi(output, nullptr, 10);  //se a opcao for o ID passa de string para int
	else {
	if (output == "admin")
	optionsMainMenu_Admin();
	/*else {
	if (validUser(output))
	//TODO chamar funcao de opcoes do menu inicial de user
	else //TODO throw a excecao caso o user nao exista??? maybe? ou dar outra oportunidade?
	}*/
	//}
	//TODO verificar se existe 
	//TODO admin ou nao
	//TODO abrir menu principal
	return;
}

/* ADMINISTRADOR */
int Agency::mainMenu_Admin() {

	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; ut.blue(); cout << "ShareIt"; ut.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                   ";  ut.grey(); cout << "ADMINISTRATION";  ut.white(); cout << "                  ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(18) << "1. Users" << setw(30) << "4. Relationships" << endl
		<< setw(24) << "2. Trip Record" << setw(20) << "5. smth else" << endl
		<< setw(25) << "3. Transactions" << setw(19) << "6. smth else" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;  ut.white();
	cout << "|~~~                                ";  ut.grey(); cout << "< 0. Close >";  ut.white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 6))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Invalid choice!" << endl;
		ut.setcolor(15); cout << "Please try again: ";
		cin >> option;
	}

	if ((option >= 0) && (option <= 6))
	{
		if (option == 0)
			//TODO logout();
			exit(0);
		return option;
	}
	return 0;
}

void Agency::optionsMainMenu_Admin() {

	unsigned short int option;

	while (option = mainMenu_Admin())
		switch (option)
		{
		case 1:
			//TODO mostrar todos users
			break;
		case 2:
			//TODO mostrar o historico de trips
			break;
		case 3:
			//TODO mostrar transacoes
			break;
		case 4:
			//TODO mostrar buddies (relacoes de amizade)
			break;
		case 5:
			break;
		case 6:
			break;
		}
	return;
}


/* FUNCOES */

bool Agency::validUser(string name) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (name == Users.at(i)->getName())
			return true;
	}
	return false;
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