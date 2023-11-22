#include "CTree.h"
#include <sstream>
#include <iostream>

CTree::CTree()
{
	pc_root = nullptr;
	b_fixed = false;
}

CTree::CTree(CNode* pcRoot) 
{
	pc_root = pcRoot;
	b_fixed = false;
}

CTree::CTree(vector<string> vFormula)
{
	b_fixed = false;
	pc_root = new CNode(vFormula[0], nullptr);
	if (pc_root->iGetChildren() == 0 && isVariable(pc_root->sGetValue()))
		m_variables[pc_root->sGetValue()] = NULL;
	CNode* pcParent = pc_root;
	CNode* pcChild = pc_root;
	for (int i = 1; i < vFormula.size(); i++) {
		while ((pcParent->pcGetParent() != nullptr) && pcParent->iGetChildren() == pcParent->iGetCurrChildren()) {
			pcParent = pcParent->pcGetParent();
		}
		if (pcParent->iGetChildren() != pcParent->iGetCurrChildren()) {
			pcChild = new CNode(vFormula[i], pcParent);
			pcParent->pcGetChildren()[pcParent->iGetCurrChildren()] = *pcChild;
			if (pcChild->iGetChildren() == 0 && isVariable(pcChild->sGetValue()))
				m_variables[(pcParent->pcGetChildren()[pcParent->iGetCurrChildren()]).sGetValue()] = NULL;
			pcParent->vSetCurrChildren(pcParent->iGetCurrChildren() + 1);
			pcParent = &(pcParent->pcGetChildren()[pcParent->iGetCurrChildren() - 1]);
		}
		else {
			b_fixed = true;
		}
	}
	if (pcParent->iGetChildren() != pcParent->iGetCurrChildren()) {
		b_fixed = true;
	}
	while (pcParent->iGetChildren() != pcParent->iGetCurrChildren()) {
		switch ((pcParent->sGetValue())[0]) {
		case ADDITION:
			pcChild = new CNode(ADDITION_DEFAULT, pcParent);
			break;
		case SUBSTRACTION:
			pcChild = new CNode(ADDITION_DEFAULT, pcParent);
			break;
		case MULTIPLICATION:
			pcChild = new CNode(MULTIPLICATION_DEFAULT, pcParent);
			break;
		case DIVISION:
			pcChild = new CNode(MULTIPLICATION_DEFAULT, pcParent);
			break;
		}
		pcParent->pcGetChildren()[pcParent->iGetCurrChildren()] = *pcChild;
		pcParent->vSetCurrChildren(pcParent->iGetCurrChildren() + 1);
		if(pcParent->pcGetParent() != nullptr && pcParent->iGetChildren() == pcParent->iGetCurrChildren())
			pcParent = pcParent->pcGetParent();
	}
}

CTree::CTree(const CTree& pcOther)
{
	b_fixed = pcOther.b_fixed;
	pc_root = new CNode(*pcOther.pc_root);
	map<string, double> mTmpMap = pcOther.m_variables;
	map<string, double>::iterator it;
	for (it = mTmpMap.begin(); it != mTmpMap.end(); it++)
		m_variables[it->first] = it->second;
}

CTree::~CTree()
{
	delete pc_root;
}

double CTree::dTreeValue()
{
	return pc_root->iNodeValue(m_variables);
}

string CTree::sVarsToStr()
{
	map<string, double>::iterator itr;
	string sRetValue;
	for (itr = m_variables.begin(); itr != m_variables.end(); itr++)
		sRetValue += ((*itr).first + DEFAULT_VALUE);
	return sRetValue;
}

string CTree::sPrefix()
{
	return pc_root->sPrefix("");
}

bool CTree::bGetFixed()
{
	return b_fixed;
}

bool CTree::bSetVars(vector<string> vValues)
{
	if (vValues.size() != m_variables.size()) {
		cout << "Podano niepoprawna ilosc zmiennych!" << endl;
		return false;
	}
	if (m_variables.size() == 0)
		return true;
	map<string, double>::iterator itr;
	int i = 0;
	for (itr = m_variables.begin(); itr != m_variables.end(); itr++) {
		(*itr).second = stod(vValues[i]);
		i++;
	}
	return true;
}

map<string, double> CTree::mGetVars()
{
	return m_variables;
}

void CTree::vJoin(CTree* pcNewTree)
{
	*this = *this + *pcNewTree;
}

void CTree::operator=(const CTree& pcNewTree)
{
	delete pc_root;
	pc_root = new CNode(*pcNewTree.pc_root);
	m_variables.clear();
	map<string, double> mTmpMap = pcNewTree.m_variables;
	map<string, double>::iterator it;
	for (it = mTmpMap.begin(); it != mTmpMap.end(); it++)
		m_variables[it->first] = it->second;
}

CTree CTree::operator+(const CTree& pcNewTree)
{
	CTree* pcRetValue = new CTree(*this);
	CTree* pcAddedElement = new CTree(pcNewTree);
	CNode* cTmp = (pcRetValue->pc_root);
	while (cTmp->iGetChildren() != 0) {
		cTmp = &cTmp->pcGetChildren()[0];
	}
	if (isVariable(cTmp->sGetValue()))
		pcRetValue->m_variables.erase(cTmp->sGetValue());
	CNode* pcParent = cTmp->pcGetParent();
	pcParent->pcGetChildren()[0] = *pcAddedElement->pc_root;
	pcAddedElement->pc_root->vSetParent(pcParent);

	map<string, double>::iterator it;
	for (it = pcAddedElement->m_variables.begin(); it != pcAddedElement->m_variables.end(); it++)
		pcRetValue->m_variables[it->first] = it->second;

	pcAddedElement = nullptr;
	pcParent = nullptr;
	return (*pcRetValue);
}

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
