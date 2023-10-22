#pragma once
#include <string>

using namespace std;

class CTable
{
private:
	int* cTable;
	string s_name;
	int i_table_len;
public:
	CTable();
	CTable(string sName, int iTableLen);
	CTable(const CTable& pcOther);
	~CTable();
	void vSetName(string sName);
	bool bSetNewSize(int iTableLen);
	CTable* pcClone();
	void statePrinter();
};
static const string DEFAULT_NAME = "name";
static const int DEFAULT_SIZE = 5;

void v_mod_tab(CTable* pcTab, int iNewSize);
void v_mod_tab(CTable pcTab, int iNewSize);

