#include "CNumber.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

CNumber::CNumber()
{
	i_length = DEFAULT_LENGTH;
	pi_number = new int[i_length];
	cout << "bezparam" << endl;
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
		if(i < i_length)
			newPiNum[iNewLength - 1 - i] = pi_number[i_length - 1 - i];
		else
			newPiNum[iNewLength - 1 - i] = 0;
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

CNumber CNumber::operator+(const int iValue)
{
	int iVal = iValue;
	int valLength = intLength(iValue);
	CNumber cRetValue;
	cRetValue = 0;
	if (valLength >= i_length) {
		cRetValue.reallocate(valLength + 1);
	}
	else {
		cRetValue.reallocate(i_length + 1);
	}
	for (int i = 1; i <= valLength; i++) {
		cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] + pi_number[i_length - i] + (iVal % 10);
		iVal /= 10;
		if (cRetValue.pi_number[cRetValue.i_length - i] >= NUM_SYSTEM) {
			cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] % 10;
			cRetValue.pi_number[cRetValue.i_length - i - 1]++;
		}
	}
	return cRetValue;
}

CNumber CNumber::operator+(const CNumber& pcOther)
{
	CNumber cRetValue;
	cRetValue = 0;
	if (pcOther.i_length >= i_length) {
		cRetValue.reallocate(pcOther.i_length + 1);
	}
	else {
		cRetValue.reallocate(i_length + 1);
	}
	for (int i = 1; i <= pcOther.i_length; i++) {
		cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] + pi_number[i_length - i] + pcOther.pi_number[pcOther.i_length - i];
		if (cRetValue.pi_number[cRetValue.i_length - i] >= NUM_SYSTEM) {
			cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] % 10;
			cRetValue.pi_number[cRetValue.i_length - 1 - i]++;
		}
	}
	return cRetValue;
}

CNumber CNumber::operator-(const int iValue)
{
	int iVal = iValue;
	int iValLength = intLength(iValue);
	CNumber cRetValue;
	cRetValue = 0;
	if (*this < iValue) {
		cRetValue.reallocate(iValLength);
		for (int i = 1; i <= cRetValue.i_length; i++) {
			cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] + (iVal % 10) - pi_number[i_length - i];
			iVal /= 10;
			if (cRetValue.pi_number[cRetValue.i_length - i] < 0) {
				cRetValue.pi_number[cRetValue.i_length - i] += 10;
				cRetValue.pi_number[cRetValue.i_length - i - 1]--;
			}
		}
		cout << "wynik ujemny" << endl;
	}
	else {
		cRetValue.reallocate(i_length);
		for (int i = 1; i <= cRetValue.i_length; i++) {
			cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] + pi_number[i_length - i] - (iVal % 10);
			iVal /= 10;
			if (cRetValue.pi_number[cRetValue.i_length - i] < 0) {
				cRetValue.pi_number[cRetValue.i_length - i] += 10;
				cRetValue.pi_number[cRetValue.i_length - i - 1]--;
			}
		}
	}
	return cRetValue;
}

CNumber CNumber::operator-(const CNumber& pcOther)
{
	CNumber cRetValue;
	cRetValue = 0;
	if (*this < pcOther) {
		cRetValue.reallocate(pcOther.i_length);
		for (int i = 1; i <= cRetValue.i_length; i++) {
			if (i < i_length)
				cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] + pcOther.pi_number[pcOther.i_length - i] - pi_number[i_length - i];
			else
				cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] + pcOther.pi_number[pcOther.i_length - i];
			if (cRetValue.pi_number[cRetValue.i_length - i] < 0) {
				cRetValue.pi_number[cRetValue.i_length - i] += 10;
				cRetValue.pi_number[cRetValue.i_length - i - 1]--;
			}
		}
		cout << "wynik ujemny" << endl;
	}
	else {
		cRetValue.reallocate(i_length);
		for (int i = 1; i <= cRetValue.i_length; i++) {
			if (i < pcOther.i_length)
				cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] + pi_number[i_length - i] - pcOther.pi_number[pcOther.i_length - i];
			else
				cRetValue.pi_number[cRetValue.i_length - i] = cRetValue.pi_number[cRetValue.i_length - i] + pi_number[i_length - i];
			if (cRetValue.pi_number[cRetValue.i_length - i] < 0) {
				cRetValue.pi_number[cRetValue.i_length - i] += 10;
				cRetValue.pi_number[cRetValue.i_length - i - 1]--;
			}
		}
	}
	return cRetValue;
}

