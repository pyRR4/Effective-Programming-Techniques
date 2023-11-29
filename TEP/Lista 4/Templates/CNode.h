#pragma once
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

static const char DEFAULT_VALUE = ' ';
static const char MULTIPLICATION = '*';
static const char DIVISION = '/';
static const char ADDITION = '+';
static const char SUBSTRACTION = '-';
static const string SIN = "sin";
static const string COS = "cos";
static const string SUPERSUM = "supersum";

vector<string> vStrToVec(string sInput)
{
	vector<string> vecResult;
	stringstream ss(sInput);
	string sTmp;
	while (getline(ss, sTmp, DEFAULT_VALUE)) {
		vecResult.push_back(sTmp);
	}
	return vecResult;
}

string sVecToStr(vector<string> vecInput, char cConnector)
{
	string sRetValue = vecInput[0];
	for (int i = 1; i < vecInput.size(); i++) {
		sRetValue += DEFAULT_VALUE;
		sRetValue += cConnector;
		sRetValue += DEFAULT_VALUE;
		sRetValue += vecInput[i];
	}
	return sRetValue;
}

bool isVariable(string sValue)
{
	for (int i = 0; i < sValue.length(); i++) {
		if (!isdigit(sValue[i]))
			return true;
	}
	return false;
}

template <typename T> class CNode
{
private:
	int i_children;
	int i_currChildren;
	string c_value;
	CNode* pc_parent;
	CNode* pc_children;
public:
	CNode() {
		c_value = DEFAULT_VALUE;
		pc_children = nullptr;
		pc_parent = nullptr;
		i_children = 0;
		i_currChildren = 0;
	}
	CNode(string cValue, CNode* pcParent) {
		c_value = cValue;
		pc_parent = pcParent;
		i_currChildren = 0;
		if (c_value[0] == MULTIPLICATION || c_value[0] == SUBSTRACTION || c_value[0] == DIVISION || c_value[0] == ADDITION) {
			pc_children = new CNode[2];
			i_children = 2;
		}
		else if (c_value.compare(SIN) == 0 || c_value.compare(COS) == 0) {
			pc_children = new CNode[1];
			i_children = 1;
		}
		else if (c_value.compare(SUPERSUM) == 0) {
			pc_children = new CNode[4];
			i_children = 4;
			c_value = ADDITION;
		}
		else {
			pc_children = nullptr;
			i_children = 0;
		}
	}
	CNode(const CNode& pcOther) {
		c_value = pcOther.c_value;
		i_children = pcOther.i_children;
		i_currChildren = pcOther.i_currChildren;
		if (pcOther.pc_parent == nullptr)
			pc_parent = nullptr;
		switch (i_children) {
		case 0:
			pc_children = nullptr;
			break;
		case 1:
			pc_children = new CNode(*pcOther.pc_children);
			break;
		case 2:
			pc_children = new CNode[2];
			pc_children[0] = *(new CNode(pcOther.pc_children[0]));
			pc_children[0].vSetParent(this);
			pc_children[1] = *(new CNode(pcOther.pc_children[1]));
			pc_children[1].vSetParent(this);
			break;
		case 4:
			pc_children[0] = *(new CNode(pcOther.pc_children[0]));
			pc_children[0].vSetParent(this);
			pc_children[1] = *(new CNode(pcOther.pc_children[1]));
			pc_children[1].vSetParent(this);
			pc_children[2] = *(new CNode(pcOther.pc_children[2]));
			pc_children[2].vSetParent(this);
			pc_children[3] = *(new CNode(pcOther.pc_children[3]));
			pc_children[3].vSetParent(this);
			break;
		}
	}
	~CNode()
	{
		delete[] pc_children;
	}
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

template <typename T>
string CNode<T>::sPrefix(string toAppend)
{
	toAppend += c_value;
	if (i_children == 1)
		toAppend += (DEFAULT_VALUE + pc_children->sPrefix(""));
	if (i_children == 2) {
		toAppend += (DEFAULT_VALUE + pc_children[0].sPrefix(""));
		toAppend += (DEFAULT_VALUE + pc_children[1].sPrefix(""));
	}
	if (i_children == 4) {
		toAppend += (DEFAULT_VALUE + pc_children[0].sPrefix(""));
		toAppend += (DEFAULT_VALUE + pc_children[1].sPrefix(""));
		toAppend += (DEFAULT_VALUE + pc_children[2].sPrefix(""));
		toAppend += (DEFAULT_VALUE + pc_children[3].sPrefix(""));
	}

	return toAppend;
}

template <typename T>
double CNode<T>::iNodeValue(map<string, double> mVars) //tuuuuuuu
{
	if (i_children == 0)
		if (!isVariable(c_value))
			return stod(c_value);
		else {
			return mVars[this->c_value];
		}
	else if (i_children == 1)
		if (c_value.compare(SIN) == 0)
			return sin(pc_children[0].iNodeValue(mVars));
		else
			return cos(pc_children[0].iNodeValue(mVars));
	else if (i_children == 2)
		switch (c_value[0]) {
		case MULTIPLICATION:
			return (pc_children[0].iNodeValue(mVars) * pc_children[1].iNodeValue(mVars));
			break;
		case DIVISION:
			return (pc_children[0].iNodeValue(mVars) / pc_children[1].iNodeValue(mVars));
			break;
		case SUBSTRACTION:
			return (pc_children[0].iNodeValue(mVars) - pc_children[1].iNodeValue(mVars));
			break;
		case ADDITION:
			return (pc_children[0].iNodeValue(mVars) + pc_children[1].iNodeValue(mVars));
			break;
		}
	else {
		return (pc_children[0].iNodeValue(mVars) + pc_children[1].iNodeValue(mVars) + pc_children[2].iNodeValue(mVars) + pc_children[3].iNodeValue(mVars));
	}
}

template <typename T>
string CNode<T>::sGetValue()
{
	return c_value;
}

template <typename T>
CNode<T>* CNode<T>::pcGetChildren()
{
	return pc_children;
}

template <typename T>
CNode<T>* CNode<T>::pcGetParent()
{
	return pc_parent;
}

template <typename T>
void CNode<T>::vSetParent(CNode<T>* pcParent)
{
	pc_parent = pcParent;
}

template <typename T>
int CNode<T>::iGetChildren()
{
	return i_children;
}

template <typename T>
int CNode<T>::iGetCurrChildren()
{
	return i_currChildren;
}

template <typename T>
void CNode<T>::vSetCurrChildren(int iNewValue)
{
	i_currChildren = iNewValue;
}

