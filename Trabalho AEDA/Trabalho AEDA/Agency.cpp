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
			Agency::instance()->menuDisplayUsers();
			break;
		case 2:
			//TODO mostrar o historico de trips
			break;
		case 3:
			//TODO mostrar transacoes
			break;
		case 4:
			Agency::instance()->menuDisplayBuddies();
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


/*FILES*/

//users (id;nome;carro;pass) 
void Agency::extractUsers()
{
	ifstream Userfile("Users.txt");
	string line;


	if (Userfile.is_open())
	{
		if (!Users.empty()) Users.clear();

		while (getline(Userfile, line))
		{

			size_t pos1 = line.find(";"); //posiçao 1
			string str1 = line.substr(pos1 + 1); //nome+balance+carro+pass
			size_t pos2 = str1.find(";"); //posiçao 2
			string str2 = str1.substr(pos2 + 1); //balance+carro+pass
			size_t pos3 = str2.find(";"); //posiçao 3
			string str3 = str2.substr(pos3 + 1); //balance+pass
			size_t pos4 = str3.find(";"); //posiçao 3

			string ids = line.substr(0, pos1); //string id
			string nome = str1.substr(0, pos2);
			string sbalance = str2.substr(0, pos3); //string balance
			string scar = str3.substr(0, pos4); //string carro
			string pass = str3.substr(pos4 + 1);

			int idi = stoi(ids, nullptr, 10); //passa o id de string para int
			bool bcar;
			if (scar == "1") //passa a tring carro para bool
				bcar = true;
			else bcar = false;

			float balancef = stof(sbalance, NULL); //passa o balance de string para float

			if (bcar)
			{
				//se o User tiver carro, adiciona um novo driver
				User *d1 = new Driver(idi, nome, balancef, pass);
				Users.push_back(d1);
			}
			else
			{
				//caso contrario adiciona um novo passenger
				User *p1 = new Passenger(idi, nome, balancef, pass);
				Users.push_back(p1);
			}
		}
		Userfile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}

void Agency::writeUsers()
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

			UserFile << ";" << Users.at(i)->getBalance() << ";" << Users.at(i)->getPassword() << endl;
		}
		UserFile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}

//buddies (id;ids buddies) 
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
					/*
					for (unsigned int j = 0; j < Users.at(j)->getBuddies().size(); j++)
					{
						cout << Users.at(i)->getBuddies().at(j)->getName() << "   ";
					}
					*/
				}
			}
		}

		Buddiesfile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}

