#include "Agency.h"
Utilities ut;
Tools t;

/////////////////////
// EXCEÇOES /////
///////////////////

class NonexistentStop
{
public:
	string stop;
	NonexistentStop(string name) { stop = name; }
};
ostream & operator<<(ostream &out, const NonexistentStop &obj)
{
	out << "The stop '" << obj.stop << "' does not exist.\n"; return out;
}

class RepeatedStop
{
public:
	string stop;
	RepeatedStop(string name) { stop = name; }
};
ostream & operator<<(ostream &out, const RepeatedStop &obj)
{
	out << "The stop '" << obj.stop << "' was already used.\n"; return out;
}

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
	string type, name, password;

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; ut.blue(); cout << "ShareIt"; ut.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                      ";  ut.grey(); cout << "Create Account";  ut.white(); cout << "                     |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl; ut.white();
	cout << "    Types of accounts:\n      - Driver: You need to register your car and host\n      trips. You'll also earn some money.\n      - Passenger: You can only join existing trips.\n\n";
	ut.grey(); cout << "  > Do you want to register as a Driver? (y/n) "; ut.white(); cin >> type;  cout << endl;
	ut.grey(); cout << "  > Enter name: "; ut.white(); cin.ignore(); getline(cin, name); cout << endl;
	ut.grey(); cout << "  > Enter password: "; ut.white();  cin >> password; cout << endl;

	if ((type == "y") || (type == "Y"))
		//addUser(true, name, password);
		cout << "ok";
	else {
		if ((type == "n") || (type == "N"))
			//addUser(false, name, password);
			cout << "okk";
		else return; //TODO nao pode ser assim lmao
	}

	//TODO melhorar esta shit

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
	ut.grey(); cout << "       > Enter id or name: "; ut.white(); cin.ignore(); getline(cin, output); cout << endl;
	ut.grey(); cout << "       > Enter password: "; ut.white();  cin >> password; cout << endl;

	if (output == "admin")
		optionsMainMenu_Admin();
	else {
		if (t.outputName(output)) { // se é uma string
			if (validUser(output) && validPassword(password)) {
				this->sessionID = findID(output);
				this->sessionPos = getPos(sessionID);
				optionsMainMenu_User();
			}
			else return;
		}
		else {
			id = stoi(output, nullptr, 10);
			if (getPos(id) == -1)
				return; //nao existe woops
			else {
				this->sessionID = id;
				this->sessionPos = getPos(sessionID);
				optionsMainMenu_User();
			}
		}
	}

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

	while (cin.fail() || (option > 6) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "> Invalid choice!" << endl;
		ut.white(); cout << "Please try again: ";
		cin >> option;
	}


	if (option == 0)
		//TODO logout();
		exit(0);
	return option;
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

/* MENUS USER */

int Agency::mainMenu_User() {

	ut.clearScreen();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; ut.blue(); cout << "ShareIt"; ut.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                   ";  ut.grey(); cout << "MAIN MENU";  ut.white(); cout << "                  ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.grey(); cout << setw(30) << "You are logged in as: "; ut.white(); cout << Users.at(getPos(sessionID))->getName() << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl; ut.white();

	cout << setw(18) << "1. Account" << setw(30) << "3. Add Buddy" << endl;

	if (Users.at(sessionPos)->car()) { //caso seja driver
		cout << setw(22) << "2. Create Trip" << setw(24) << "4. Add Car" << endl;
	}
	else { // caso seja passenger
		cout << setw(20) << "2. Join Trip" << setw(28) << "4. smth else" << endl;
	}

	ut.blue(); cout << "-----------------------------------------------------------" << endl;  ut.white();
	cout << "|~~~                                ";  ut.grey(); cout << "< 0. Logout >";  ut.white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 4) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "> Invalid choice!" << endl;
		ut.white(); cout << "Please try again: ";
		cin >> option;
	}

	//if (option == 0)
		//TODO logout
	return option;

}

void Agency::optionsMainMenu_User() {

	unsigned short int option;

	while (option = mainMenu_User())
		switch (option)
		{
		case 1:
			//TODO mostrar conta do user
			break;
		case 2:
			//TODO se tem carro, criar trip, se nao tem, nao pode, volta atras
			break;
		case 3:
			//TODO quem tem carro pode fazer join?
			break;
		case 4:
			//TODO add buddy
			break;
		}
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

bool Agency::validPassword(string password) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (password == Users.at(i)->getPassword())
			return true;
	}
	return false;
}

int Agency::findID(string name) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (name == Users.at(i)->getName())
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

vector<User *> Agency::getUsers() {
	return Users;
}

void Agency::addUsers(User * u)
{
	Users.push_back(u);
}

