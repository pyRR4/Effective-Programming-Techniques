#pragma once
#include <string>
#include "CTree.h"

using namespace std;

template <typename T> class ConsoleGUI
{
private:
	string s_formula;
	CTree<T>* pc_tree;
public:
	ConsoleGUI()
	{
		s_formula = DEFAULT_VALUE;
		pc_tree = nullptr;
	}
	void vAsker();
};

static const string JOIN = "join";
static const string PRINT = "print";
static const string COMP = "comp";
static const string ENTER = "enter";
static const string VARS = "vars";
static const string QUIT = "quit";
static const string RETURN = "return";

template <typename T>
void ConsoleGUI<T>::vAsker()
{
	while (true) {
		cout << endl << "===============================" << endl;
		cout << "Wpisz jedna z ponizszych komend:" << endl;
		cout << "1. Wprowadz nowa formule: enter <formula>" << endl;
		cout << "2. Wyswietl zmienne w formule: vars" << endl;
		cout << "3. Oblicz formule dla podanych zmiennych: comp <var1> <var2> ... <varN> [ILOSC WARTOSCI MUSI BYC TAKA SAMA JAK ZMIENNYCH WYSWIETLONYCH PRZEZ VARS!!!]" << endl;
		cout << "4. Wyswietl formule w postaci prefiksowej: print" << endl;
		cout << "5. Dolacz nowa formule do aktualnej: join <formula>" << endl;
		cout << "6. Wroc do wyboru typu drzewa: return" << endl << endl;
		string sInput;
		getline(cin, sInput);
		if (sInput == RETURN) {
			delete pc_tree;
			return;
		}
		vector<string> vecInput = vStrToVec(sInput);
		string sKey = vecInput[0];
		vecInput.erase(vecInput.begin());
		if (sKey.compare(VARS) == 0) {
			if (pc_tree != nullptr)
				cout << pc_tree->sVarsToStr() << endl;
			else
				cout << "Nie podano drzewa!" << endl;
		}
		else if (sKey.compare(PRINT) == 0) {
			if (pc_tree != nullptr)
				cout << pc_tree->sPrefix() << endl;
			else
				cout << "Nie podano drzewa!" << endl;
		}
		else if (sKey.compare(COMP) == 0) {
			if (pc_tree != nullptr) {
				if (pc_tree->bSetVars(vecInput))
					cout << "Wartosc formuly wynosi: " << pc_tree->tTreeValue() << endl;
				else
					cout << "Niepoprawne polecenie, sprobuj ponownie!" << endl;
			}
			else
				cout << "Nie podano drzewa!" << endl;
		}
		else if (sKey.compare(JOIN) == 0) {
			if (pc_tree != nullptr) {
				pc_tree->vJoin(new CTree<T>(vecInput));
				if (pc_tree->bGetFixed())
					cout << "Drzewo zostalo naprawione przez program i moze nie wskazywac zadanych wartosci";
			}
			else
				cout << "Nie podano drzewa!" << endl;
		}
		else if (sKey.compare(ENTER) == 0) {
			delete pc_tree;
			pc_tree = new CTree<T>(vecInput);
			if (pc_tree->bGetFixed())
				cout << "Drzewo zostalo naprawione przez program i moze nie wskazywac zadanych wartosci";
		}
		else {
			cout << "Niepoprawne polecenie! Sprobuj ponownie." << endl;
		}
	}
}