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
	map<string, string> m_variables;
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
		addVars(pc_root, pc_root);
		CNode<T>* pcParent = pc_root;
		CNode<T>* pcChild = pc_root;
		for (int i = 1; i < vecFormula.size(); i++) {
			while ((pcParent->pcGetParent() != nullptr) && pcParent->iGetChildren() == pcParent->iGetCurrChildren()) {
				pcParent = pcParent->pcGetParent();
			}
			if (pcParent->iGetChildren() != pcParent->iGetCurrChildren()) {
				pcChild = new CNode<T>(vecFormula[i], pcParent);
				pcParent->pcGetChildren()[pcParent->iGetCurrChildren()] = *pcChild;
				addVars(pcChild, pcParent);
				
				
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
		map<string, string> mTmpMap = pcOther.m_variables;
		map<string, string>::iterator it;
		for (it = mTmpMap.begin(); it != mTmpMap.end(); it++)
			m_variables[it->first] = it->second;
	}
	~CTree()
	{
		delete pc_root;
	}
	void addVars(CNode<T>* pcChild, CNode<T>* pcParent);
	CString sGetKnownType();
	T tTreeValue();
	string sVarsToStr();
	string sPrefix();
	bool bGetFixed();
	bool bSetVars(vector<string> vecValues);
	map<string, string> mGetVars();
	void vJoin(CTree* pcNewTree);
	void operator=(const CTree& pcNewTree);
	CTree operator+(const CTree& pcNewTree);
};


template<typename T>
void CTree<T>::addVars(CNode<T>* pcChild, CNode<T>* pcParent)
{
	if (pcChild->iGetChildren() == 0 && isVariable(pcChild->sGetValue()))
		m_variables[(pcParent->pcGetChildren()[pcParent->iGetCurrChildren()]).sGetValue()] = DEFAULT_VALUE;
}
template<>
void CTree<string>::addVars(CNode<string>* pcChild, CNode<string>* pcParent)
{
	if (pcChild->iGetChildren() == 0 && isStringVariable(pcChild->sGetValue()))
		m_variables[(pcParent->pcGetChildren()[pcParent->iGetCurrChildren()]).sGetValue()] = DEFAULT_VALUE;
}
template<>
void CTree<bool>::addVars(CNode<bool>* pcChild, CNode<bool>* pcParent)
{
	if (pcChild->iGetChildren() == 0 && isBoolVariable(pcChild->sGetValue()))
		m_variables[(pcParent->pcGetChildren()[pcParent->iGetCurrChildren()]).sGetValue()] = DEFAULT_VALUE;
}

template<typename T>
CString CTree<T>::sGetKnownType()
{
	return pc_root->sGetKnownType();
}

template<>
CString CTree<int>::sGetKnownType()
{
	return pc_root->sGetKnownType();
}

template<>
CString CTree<double>::sGetKnownType()
{
	return pc_root->sGetKnownType();
}

template<>
CString CTree<string>::sGetKnownType()
{
	return pc_root->sGetKnownType();
}

template <typename T>
T CTree<T>::tTreeValue()
{
	return pc_root->tNodeValue(m_variables);
}

template <typename T>
string CTree<T>::sVarsToStr()
{
	map<string, string>::iterator itr;
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
		return false;
	}
	if (m_variables.size() == 0)
		return true;
	map<string, string>::iterator itr;
	int i = 0;
	for (itr = m_variables.begin(); itr != m_variables.end(); itr++) {
		if (sGetKnownType() == STRING)
			if (!isStringVariable(vValues[i]))
				(*itr).second = vValues[i].substr(1, vValues[i].size() - 2);
			else
				return false;
		else if (sGetKnownType() == BOOL) {
			if (!isBoolVariable(vValues[i]))
				(*itr).second = vValues[i];
			else
				return false;
		}
		else
			if (!isVariable(vValues[i]))
				(*itr).second = vValues[i];
			else
				return false;
		i++;
	}
	return true;
}


template <typename T>
map<string, string> CTree<T>::mGetVars()
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
	map<string, string> mTmpMap = pcNewTree.m_variables;
	map<string, string>::iterator it;
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

	map<string, string>::iterator it;
	for (it = pcAddedElement->m_variables.begin(); it != pcAddedElement->m_variables.end(); it++)
		pcRetValue->m_variables[it->first] = it->second;

	pcAddedElement = nullptr;
	pcParent = nullptr;
	return (*pcRetValue);
}

