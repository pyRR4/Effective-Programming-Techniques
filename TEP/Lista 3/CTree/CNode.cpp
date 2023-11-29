#include "CNode.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include "CTree.h"

using namespace std;


CNode::CNode()
{
	c_value = DEFAULT_VALUE;
	pc_children = nullptr;
	pc_parent = nullptr;
	i_children = 0;
	i_currChildren = 0;
}

CNode::CNode(string cValue, CNode* cnParent)
{
	c_value = cValue;
	pc_parent = cnParent;
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

CNode::CNode(const CNode &pcOther)
{
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

CNode::~CNode()
{
	delete[] pc_children;
}

string CNode::sPrefix(string toAppend)
{
	toAppend += c_value;
	if (i_children == 1)
		toAppend += (DEFAULT_VALUE + pc_children->sPrefix(""));
	if (i_children == 2) {
		toAppend += (DEFAULT_VALUE + pc_children[0].sPrefix(""));
		toAppend += (DEFAULT_VALUE + pc_children[1].sPrefix(""));
	}
	if(i_children == 4) {
		toAppend += (DEFAULT_VALUE + pc_children[0].sPrefix(""));
		toAppend += (DEFAULT_VALUE + pc_children[1].sPrefix(""));
		toAppend += (DEFAULT_VALUE + pc_children[2].sPrefix(""));
		toAppend += (DEFAULT_VALUE + pc_children[3].sPrefix(""));
	}

	return toAppend;
}

double CNode::iNodeValue(map<string, double> mVars)
{
	if (i_children == 0)
		if (!isVariable(c_value))
			return stod(c_value);
		else {
			return mVars[this->c_value];
		}
	else if (i_children == 1)
		if(c_value.compare(SIN) == 0)
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

string CNode::sGetValue()
{
	return c_value;
}

CNode* CNode::pcGetChildren()
{
	return pc_children;
}

CNode* CNode::pcGetParent()
{
	return pc_parent;
}

void CNode::vSetParent(CNode* pcParent)
{
	pc_parent = pcParent;
}

int CNode::iGetChildren()
{
	return i_children;
}

int CNode::iGetCurrChildren()
{
	return i_currChildren;
}

void CNode::vSetCurrChildren(int iNewValue)
{
	i_currChildren = iNewValue;
}