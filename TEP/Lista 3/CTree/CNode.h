#pragma once
#include <string>
#include <map>

using namespace std;

class CNode
{
private:
	int i_children;
	int i_currChildren;
	string c_value;
	CNode* pc_parent;
	CNode* pc_children;
public:
	CNode();
	CNode(string cValue, CNode* pcParent);
	CNode(const CNode& pcOther);
	~CNode();
	string sPrefix(string toAppend);
	CNode* pcGetChildren();
	CNode* pcGetParent();
	void vSetParent(CNode* pcParent);
	int iGetChildren();
	int iGetCurrChildren();
	void vSetCurrChildren(int iNewValue);
	double iNodeValue(map<string, double> mVars);
	string sGetValue();
};

static const char DEFAULT_VALUE = ' ';
static const char MULTIPLICATION = '*';
static const char DIVISION = '/';
static const char ADDITION = '+';
static const char SUBSTRACTION = '-';
static const string SIN = "sin";
static const string COS = "cos";
static const string SUPERSUM = "supersum";

