#include "CNumber.h"
#include <iostream>

CNumber::CNumber()
{
	i_length = DEFAULT_LENGTH;
	pi_number = new int[i_length];
	operator=(DEFAULT_NUM);
	cout << "bezparam: " << endl;
}

CNumber::CNumber(int iNumber, int iLength) 
{
	i_length = iLength;
	pi_number = new int[i_length];
	operator=(iNumber);
	cout << "param: " << endl;
}

CNumber::~CNumber()
{
	delete pi_number;
	cout << "usuwam: " << endl;
}

string CNumber::sToStr()
{
	string retValue = "";
	for (int i = 0; i < i_length; i++)
		retValue += pi_number[i];
	return retValue;
}




void CNumber::operator=(const int iValue)
{
	int x = iValue;
	int int_length = intLength(x);
	if (i_length < int_length)
		reallocate(int_length);
	for (int i = i_length; i >= 0; i--) {
		pi_number[i] = x % 10;
		x /= 10;
	}
}



void CNumber::operator=(const CNumber& pcOther)
{
	pi_number = pcOther.pi_number;
	i_length = pcOther.i_length;
}

void CNumber::reallocate(int iLength)
{
	i_length = iLength;
	delete pi_number;
	pi_number = new int[i_length];
}


int intLength(int iVal)
{
	int result = 0;
	while (iVal != 0) {
		result++;
		iVal / 10;
	}
	return result;
}


int main() {
	CNumber* num = new CNumber();
	CNumber* num1 = new CNumber(5, 1);

	*num = 3215;
	*num1 = 2314439;

	num->sToStr();
	num1->sToStr();

	return 0;
}
