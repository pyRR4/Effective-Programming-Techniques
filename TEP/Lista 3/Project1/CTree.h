#pragma once
#include "CNode.h"
class CTree
{
private:
	CNode* pc_root;
	int i_depth;
public:
	CTree();
	CTree(CNode* pcRoot);
	~CTree();
};