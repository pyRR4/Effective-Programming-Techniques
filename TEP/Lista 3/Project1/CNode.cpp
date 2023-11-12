#include "CNode.h"
#include <iostream>
#include <string>

using namespace std;


CNode::CNode()
{
	c_value = DEFAULT_VALUE;
	pc_children = nullptr;
	pc_parent = nullptr;
}

CNode::CNode(string cValue, CNode* cnParent)
{
	c_value = cValue;
	pc_parent = cnParent;
	if (isdigit(cValue[0]))
		pc_children = nullptr;
	else
		if (c_value[0] == '*' || c_value[0] == '-' || c_value[0] == '/' || c_value[0] == '+')
			pc_children = new CNode[2];
		else
			pc_children = new CNode[1];
}

CNode::~CNode()
{
	delete[] pc_children;
	delete pc_parent;
}

CNode* CNode::getChildren()
{
	return pc_children;
}

CNode* CNode::getParent()
{
	return pc_parent;
}

int CNode::iDepth()
{
	int depth = 1;
	if (pc_children != nullptr) {
		
	}
	return depth;
}