CNumber CNumber::operator*(const int iValue)
{
	int iVal = iValue;
	int valLength = intLength(iValue);
	CNumber cRetValue; 
	cRetValue = 0;
	cRetValue.reallocate(valLength + i_length);
	if (valLength >= i_length) {
		for (int i = 0; i < i_length; i++) {
			for (int j = 1; j <= valLength; j++) {
				cRetValue.pi_number[cRetValue.i_length - i - j] = cRetValue.pi_number[cRetValue.i_length - i - j] + pi_number[i_length - i - 1] * (iVal % 10);
				if (cRetValue.pi_number[cRetValue.i_length - i - j] >= NUM_SYSTEM) {
					int iMove = cRetValue.pi_number[cRetValue.i_length - i - j] / 10;
					cRetValue.pi_number[cRetValue.i_length - i - j] = cRetValue.pi_number[cRetValue.i_length - i - j] % 10;
					cRetValue.pi_number[cRetValue.i_length - i - j - 1] += iMove;
				}
				iVal /= 10;
			}
			iVal = iValue;
		}
	}
	else {
		for (int i = 0; i < valLength; i++) {
			for (int j = 1; j <= i_length; j++) {
				cRetValue.pi_number[cRetValue.i_length - i - j] = cRetValue.pi_number[cRetValue.i_length - i - j] + pi_number[i_length - j] * (iVal % 10);
				if (cRetValue.pi_number[cRetValue.i_length - i - j] >= NUM_SYSTEM) {
					int iMove = cRetValue.pi_number[cRetValue.i_length - i - j] / 10;
					cRetValue.pi_number[cRetValue.i_length - i - j] = cRetValue.pi_number[cRetValue.i_length - i - j] % 10;
					cRetValue.pi_number[cRetValue.i_length - i - j - 1] += iMove;
				}
			}
			iVal /= 10;
		}
	}
	
	return cRetValue;
}

CNumber CNumber::operator*(const CNumber& pcOther)
{
	CNumber cRetValue;
	cRetValue = 0;
	cRetValue.reallocate(pcOther.i_length + i_length);
	if (pcOther.i_length >= i_length) {
		for (int i = 0; i < i_length; i++) {
			for (int j = 1; j <= pcOther.i_length; j++) {
				cRetValue.pi_number[cRetValue.i_length - i - j] = cRetValue.pi_number[cRetValue.i_length - i - j] + pi_number[i_length - i - 1] * pcOther.pi_number[pcOther.i_length - j];
				if (cRetValue.pi_number[cRetValue.i_length - i - j] >= NUM_SYSTEM) {
					int iMove = cRetValue.pi_number[cRetValue.i_length - i - j] / 10;
					cRetValue.pi_number[cRetValue.i_length - i - j] = cRetValue.pi_number[cRetValue.i_length - i - j] % 10;
					cRetValue.pi_number[cRetValue.i_length - i - j - 1] += iMove;
				}
			}
		}
	}
	else {
		for (int i = 0; i < pcOther.i_length; i++) {
			for (int j = 1; j <= i_length; j++) {
				cRetValue.pi_number[cRetValue.i_length - i - j] = cRetValue.pi_number[cRetValue.i_length - i - j] + pi_number[i_length - j] * pcOther.pi_number[pcOther.i_length - i - 1];
				if (cRetValue.pi_number[cRetValue.i_length - i - j] >= NUM_SYSTEM) {
					int iMove = cRetValue.pi_number[cRetValue.i_length - i - j] / 10;
					cRetValue.pi_number[cRetValue.i_length - i - j] = cRetValue.pi_number[cRetValue.i_length - i - j] % 10;
					cRetValue.pi_number[cRetValue.i_length - i - j - 1] += iMove;
				}
			}
		}
	}

	return cRetValue;
}

