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

int main()
{
	//Janela//
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 310, 150, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	//Menu de boas vindas
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~               "; u.setcolor(3); cout << "Supermercado  Vende++"; u.setcolor(15); cout << "               ~~~| " << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|                      ";  u.setcolor(7); cout << "BEM   VINDO !";  u.setcolor(15); cout << "                      |" << endl;
	u.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	u.setcolor(15); cout << setw(56) << "Indique o nome dos ficheiros com os dados, incluindo" << endl << setw(40) << "tambem a sua extensao." << endl << endl;
	u.setcolor(7); cout << setw(13) << "Exemplo: ";  u.setcolor(15); cout << "     NOMEDOFICHEIRO.txt" << endl;
	u.setcolor(3);  cout << "-----------------------------------------------------------" << endl;
	u.setcolor(15);

	//ficheiroClientes();
	//ficheiroProdutos();
	//ficheiroTransacoes();

	u.setcolor(3);
	cout << endl;
	Sleep(500);  cout << "."; Sleep(500);  cout << "."; Sleep(500);  cout << "." << endl;  u.setcolor(15);

	//Store::instance()->extrairClientes();
	//Store::instance()->extrairProdutos();
	//Store::instance()->extrairTransacoes();

	//Store::instance()->opcoesMenuInicial();

	return 0;
}