//TODO: WRITEBUDDIES NAO FUNCIONA
void Agency::writeBuddies()
{
	ofstream BuddiesFile("Buddies.txt");


	if (BuddiesFile.is_open())
	{
		for (unsigned int i = 0; i < Users.size(); i++)
		{
			BuddiesFile << Users.at(i)->getID() << ";";

			string buddies_s;

			for (unsigned int j = 0; j < Users.at(j)->getBuddies().size(); j++)
			{
				buddies_s.append(to_string(Users.at(i)->getBuddies().at(j)->getID()));
				buddies_s.append(",");
			}

			buddies_s.erase(buddies_s.size() - 1, 1); //apaga a ultima virgula
			BuddiesFile << buddies_s << endl;
		}
		BuddiesFile.close();
	}
	else { ut.setcolor(4); cerr << "Impossivel abrir ficheiro." << endl; ut.setcolor(15); }
}



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

	ut.red(); cout << "\tAVAILABLE STOPS:\n\n"; ut.white();

	for (size_t i = 0; i < stopsAvailable.size(); i++) {
		cout << "- " << stopsAvailable[i] << endl;
	}
	cout << endl;
	ut.grey(); cout << "Please enter your stops (CTRL + Z to END):\n"; ut.white();

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
				ut.red(); cout << e; ut.white();
			}
			catch (const RepeatedStop &e)
			{
				ut.red(); cout << e; ut.white();
			}
		}
		
		//fim da introduçao das paragens
		else {

			t.setStops(stops);

			if (stops.size() < 2)
			{
				ut.red(); cout << "[ERROR] You did not enter at least 2 distinct stops.\n"; ut.white();
				Sleep(2500);
				ut.clearScreen();
			}
			else
			{
				//introducao do numero de lugares disponiveis
				ut.blue(); cout << "\nPlease enter the number of seats available ( minimun: 1 , maximum: 6):\n-> "; cin.clear(); ut.white();
				int numSeats = ut.leInteiro(1, 6); cin.clear();
				t.setAvailableSeats(numSeats);

				//adicao da viagem ao vetor na agencia
				ut.green();  cout << "\n\nStops and number of seats successfully added to your trip.\n\n"; ut.white();
				Sleep(2500);
				ut.clearScreen();
				Trips.push_back(t);
				Users.at(sessionPos)->addTrip(t);			//adiciona a viagem criada ao utilizador correspondente
				
			}
			break;
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
		ut.green(); cout << "Running trip # " << t.getID() << " :\n";
		ut.grey(); cout << "Origin: " << t.getOrigin() << endl; cout << "Destination: " << t.getDestination() << endl;
		cout << "\nDriver: " << Users[getPos(t.getID())]->getName() << " \n";
		ut.white();  cout << "\nCurrent stop is " << currentStop << "\n";

		if (i == t.getStops().size() - 1)
		{
			ut.blue(); cout << "Final destination reached!\n"; ut.white();
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
								//TODO: quando sair adicionar transacao
							}
						}
					}
				}
			}

			//se houve alguma saida de passageiros
			if (usersAway.size() > 0)
			{
				ut.red(); cout << "\n->Exited:\n"; ut.white(); 
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
					ut.green(); cout << "\n->Entered:\n"; ut.white();
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


void Agency::displayUsers() {

	for (unsigned int i = 0; i < Users.size(); i++)
	{
		cout << setw(5) << Users.at(i)->getID();
		cout << setw(20) << Users.at(i)->getName();
		cout << setw(18) << setprecision(2) << fixed <<  Users.at(i)->getBalance();

		if(Users.at(i)->car())
			cout << setw(12)  << "[X]" << endl;
		else cout << setw(12) << "[ ]" << endl;
	}

	return;
}

int Agency::menuDisplayUsers() {

	ut.clearScreen();

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; ut.blue(); cout << "ShareIt"; ut.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                          ";  ut.grey(); cout << "Users";  ut.white(); cout << "                          |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(7); cout << setw(5) << "ID" << setw(20) << "Name" << setw(18) << "Balance" << setw(12) << "Driver" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  displayUsers();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(7);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Return >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao < 1))
	{
		if (opcao == 0)
			return 0;
		return opcao;
	}
	return 0;

}

void Agency::displayBuddies() {

	for (unsigned int i = 0; i < Users.size(); i++)
	{
		ut.setcolor(7); cout << setw(5) << "   USER"; ut.blue(); cout <<" | ";
		ut.white(); cout<< Users.at(i)->getName() << endl;
		ut.setcolor(7); cout << setw(5) << "BUDDIES"; ut.blue(); cout << " | ";
		ut.white();
		for (unsigned int j = 0; j < Users.at(i)->getBuddies().size(); j++)
		{
			cout << Users.at(i)->getBuddies().at(j)->getName() << "   ";
		}

		cout << endl << endl;
	}

	return;
}

int Agency::menuDisplayBuddies() {

	ut.clearScreen();

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; ut.blue(); cout << "ShareIt"; ut.white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                      ";  ut.grey(); cout << "Relationships";  ut.white(); cout << "                    |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  displayBuddies();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(7);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Return >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int opcao;
	cout << "Insira a sua escolha: ";
	cin >> opcao;

	while (cin.fail() || (opcao > 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.setcolor(4); cout << "> Digito invalido!" << endl;
		ut.setcolor(15); cout << "Volte a indicar escolha: ";
		cin >> opcao;
	}

	if ((opcao >= 0) && (opcao < 1))
	{
		if (opcao == 0)
			return 0;
		return opcao;
	}
	return 0;

}
