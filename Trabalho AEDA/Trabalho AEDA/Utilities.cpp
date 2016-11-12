#include "Utilities.h"

Utilities::Utilities()
{
}


Utilities::~Utilities()
{
}

void Utilities::menuHeader()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                      "; blue(); cout << "ShareIt"; white(); cout << "                      ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
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
int Utilities::readInt(int min, int max) {

	bool validInput = false;
	int option;

	while (!validInput) {
		cin >> option;

		if (option > max || option < min || cin.fail())
		{
			red(); cout << "ERROR: Not a valid number!\n\n"; white();
			green();  cout << " Please, type a number between " << min << " and " << max << ": "; white();
			cin.clear();
		}
		else
			validInput = true;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return option;


}

void Utilities::clearScreen_param(int x) {

	COORD upperLeftCorner = { 0, x };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);

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

void Utilities::yellow()
{
	setcolor(14);
}

