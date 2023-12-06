#include <iostream>
#include <string>
#include "ConsoleGUI.h"
#include "CString.h"

using namespace std;

int main() { 
	bool bQuit = false;
	while (!bQuit) {
		cout << endl << "===============================" << endl;
		cout << "Wybierz jakiego typu drzewo chcesz wprowadzic (string/double/int/bool) lub wpisz quit aby opuscic program: " << endl << endl;
		string sInput;
		getline(cin, sInput);
		if (sInput.compare(QUIT) == 0) {
			bQuit = true;
		}
		else if (sInput.compare(INT) == 0) {
			ConsoleGUI<int>* pcConsole = new ConsoleGUI<int>();
			pcConsole->vAsker();
			delete pcConsole;
		}
		else if (sInput.compare(DOUBLE) == 0) {
			ConsoleGUI<double>* pcConsole = new ConsoleGUI<double>();
			pcConsole->vAsker();
			delete pcConsole;
		}
		else if (sInput.compare(STRING) == 0) {
			ConsoleGUI<string>* pcConsole = new ConsoleGUI<string>();
			pcConsole->vAsker();
			delete pcConsole;
		}
		else if (sInput.compare(BOOL) == 0) {
			ConsoleGUI<bool>* pcConsole = new ConsoleGUI<bool>();
			pcConsole->vAsker();
			delete pcConsole;
		}
		else {
			cout << "Niepoprawne polecenie, sprobuj ponownie!" << endl;
		}
	}
}