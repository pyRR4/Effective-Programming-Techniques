#include "CBool.h"

CBool::CBool()
{
	b_value = true;
}

CBool::CBool(string sValue)
{
	if (stoi(sValue) == 0)
		b_value = false;
	else
		b_value = true;
}

CBool::CBool(bool bValue)
{
	b_value = bValue;
}

void CBool::operator=(const CBool& pcOther)
{
	b_value = pcOther.b_value;
}

void CBool::operator=(const bool& pcOther)
{
	b_value = pcOther;
}

CBool CBool::operator+(const CBool& pcOther)
{
	CBool cBool;
	cBool = true;
	if (!b_value && !pcOther.b_value)
		cBool = false;
	return cBool;
}

CBool CBool::operator-(const CBool& pcOther)
{
	CBool cBool;
	cBool = false;
	if (b_value)
		if (!pcOther.b_value)
			cBool = true;
	return cBool;
}

CBool CBool::operator/(const CBool& pcOther)
{
	CBool cBool;
	cBool = false;
	if (pcOther.b_value == b_value)
		cBool = true;
	return cBool;
}

CBool CBool::operator*(const CBool& pcOther)
{
	CBool cBool;
	cBool = false;
	if (pcOther.b_value && b_value)
		cBool = true;
	return cBool;
}

bool CBool::bGetValue()
{
	return b_value;
}
