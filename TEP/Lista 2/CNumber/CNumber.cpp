#include "CNumber.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

CNumber::CNumber()
{
	i_length = DEFAULT_LENGTH;
	pi_number = new int[i_length];
	operator=(DEFAULT_NUM);
	cout << "bezparam: " << sToStr() << endl;
}

CNumber::CNumber(int iNumber, int iLength) 
{
	i_length = iLength;
	pi_number = new int[i_length];
	operator=(iNumber);
	cout << "param: " << sToStr() << endl;
}

CNumber::~CNumber() {
	cout << "usuwam: " << sToStr() << endl;
	delete pi_number;
}

void CNumber::operator=(const int iValue)
{
	int x = iValue;
	int val_length = intLength(x);
	if (i_length < val_length) {
		i_length = val_length;
		
		delete pi_number;
		pi_number = new int[i_length];
	}
	for (int i = i_length - 1; i >= 0; i--) {
		pi_number[i] = x % 10;
		x = x / 10;
	}
	cout << "przypisano wartosc " << iValue << endl;
}



void CNumber::operator=(const CNumber& pcOther)
{
	pi_number = pcOther.pi_number;
	i_length = pcOther.i_length;
}

string CNumber::sToStr()
{
	ostringstream oss;
	for (int i = 0; i < i_length; i++)
		oss << pi_number[i];
	return oss.str();
}

int intLength(int iVal)
{
	int iResult = 0;
	while (iVal != 0) {
		iResult++;
		iVal = iVal / 10;
	}
	return iResult;
}


int main() {

	CNumber num2, num3;
	num2 = 368;
	num3 = 1567;
	num2 = num3;


	cout << num2.sToStr() << endl;
	cout << num3.sToStr() << endl;

	return 0;
}
