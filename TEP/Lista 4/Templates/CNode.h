#pragma once
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include "CString.h"
#include "CBool.h"

using namespace std;

static const char DEFAULT_VALUE = ' ';
static const char MULTIPLICATION = '*';
static const char DIVISION = '/';
static const char ADDITION = '+';
static const char SUBSTRACTION = '-';
static const string SIN = "sin";
static const string COS = "cos";
static const string SUPERSUM = "supersum";
static const string INT = "int";
static const string BOOL = "bool";
static const string DOUBLE = "double";
static const string STRING = "string";
static const string UNKNOWN = "unknown";

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

bool isStringVariable(string sValue)
{
	if (sValue[0] == '"' && sValue[sValue.length() - 1] == '"')
		return false;
	return true;
}

bool isBoolVariable(string sValue)
{
	if (sValue == "1" || sValue == "0")
		return false;
	return true;
}

bool bValue(string sValue) {
	if (stoi(sValue) == 1)
		return true;
	else
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
			if (sGetKnownType() == BOOL)
				throw new invalid_argument("Wezel nie moze przyjmowac 1 lub wiecej niz 2 argumentow!");
			if (sGetKnownType() == STRING) {
				pc_children = new CNode[0];
				pc_children = 0;
			}
			pc_children = new CNode[1];
			i_children = 1;
		}
		else if (c_value.compare(SUPERSUM) == 0) {
			if(sGetKnownType() == BOOL)
				throw new invalid_argument("Wezel nie moze przyjmowac 1 lub wiecej niz 2 argumentow!");
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
	~CNode() {
		if(pc_children != nullptr)
			delete[] pc_children;
	}
	CString sGetKnownType();
	string sPrefix(string toAppend);
	CNode* pcGetChildren();
	CNode* pcGetParent();
	void vSetParent(CNode* pcParent);
	int iGetChildren();
	int iGetCurrChildren();
	void vSetCurrChildren(int iNewValue);
	T tNodeValue(map<string, string> mVars);
	string sGetValue();
};



template <>
CString CNode<int>::sGetKnownType()
{
	CString s_type;
	s_type = INT;
	return s_type;
}

template <>
CString CNode<double>::sGetKnownType()
{
	CString s_type;
	s_type = DOUBLE;
	return s_type;
}

template <>
CString CNode<string>::sGetKnownType()
{
	CString s_type;
	s_type = STRING;
	return s_type;
}
template <>
CString CNode<bool>::sGetKnownType()
{
	CString s_type;
	s_type = BOOL;
	return s_type;
}

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

template <>
double CNode<double>::tNodeValue(map<string, string> mVars) //tuuuuuuu
{
	if (i_children == 0)
		if (!isVariable(c_value))
			return stod(c_value);
		else {
			return stod(mVars[this->c_value]);
		}
	else if (i_children == 1)
		if (c_value.compare(SIN) == 0)
			return sin(pc_children[0].tNodeValue(mVars));
		else
			return cos(pc_children[0].tNodeValue(mVars));
	else if (i_children == 2)
		switch (c_value[0]) {
		case MULTIPLICATION:
			return (pc_children[0].tNodeValue(mVars) * pc_children[1].tNodeValue(mVars));
			break;
		case DIVISION:
			return (pc_children[0].tNodeValue(mVars) / pc_children[1].tNodeValue(mVars));
			break;
		case SUBSTRACTION:
			return (pc_children[0].tNodeValue(mVars) - pc_children[1].tNodeValue(mVars));
			break;
		case ADDITION:
			return (pc_children[0].tNodeValue(mVars) + pc_children[1].tNodeValue(mVars));
			break;
		}
	else if (i_children == 4) {
		return (pc_children[0].tNodeValue(mVars) + pc_children[1].tNodeValue(mVars) + pc_children[2].tNodeValue(mVars) + pc_children[3].tNodeValue(mVars));
	}
}
template <>
int CNode<int>::tNodeValue(map<string, string> mVars) //tuuuuuuu
{
	if (i_children == 0)
		if (!isVariable(c_value))
			return stoi(c_value);
		else {
			return stoi(mVars[this->c_value]);
		}
	else if (i_children == 1)
		if (c_value.compare(SIN) == 0)
			return (int)sin(pc_children[0].tNodeValue(mVars));
		else
			return (int)cos(pc_children[0].tNodeValue(mVars));
	else if (i_children == 2)
		switch (c_value[0]) {
		case MULTIPLICATION:
			return (pc_children[0].tNodeValue(mVars) * pc_children[1].tNodeValue(mVars));
			break;
		case DIVISION:
			return (pc_children[0].tNodeValue(mVars) / pc_children[1].tNodeValue(mVars));
			break;
		case SUBSTRACTION:
			return (pc_children[0].tNodeValue(mVars) - pc_children[1].tNodeValue(mVars));
			break;
		case ADDITION:
			return (pc_children[0].tNodeValue(mVars) + pc_children[1].tNodeValue(mVars));
			break;
		}
	else if (i_children == 4) {
		return (pc_children[0].tNodeValue(mVars) + pc_children[1].tNodeValue(mVars) + pc_children[2].tNodeValue(mVars) + pc_children[3].tNodeValue(mVars));
	}
}
template <>
string CNode<string>::tNodeValue(map<string, string> mVars) {
	if (i_children == 0)
		if (!isStringVariable(c_value))
			return c_value.substr(1, c_value.size() - 2);
		else {
			return mVars[this->c_value];
		}
	else if (i_children == 2) {
		CString cChild1 = pc_children[0].tNodeValue(mVars);
		CString cChild2 = pc_children[1].tNodeValue(mVars);
		switch (c_value[0]) {
		case MULTIPLICATION:
			return (cChild1 * cChild2).sToString();
			break;
		case DIVISION:
			return (cChild1 / cChild2).sToString();
			break;
		case SUBSTRACTION:
			return (cChild1 - cChild2).sToString();
			break;
		case ADDITION:
			return (cChild1 + cChild2).sToString();
			break;
		}
	}
	else if (i_children == 4) {
		CString cChild1 = pc_children[0].tNodeValue(mVars);
		CString cChild2 = pc_children[1].tNodeValue(mVars);
		CString cChild3 = pc_children[2].tNodeValue(mVars);
		CString cChild4 = pc_children[3].tNodeValue(mVars);
		return (cChild1 + cChild2 + cChild3 + cChild4).sToString();
	}
}
template <>
bool CNode<bool>::tNodeValue(map<string, string> mVars) {
	if (i_children == 0)
		if (!isBoolVariable(c_value))
			return bValue(c_value);
		else {
			return bValue(mVars[this->c_value]);
		}
	else if (i_children == 2) {
		CBool cChild1 = pc_children[0].tNodeValue(mVars);
		CBool cChild2 = pc_children[1].tNodeValue(mVars);
		switch (c_value[0]) {
		case MULTIPLICATION:
			return (cChild1 * cChild2).bGetValue();
			break;
		case DIVISION:
			return (cChild1 / cChild2).bGetValue();
			break;
		case SUBSTRACTION:
			return (cChild1 - cChild2).bGetValue();
			break;
		case ADDITION:
			return (cChild1 + cChild2).bGetValue();
			break;
		}
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

