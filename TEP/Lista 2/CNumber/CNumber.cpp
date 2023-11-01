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

void CNumber::reallocate(int iNewLength)
{
	
	int* newPiNum = new int[iNewLength];
	for (int i = 0; i < iNewLength; i++) {
		newPiNum[i] = pi_number[i];
	}
	i_length = iNewLength;
	delete pi_number;
	pi_number = newPiNum;
}

void CNumber::operator=(const int iValue)
{
	int iVal = iValue;
	int valLength = intLength(iVal);
	if (i_length < valLength) {
		i_length = valLength;
		
		delete pi_number;
		pi_number = new int[i_length];
	}
	for (int i = i_length - 1; i >= 0; i--) {
		if (iVal % 10 >= NUM_SYSTEM)
			cout << "wartosc niezgodna z przyjetym systemem liczbowym! nie przypisano wartosci na miejscu " << i + 1 << endl;
		else {
			pi_number[i] = iVal % 10;
			iVal = iVal / 10;
		}
	}
	cout << "przypisano wartosc " << iValue << endl;
}



void CNumber::operator=(const CNumber& pcOther)
{
	delete pi_number;
	i_length = pcOther.i_length;
	pi_number = new int[i_length];
	for (int i = 0; i < i_length; i++)
		pi_number[i] = pcOther.pi_number[i];
}

void CNumber::operator+(const int iValue)
{
	int iVal = iValue;
	int valLength = intLength(iValue);
	if (valLength >= i_length)
		reallocate(valLength + 1);
	for (int i = 0; i < valLength; i++) {
		pi_number[i] = pi_number[i] + (iVal % 10);
		iVal /= 10;
		if (pi_number[i] >= NUM_SYSTEM) {
			pi_number[i] = pi_number[i] % 10;
			pi_number[i + 1]++;
		}
	}
}

void CNumber::operator+(const CNumber& pcOther)
{
	if (pcOther.i_length >= i_length) {
		reallocate(pcOther.i_length + 1);
	}
	for (int i = 0; i < pcOther.i_length; i++) {
		pi_number[i] = pi_number[i] + pcOther.pi_number[i];
		if (pi_number[i] >= NUM_SYSTEM) {
			pi_number[i] = pi_number[i] % 10;
			pi_number[i + 1]++;
		}
	}
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

	num2 + num3;

	cout << num2.sToStr() << endl;

	return 0;
}
