#include "CNumber.h"
#include <iostream>

CNumber::CNumber()
{
	i_length = DEFAULT_LENGTH;
	pi_number = new int[i_length];
	operator=(DEFAULT_NUM);
	cout << "bezparam: " << toStr() << endl;
}

CNumber::CNumber(int iNumber, int iLength) 
{
	i_length = iLength;
	pi_number = new int[i_length];
	operator=(iNumber);
	cout << "param: " << toStr() << endl;
}

CNumber::~CNumber()
{
	delete pi_number;
	cout << "usuwam: " << toStr() << endl;
}

void CNumber::operator=(const int iValue)
{
	int x = iValue;
	for (int i = i_length; i >= 0; i--) {
		pi_number[i] = x % 10;
		x /= 10;
	}
	if (!(x < 10))
		cout << "brak miejsca na ca³¹ liczbe" << endl; //ogarnij to
}

void CNumber::operator=(const CNumber& pcOther)
{
	pi_number = pcOther.pi_number;
	i_length = pcOther.i_length;
}

string CNumber::toStr()
{

	return "";
}
