#pragma once
#include "CNode.h"
#include <vector>
#include <map>

class CTree
{
private:
	CNode* pc_root;
	map<string, double> m_variables;
	bool b_fixed;
public:
	CTree();
	CTree(CNode* pcRoot);
	CTree(vector<string> vecFormula);
	CTree(const CTree &pcOther);
	~CTree();
	double dTreeValue();
	string sVarsToStr();
	string sPrefix();
	bool bGetFixed();
	bool bSetVars(vector<string> vecValues);
	map<string, double> mGetVars();
	void vJoin(CTree* pcNewTree);
	void operator=(const CTree& pcNewTree);
	CTree operator+(const CTree& pcNewTree);
};

vector<string> vStrToVec(string sInput);
string sVecToStr(vector<string> sInput, char cConnector);
bool isVariable(string sValue);

static const string MULTIPLICATION_DEFAULT = "1";
static const string ADDITION_DEFAULT = "0";