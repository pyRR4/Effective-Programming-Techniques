#pragma once
#include <string>
#include "CTree.h"

class ConsoleGUI
{
private:
	string s_formula;
	CTree* pc_tree;
public:
	ConsoleGUI();
	void vAsker();
};

string sSuperSumInput(vector<string> vecValues);

static const string JOIN = "join";
static const string PRINT = "print";
static const string COMP = "comp";
static const string ENTER = "enter";
static const string VARS = "vars";
static const string QUIT = "quit";

