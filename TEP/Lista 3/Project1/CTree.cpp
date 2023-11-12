#include "CTree.h"

CTree::CTree()
{
	pc_root = nullptr;
	i_depth = 0;
}

CTree::CTree(CNode* pcRoot) {
	pc_root = pcRoot;
}

CTree::~CTree()
{
	delete pc_root;
}