CNumber CNumber::operator/(const int iValue)
{
	CNumber cRetValue;
	cRetValue = 0;
	int iResultIndex = intLength(iValue);
	if (*this > iValue) {
		CNumber cTmp;
		cTmp.reallocate(iResultIndex);
		int iThisStartIndex = findStartIndex();
		cRetValue.reallocate(i_length - iThisStartIndex);
		for (int i = 1; i <= iResultIndex; i++)
			cTmp.pi_number[cTmp.i_length - i] = pi_number[iThisStartIndex + iResultIndex - i];
		while (iResultIndex <= cRetValue.i_length) { //dlugosc dzielnej - dlugosc dzielnika + 1 razy
			int iTimes = 0;
			while (!(cTmp < iValue)) { // max 9 razy
				cTmp = cTmp - iValue;
				iTimes++;
			}
			cRetValue.pi_number[iResultIndex - 1] = iTimes;
			iResultIndex++;
			cTmp = cTmp * 10;
			cTmp.pi_number[cTmp.i_length - 1] = pi_number[iThisStartIndex + iResultIndex - 1];
		}
	}
	return cRetValue;
}

CNumber CNumber::operator/(const CNumber& pcOther)
{
	CNumber cRetValue;
	cRetValue = 0;
	int iResultIndex = pcOther.i_length;
	if (*this > pcOther) {
		CNumber cTmp;
		cTmp.reallocate(iResultIndex);
		int iThisStartIndex = findStartIndex();
		cRetValue.reallocate(i_length - iThisStartIndex);
		for (int i = 1; i <= iResultIndex; i++)
			cTmp.pi_number[cTmp.i_length - i] = pi_number[iThisStartIndex + iResultIndex - i];
		while (iResultIndex <= cRetValue.i_length) { //dlugosc dzielnej - dlugosc dzielnika + 1 razy
			int iTimes = 0;
			while (!(cTmp < pcOther)) { // max 9 razy
				cTmp = cTmp - pcOther;
				iTimes++;
			}
			cRetValue.pi_number[iResultIndex - 1] = iTimes;
			iResultIndex++;
			cTmp = cTmp * 10;
			cTmp.pi_number[cTmp.i_length - 1] = pi_number[iThisStartIndex + iResultIndex - 1];
		}
	}
	return cRetValue;
}

bool CNumber::operator>(const int iValue)
{
	CNumber num;
	num = iValue;
	bool answer = (*this > num);
	return answer;
}

bool CNumber::operator>(const CNumber& pcOther)
{
	int iThisStartIndex = findStartIndex();
	int iOtherStartIndex = 0;
	while (pcOther.pi_number[iOtherStartIndex] == 0) {
		iOtherStartIndex++;
	}
	if ((i_length - iThisStartIndex) > (pcOther.i_length - iOtherStartIndex))
		return true;
	else if ((i_length - iThisStartIndex) < (pcOther.i_length - iOtherStartIndex))
		return false;
	else {
		int iTmp = 0;
		while (pi_number[iThisStartIndex + iTmp] == pcOther.pi_number[iOtherStartIndex + iTmp] && (iThisStartIndex + iTmp) < i_length)
			iTmp++;
		if (pi_number[iThisStartIndex + iTmp] > pcOther.pi_number[iOtherStartIndex + iTmp])
			return true;
		else
			return false;
	}
}

bool CNumber::operator<(const int iValue)
{
	CNumber num;
	num = iValue;
	bool answer = (*this < num);
	return answer;
}

bool CNumber::operator<(const CNumber& pcOther)
{
	int iThisStartIndex = findStartIndex();
	int iOtherStartIndex = 0;
	while (pcOther.pi_number[iOtherStartIndex] == 0) {
		iOtherStartIndex++;
	}
	if ((i_length - iThisStartIndex) < (pcOther.i_length - iOtherStartIndex))
		return true;
	else if ((i_length - iThisStartIndex) > (pcOther.i_length - iOtherStartIndex))
		return false;
	else {
		int iTmp = 0;
		while (pi_number[iThisStartIndex + iTmp] == pcOther.pi_number[iOtherStartIndex + iTmp] && (iThisStartIndex + iTmp) < i_length)
			iTmp++;
		if (pi_number[iThisStartIndex + iTmp] < pcOther.pi_number[iOtherStartIndex + iTmp])
			return true;
		else
			return false;
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

int CNumber::findStartIndex()
{
	int iStartIndex = 0;
	while (pi_number[iStartIndex] == 0) {
		iStartIndex++;
	}
	return iStartIndex;
}


int main() {

	CNumber num2, num3;
	num2 = 1;
	num3 = 234502;
	num2 = num3 / num2;
	cout << "num2: " << num2.sToStr() << endl;

	return 0;
}
