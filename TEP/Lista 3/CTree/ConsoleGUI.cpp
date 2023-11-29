#include "ConsoleGUI.h"
#include <string>
#include <iostream>


ConsoleGUI::ConsoleGUI()
{
	s_formula = "";
	pc_tree = nullptr;
}

void ConsoleGUI::vAsker()
{
	while (true) {
		cout << endl << "===============================" << endl;
		cout << "Wpisz jedna z ponizszych komend:" << endl;
		cout << "1. Wprowadz nowa formule: enter <formula>" << endl;
		//cout << "2. Wprowadz SuperSume: supersum <formula>" << endl;
		cout << "2. Wyswietl zmienne w formule: vars" << endl;
		cout << "3. Oblicz formule dla podanych zmiennych: comp <var1> <var2> ... <varN> [ILOSC WARTOSCI MUSI BYC TAKA SAMA JAK ZMIENNYCH WYSWIETLONYCH PRZEZ VARS!!!]" << endl;
		cout << "4. Wyswietl formule w postaci prefiksowej: print" << endl;
		cout << "5. Dolacz nowa formule do aktualnej: join <formula>" << endl;
		cout << "6. Wyjdz: quit" << endl << endl;
		string sInput;
		getline(cin, sInput);
		if (sInput == QUIT) {
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
					cout << "Wartosc formuly wynosi: " << pc_tree->dTreeValue() << endl;
			}
			else
				cout << "Nie podano drzewa!" << endl;
		}
		else if (sKey.compare(JOIN) == 0) {
			if (pc_tree != nullptr) {
				pc_tree->vJoin(new CTree(vecInput));
				if (pc_tree->bGetFixed())
					cout << "Drzewo zostalo naprawione przez program i moze nie wskazywac zadanych wartosci";
			}
			else
				cout << "Nie podano drzewa!" << endl;
		}
		else if (sKey.compare(ENTER) == 0) {
			delete pc_tree;
			pc_tree = new CTree(vecInput);
			if (pc_tree->bGetFixed())
				cout << "Drzewo zostalo naprawione przez program i moze nie wskazywac zadanych wartosci";
		}
		/*else if (sKey.compare(SUPERSUM) == 0) {
			if (vecInput.size() != 4)
				cout << "Niepoprawna liczba argumentow!" << endl;
			else {
				delete pc_tree;
				string sModifiedInput = sSuperSumInput(vecInput);
				pc_tree = new CTree(vStrToVec(sModifiedInput));
			}
		}*/
		else {
			cout << "Niepoprawne polecenie! Sprobuj ponownie." << endl;
		}
	}
}

string sSuperSumInput(vector<string> vecValues)
{
	string superSumInput = "";
	for (int i = 0; i < vecValues.size(); i++) {
		if (i == 0) {
			superSumInput += ADDITION;
			superSumInput += DEFAULT_VALUE;
			superSumInput += ADDITION;
		}
		else if (i == 2) {
			superSumInput += DEFAULT_VALUE;
			superSumInput += ADDITION;
		}
		superSumInput += DEFAULT_VALUE;
		superSumInput += vecValues[i];
	}
	return superSumInput;
}