void Agency::addTrip() {

	Trip t;	t.setDriverID(1); t.setID( 1);
	//Trip t;	t.setDriverID(sessionID); t.setID(Trips.back().getID() + 1);
	vector<string> stops;
	string eachStop;
	int stopNumber = 1;

	cout << "\tAVAILABLE STOPS:\n\n";

	for (size_t i = 0; i < stopsAvailable.size(); i++) {
		cout << "- " << stopsAvailable[i] << endl;
	}
	cout << endl;
	cout << "Please enter your stops (CTRL + Z to END):\n";

	while (1)
	{
		cout << "Stop # " << stopNumber << " : ";
		cin >> eachStop;

		//enquanto o utilizador nao inserir ctrl+z
		if (!cin.eof())
		{
			try
			{
				//se a paragem existe
				if (checkStop(eachStop)) {	
					//se a paragem ja foi inserida lança a exceçao
					if (find(stops.begin(), stops.end(), eachStop) != stops.end()) {
						throw RepeatedStop(eachStop);
					}
					//caso corra tudo bem é adicionada ao vetor
					else {
						stops.push_back(eachStop);
						stopNumber++;
					}
				}
				//se nao existe lança a exceçao
				else                       
					throw NonexistentStop(eachStop);

			}
			catch (const NonexistentStop &e)
			{
				cout << e;
			}
			catch (const RepeatedStop &e)
			{
				cout << e;
			}
		}
		
		//fim da introduçao das paragens
		else {
			cout << "Please enter the number of seats available ( minimun: 1 , maximum: 6):\n-> "; cin.clear();
			int numSeats = ut.leInteiro(1, 6);
			t.setAvailableSeats(numSeats);

			cout << "\n\nStops and number of seats successfully added to your trip.\n\n";
			Sleep(1500);
			ut.clearScreen();
			t.setStops(stops);
			Trips.push_back(t);
			Users.at(sessionPos)->addTrip(t);			//adiciona a viagem criada ao utilizador correspondente
			break;										//deixa o ciclo 'while'
		}
	}
}

bool Agency::checkStop(string s) {

	bool exists = false;

	for (size_t i = 0; i < stopsAvailable.size(); i++)
	{
		if (stopsAvailable[i] == s)
			exists = true;
	}

	return exists;
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

void Agency::runTrip(int tripID) {

	Trip t;
	int tripIndex;
	vector<int> passengersID;

	for (unsigned int i = 0; i < Trips.size(); i++)
	{
		if (Trips[i].getID() == tripID) {
			t = Trips[i];
			tripIndex = i;
			break;
		}
	}

	passengersID = t.getPassengers();
	vector<string> stops = t.getStops();

	for (size_t i = 0; i < stops.size(); i++)
	{
		string currentStop = stops.at(i);

		ut.clearScreen();
		cout << "Running trip # " << t.getID() << " :\n"; cout << "Origin: " << t.getOrigin() << endl; cout << "Destination: " << t.getDestination() << endl;
		cout << "\nDriver: " << Users[getPos(t.getID())]->getName() << " \n";
		cout << "Current stop is " << currentStop << "\n";

		if (i == t.getStops().size() - 1)
		{
			cout << "Final destination reached!\n";
		}
		else {
			//saida de passageiros
			vector<User *> usersAway;

			for (size_t i = 0; i < passengersID.size(); i++)
			{
				unsigned int vectorPos = getPos(passengersID[i]);

				//se o ID é positivo, procura-se no vetor Users
				if (passengersID[i] > 0)
				{
					//se a ultima paragem é a atual, ele sai
					if (Users[vectorPos]->getLast() == currentStop)
					{
						usersAway.push_back(Users[vectorPos]);
					}
				}

				//se o ID é negativo, procura-se no vetor de Guest
				if (passengersID[i] < 0)
				{
					for (size_t j = 0; j < Guests.size(); j++)
					{
						//encontrado o guest do ID respetivo
						if (Guests[j]->getID() == passengersID[i])
						{
							//se a paragem final é a atual, ele sai
							if (Guests[j]->getEnd() == currentStop)
							{
								//criacao de um user local para ser adicionado ao vetor de entradas
								User *u = new Passenger(Guests[j]->getName());
								usersAway.push_back(u);
							}
						}
					}
				}
			}

			//se houve alguma saida de passageiros
			if (usersAway.size() > 0)
			{
				cout << "\n->Exited:\n";
				for (size_t i = 0; i < usersAway.size(); i++)
				{
					cout << usersAway[i]->getName() << endl;
				}

				cout << endl;
				//atualizacao do numero de lugares disponiveis
				t.setAvailableSeats(t.getNumSeats() + (int)usersAway.size());
			}

			///entrada de passageiros///
			vector<User *> usersOnBoard;

			if (t.getNumSeats() > 0)
			{
				for (size_t i = 0; i < passengersID.size(); i++)
				{
					unsigned int vectorPos = getPos(passengersID[i]);

					//se o ID é positivo, procura-se no vetor Users
					if (passengersID[i] > 0)
					{
						//se a primeira paragem é a atual, ele entra
						if (Users[vectorPos]->getFirst() == currentStop)
						{
							usersOnBoard.push_back(Users[vectorPos]);
						}
					}

					//se o ID é negativo, procura-se no vetor de Guest
					if (passengersID[i] < 0)
					{
						for (size_t j = 0; j < Guests.size(); j++)
						{
							//encontrado o guest do ID respetivo
							if (Guests[j]->getID() == passengersID[i])
							{
								//se a paragem inicial é a atual
								if (Guests[j]->getStart() == currentStop)
								{
									//criacao de um user local para ser adicionado ao vetor de entradas
									User *u = new Passenger(Guests[j]->getName());
									usersOnBoard.push_back(u);
								}
							}
						}
					}
				}

				//se houve alguma entrada de passageiros
				if (usersOnBoard.size() > 0)
				{
					cout << "\n->Entered:\n";
					for (size_t i = 0; i < usersOnBoard.size(); i++)
					{
						cout << usersOnBoard[i]->getName() << endl;
					}

					cout << endl;
					t.setAvailableSeats(t.getNumSeats() - (int)usersOnBoard.size());
				}
			}

			else
			{
				cout << "All seats are full at this stop.\n";
			}

		}

		//espera pelo input da tecla Enter para passar à proxima paragem
		cout << "\n\n-> ENTER to go to the next stop <-";
		ut.getEnter();
	}
}


