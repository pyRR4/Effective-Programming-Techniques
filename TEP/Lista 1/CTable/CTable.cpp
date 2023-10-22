#include "CTable.h"
#include <iostream>
#include <string>

using namespace std;

CTable::CTable() {
	s_name = DEFAULT_NAME;
	i_table_len = DEFAULT_SIZE;
	cTable = new int[i_table_len];
	cout << "bezp: " << s_name << endl;
}

CTable::CTable(string sName, int iTableLen) {
	if (iTableLen <= 0) {
		cout << "Niepoprawna dlugosc tablicy!" << endl;
		return;
	}
	s_name = sName;
	i_table_len = iTableLen;
	cTable = new int[i_table_len];
	cout << "parametr: " << s_name << endl;
}

CTable::CTable(const CTable& pcOther) {
	s_name = pcOther.s_name + "_copy";
	i_table_len = pcOther.i_table_len;
	cTable = new int[i_table_len];
	for (int index = 0; index < i_table_len; index++) {
		cTable[index] = pcOther.cTable[index];
	}
	cout << "kopiuj: " << s_name << endl;
}

CTable::~CTable() {
	delete cTable;
	cout << "usuwam: " << s_name << endl;
}

void CTable::vSetName(string sName) {
	s_name = sName;
}

bool CTable::bSetNewSize(int iNewLen) {
	if(iNewLen <= 0) {
		return false;
	}
	else {
		i_table_len = iNewLen;
		delete cTable;
		cTable = new int[i_table_len];
		return true;
	}
}

CTable* CTable::pcClone()
{
	return new CTable(*this);
}

void v_mod_tab(CTable* pcTab, int iNewSize)
{
	pcTab->bSetNewSize(iNewSize);
}

void v_mod_tab(CTable pcTab, int iNewSize)
{
	pcTab.bSetNewSize(iNewSize);
}

void CTable::statePrinter() {
	cout << "Nazwa: " << s_name << ", Rozmiar: " << i_table_len << endl;
}

int main() {
	CTable* dcTab = new CTable(); //default
	CTable* pcTab = new CTable("tab", 3); //param
	CTable* ccTab = new CTable(*pcTab); //copy

	dcTab->statePrinter();
	pcTab->statePrinter();
	ccTab->statePrinter();

	ccTab->pcClone(); //2x copy

	dcTab->bSetNewSize(-2);
	pcTab->bSetNewSize(12);

	dcTab->statePrinter();
	pcTab->statePrinter();

	ccTab->vSetName("copied tab");
	ccTab->statePrinter();

	v_mod_tab(dcTab, 20);
	v_mod_tab(*pcTab, 20);

	dcTab->statePrinter();
	pcTab->statePrinter();

}