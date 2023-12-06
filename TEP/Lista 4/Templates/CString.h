#pragma once
#include <string>
#include <iostream>

using namespace std;

class CString
{
private:
	string s_value;
public:
	CString();
	CString(string sValue);
	void operator=(const CString& pcOther);
	void operator=(const string& pcOther);
	bool operator==(const string& pcOther);
	bool operator==(const CString& pcOther);
	CString operator+(const CString& pcOther);
	CString operator-(const CString& pcOther);
	CString operator/(const CString& pcOther);
	CString operator*(const CString& pcOther);
	string sToString();
};

