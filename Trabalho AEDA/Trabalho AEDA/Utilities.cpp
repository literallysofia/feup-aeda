#include "Utilities.h"

Utilities::Utilities()
{
}


Utilities::~Utilities()
{
}

void Utilities::setcolor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}



void Utilities::clearScreen() {

	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

//para ler um numero entre um minimo e maximo
int Utilities::leInteiro(int min, int max) {

	bool validInput = false;
	int opcao;

	while (!validInput) {
		cin >> opcao;

		if (opcao > max || opcao < min || cin.fail())
		{
			cout << endl << "[ERRO!] Nao foi introduzida uma opcao valida." << endl;
			cout << " Por favor, introduza uma opcao entre " << min << " e " << max << ": ";
			cin.clear();
		}
		else
			validInput = true;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return opcao;


}



// espera que o utilizador prima ENTER
void Utilities::getEnter() {

	int ENTER = 13;
	//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	char ch = _getch();

	while (ch != ENTER)
	{
		ch = _getch();
	}

	//PressKey();
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void Utilities::white()
{
	setcolor(15);
}

void Utilities::blue()
{
	setcolor(3);
}

void Utilities::grey()
{
	setcolor(7);
}

void Utilities::red()
{
	setcolor(4);
}
void Utilities::green()
{
	setcolor(2);
}