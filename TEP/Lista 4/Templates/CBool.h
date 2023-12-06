#pragma once
#include <string>

using namespace std;

class CBool
{
private:
	bool b_value;
public:
	CBool();
	CBool(string sValue);
	CBool(bool bValue);
	void operator=(const CBool& pcOther);
	void operator=(const bool& pcOther);
	CBool operator+(const CBool& pcOther);
	CBool operator-(const CBool& pcOther);
	CBool operator/(const CBool& pcOther);
	CBool operator*(const CBool& pcOther);
	bool bGetValue();
};

