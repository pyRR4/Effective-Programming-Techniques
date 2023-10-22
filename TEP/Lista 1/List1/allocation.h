#pragma once
class Allocation {
public:
	static const int TABLE_VALUE = 34;
	static void v_alloc_table_fill_34(int iSize);
	static bool b_alloc_table_2_dim(int***  piTable, int iSizeX, int iSizeY);
	static bool b_dealloc_table_2_dim(int*** piTable, int iSizeX);
};