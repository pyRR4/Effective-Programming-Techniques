#pragma once
#include <string>

using namespace std;

class CNode
{
private:
	string c_value;
	CNode* pc_parent;
	CNode* pc_children;
public:
	CNode();
	CNode(string cValue, CNode* cnParent);
	~CNode();
	CNode* getChildren();
	CNode* getParent();
	int iDepth();
};

static const char DEFAULT_VALUE = ' ';

