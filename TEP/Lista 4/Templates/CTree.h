#pragma once
#include "CNode.h"
#include <vector>
#include <map>

using namespace std;

static const string MULTIPLICATION_DEFAULT = "1";
static const string ADDITION_DEFAULT = "0";

template <typename T> class CTree
{
private:
	CNode<T>* pc_root;
	map<string, double> m_variables;
	bool b_fixed;
public:
	CTree()
	{
		pc_root = nullptr;
		b_fixed = false;
	}
	CTree(CNode<T>* pcRoot)
	{
		pc_root = pcRoot;
		b_fixed = false;
	}
	CTree(vector<string> vecFormula)
	{
		b_fixed = false;
		pc_root = new CNode<T>(vecFormula[0], nullptr);
		if (pc_root->iGetChildren() == 0 && isVariable(pc_root->sGetValue()))
			m_variables[pc_root->sGetValue()] = NULL;
		CNode<T>* pcParent = pc_root;
		CNode<T>* pcChild = pc_root;
		for (int i = 1; i < vecFormula.size(); i++) {
			while ((pcParent->pcGetParent() != nullptr) && pcParent->iGetChildren() == pcParent->iGetCurrChildren()) {
				pcParent = pcParent->pcGetParent();
			}
			if (pcParent->iGetChildren() != pcParent->iGetCurrChildren()) {
				pcChild = new CNode<T>(vecFormula[i], pcParent);
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
				pcChild = new CNode<T>(ADDITION_DEFAULT, pcParent);
				break;
			case SUBSTRACTION:
				pcChild = new CNode<T>(ADDITION_DEFAULT, pcParent);
				break;
			case MULTIPLICATION:
				pcChild = new CNode<T>(MULTIPLICATION_DEFAULT, pcParent);
				break;
			case DIVISION:
				pcChild = new CNode<T>(MULTIPLICATION_DEFAULT, pcParent);
				break;
			}
			pcParent->pcGetChildren()[pcParent->iGetCurrChildren()] = *pcChild;
			pcParent->vSetCurrChildren(pcParent->iGetCurrChildren() + 1);
			if (pcParent->pcGetParent() != nullptr && pcParent->iGetChildren() == pcParent->iGetCurrChildren())
				pcParent = pcParent->pcGetParent();
		}
	}
	CTree(const CTree& pcOther)
	{
		b_fixed = pcOther.b_fixed;
		pc_root = new CNode<T>(*pcOther.pc_root);
		map<string, double> mTmpMap = pcOther.m_variables;
		map<string, double>::iterator it;
		for (it = mTmpMap.begin(); it != mTmpMap.end(); it++)
			m_variables[it->first] = it->second;
	}
	~CTree()
	{
		delete pc_root;
	}
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




template <typename T>
double CTree<T>::dTreeValue()
{
	return pc_root->iNodeValue(m_variables);
}

template <typename T>
string CTree<T>::sVarsToStr()
{
	map<string, double>::iterator itr;
	string sRetValue;
	for (itr = m_variables.begin(); itr != m_variables.end(); itr++)
		sRetValue += ((*itr).first + DEFAULT_VALUE);
	return sRetValue;
}

template <typename T>
string CTree<T>::sPrefix()
{
	return pc_root->sPrefix("");
}

template <typename T>
bool CTree<T>::bGetFixed()
{
	return b_fixed;
}

template <typename T>
bool CTree<T>::bSetVars(vector<string> vValues)
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

template <typename T>
map<string, double> CTree<T>::mGetVars()
{
	return m_variables;
}

template <typename T>
void CTree<T>::vJoin(CTree<T>* pcNewTree)
{
	*this = *this + *pcNewTree;
}

template <typename T>
void CTree<T>::operator=(const CTree<T>& pcNewTree)
{
	delete pc_root;
	pc_root = new CNode<T>(*pcNewTree.pc_root);
	m_variables.clear();
	map<string, double> mTmpMap = pcNewTree.m_variables;
	map<string, double>::iterator it;
	for (it = mTmpMap.begin(); it != mTmpMap.end(); it++)
		m_variables[it->first] = it->second;
}

template <typename T>
CTree<T> CTree<T>::operator+(const CTree<T>& pcNewTree)
{
	CTree* pcRetValue = new CTree(*this);
	CTree* pcAddedElement = new CTree(pcNewTree);
	CNode<T>* cTmp = (pcRetValue->pc_root);
	while (cTmp->iGetChildren() != 0) {
		cTmp = &cTmp->pcGetChildren()[0];
	}
	if (isVariable(cTmp->sGetValue()))
		pcRetValue->m_variables.erase(cTmp->sGetValue());
	CNode<T>* pcParent = cTmp->pcGetParent();
	pcParent->pcGetChildren()[0] = *pcAddedElement->pc_root;
	pcAddedElement->pc_root->vSetParent(pcParent);

	map<string, double>::iterator it;
	for (it = pcAddedElement->m_variables.begin(); it != pcAddedElement->m_variables.end(); it++)
		pcRetValue->m_variables[it->first] = it->second;

	pcAddedElement = nullptr;
	pcParent = nullptr;
	return (*pcRetValue);
}

