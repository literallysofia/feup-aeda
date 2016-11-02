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


/*FICHEIROS*/
//TODO: veiculos disponiveis (id driver;lugares disponíveis;itinerário) & historico de viagens(nome do utilizador;proprietário da viatura;ponto de origem;ponto de destino;hora de início;hora de fim;dia)

//users (id;nome;carro;pass) 
void Agency::extrairUsers()
{
	ifstream Userfile("Users.txt");
	string line;


	if (Userfile.is_open())
	{
		if (!Users.empty()) Users.clear();

		while (getline(Userfile, line))
		{

			size_t pos1 = line.find(";"); //posiçao 1
			string str1 = line.substr(pos1 + 1); //nome+carro+pass
			size_t pos2 = str1.find(";"); //posição 2
			string str2 = str1.substr(pos2 + 1); //carro+pass
			size_t pos3 = str2.find(";"); //posiçao 3

			string ids = line.substr(0, pos1); //string id
			string nome = str1.substr(0, pos2);
			string scarro = str2.substr(0, pos3); //string se carro
			string pass = str2.substr(pos3 + 1);

			int idi = stoi(ids, nullptr, 10); //passa o id de string para int
			bool bcarro;
			if (scarro == "1")
				bcarro = true;
			else bcarro = false;

			if (bcarro)
			{
				User *d1 = new Driver(idi, nome, pass);
				Users.push_back(d1);
			}
			else
			{
				User *p1 = new Passenger(idi, nome, pass);
				Users.push_back(p1);
			}
		}
		Userfile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}


void Agency::escreverUsers()
{
	ofstream UserFile("Users.txt");

	if (UserFile.is_open())
	{
		for (unsigned int i = 0; i < Users.size(); i++)
		{
			UserFile << Users.at(i)->getID() << ";" << Users.at(i)->getName() << ";";
			if (Users.at(i)->car())
				UserFile << "1";
			else UserFile << "0";

			UserFile << ";" << Users.at(i)->getPassword() << endl;
		}
		UserFile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}

/*
//buddies (id;id buddies)
//TODO: map
void Agency::extrairBuddies()
{
	ifstream Buddiesfile("Buddies.txt");
	string line;


	if (Buddiesfile.is_open())
	{
		if (!vbuddies.empty()) vbuddies.clear();

		while (getline(Buddiesfile, line))
		{

			size_t pos1 = line.find(";"); //posiçao 1
			string ids = line.substr(0, pos1); //string id

			string buddiess = line.substr(pos1 + 1); //string buddies

			int idi = stoi(ids, nullptr, 10); //passa o id de string para int

			buddiess.append(",");

			vector <int> buddies;
			buddies.push_back(idi);

			while (!(buddiess.empty()))
			{
				buddies.push_back(stoi(buddiess.substr(0, buddiess.find_first_of(",")), nullptr, 10)); //adiciona um buddy ao vetor de buddies
				buddiess.erase(0, buddiess.find_first_of(",") + 1); //apaga esse buddy e a virgula seguinte da lista de buddies
			}

			vbuddies.push_back(buddies); //cria um novo elemento no vector

		}
		Buddiesfile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}

void Agency::escreverBuddies()
{
	ofstream BuddiesFile("Buddies.txt");

	if (BuddiesFile.is_open())
	{
		for (unsigned int i = 0; i < vbuddies.size(); i++)
		{
			BuddiesFile << vbuddies.at(i).at(0) << ";";

			for (unsigned int j = 1; i < vbuddies.at(i).size(); j++)
			{
				BuddiesFile << vbuddies.at(i).at(j) << ",";
			}
			BuddiesFile << endl;
		}
		BuddiesFile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}
*/

/* FUNCOES */

bool Agency::validUser(string name) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (name == Users.at(i)->getName())
			return true;
	}
	return false;
}
vector<User *> Agency::getUsers() {
	return Users;
}

void Agency::addUsers(User * u)
{
	Users.push_back(u);
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