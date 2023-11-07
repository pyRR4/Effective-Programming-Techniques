#include "CNumber.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void CNumber::v_addition(CNumber& pcSum, const CNumber& pcIngredientLonger, const CNumber& pcIngredientShorter)
{
	pcSum.reallocate(pcIngredientLonger.i_length + 1);
	for (int i = 1; i <= pcIngredientLonger.i_length; i++) {
		if (i <= pcIngredientShorter.i_length)
			pcSum.pi_number[pcSum.i_length - i] = pcSum.pi_number[pcSum.i_length - i] + pcIngredientLonger.pi_number[pcIngredientLonger.i_length - i] + pcIngredientShorter.pi_number[pcIngredientShorter.i_length - i];
		else 
			pcSum.pi_number[pcSum.i_length - i] = pcSum.pi_number[pcSum.i_length - i] + pcIngredientLonger.pi_number[pcIngredientLonger.i_length - i];
		if (pcSum.pi_number[pcSum.i_length - i] >= NUM_SYSTEM) {
			pcSum.pi_number[pcSum.i_length - i] = pcSum.pi_number[pcSum.i_length - i] % NUM_SYSTEM;
			pcSum.pi_number[pcSum.i_length - 1 - i]++;
		}
	}
}

void CNumber::v_substraction(CNumber& pcDifference, const CNumber& pcMinuend, const CNumber& pcSubtrahend)
{
	pcDifference.reallocate(pcMinuend.i_length - findStartIndex(pcMinuend));
	for (int i = 1; i <= pcDifference.i_length; i++) {
		if (i < pcSubtrahend.i_length)
			pcDifference.pi_number[pcDifference.i_length - i] = pcDifference.pi_number[pcDifference.i_length - i] + pcMinuend.pi_number[pcMinuend.i_length - i] - pcSubtrahend.pi_number[pcSubtrahend.i_length - i];
		else
			pcDifference.pi_number[pcDifference.i_length - i] = pcDifference.pi_number[pcDifference.i_length - i] + pcMinuend.pi_number[pcMinuend.i_length - i];
		if (pcDifference.pi_number[pcDifference.i_length - i] < 0) {
			pcDifference.pi_number[pcDifference.i_length - i] += NUM_SYSTEM;
			pcDifference.pi_number[pcDifference.i_length - i - 1]--;
		}
	}
}

void CNumber::v_multiplication(CNumber& pcProduct, const CNumber& pcElement1, const CNumber& pcElement2)
{
	int iLengthEl1 = pcElement1.i_length - findStartIndex(pcElement1);
	int iLengthEl2 = pcElement2.i_length - findStartIndex(pcElement2);
	pcProduct.reallocate(iLengthEl1 + iLengthEl2);
	for (int i = 0; i < iLengthEl1; i++) {
		for (int j = 1; j <= iLengthEl2; j++) {
			pcProduct.pi_number[pcProduct.i_length - i - j] = pcProduct.pi_number[pcProduct.i_length - i - j] + pcElement1.pi_number[pcElement1.i_length - i - 1] * pcElement2.pi_number[pcElement2.i_length - j];
			if (pcProduct.pi_number[pcProduct.i_length - i - j] >= NUM_SYSTEM) {
				int iCarry = pcProduct.pi_number[pcProduct.i_length - i - j] / NUM_SYSTEM;
				pcProduct.pi_number[pcProduct.i_length - i - j] = pcProduct.pi_number[pcProduct.i_length - i - j] % NUM_SYSTEM;
				pcProduct.pi_number[pcProduct.i_length - i - j - 1] += iCarry;
			}
		}
	}
}

CNumber CNumber::v_division(CNumber& pcQuotient, const CNumber& pcDividend, const CNumber& pcDivider)
{
	int iResultIndex = pcDivider.i_length - findStartIndex(pcDivider);
	CNumber cTmp;
	CNumber cTen;
	cTen = NUM_SYSTEM;
	cTmp.reallocate(iResultIndex);
	int iThisStartIndex = findStartIndex(pcDividend);
	pcQuotient.reallocate(pcDividend.i_length - iThisStartIndex);
	for (int i = 1; i <= iResultIndex; i++)
		cTmp.pi_number[cTmp.i_length - i] = pcDividend.pi_number[iThisStartIndex + iResultIndex - i];
	while (iResultIndex <= pcQuotient.i_length) { //dlugosc dzielnej - dlugosc dzielnika + 1 razy
		int iTimes = 0;
		while (!(cTmp < pcDivider)) { // max 9 razy
			cTmp = (cTmp - pcDivider);
			iTimes++;
		}
		pcQuotient.pi_number[iResultIndex - 1] = iTimes;
		iResultIndex++;
		if (iResultIndex <= pcQuotient.i_length)
		{
			cTmp = cTmp * cTen;
			cTmp.pi_number[cTmp.i_length - 1] = pcDividend.pi_number[iThisStartIndex + iResultIndex - 1];
		}
	}
	return cTmp;
}

CNumber::CNumber()
{
	i_length = DEFAULT_LENGTH;
	pi_number = new int[i_length];
	b_negative = DEFAULT_NEGATIVE;
}

CNumber::CNumber(bool bNegative, int iNumber, int iLength) 
{
	b_negative = bNegative;
	i_length = iLength;
	pi_number = new int[i_length];
	operator=(iNumber);
}

CNumber::~CNumber() {
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
	int iVal;
	if (iValue < 0) {
		b_negative = true;
		iVal = -iValue;
	}
	else {
		b_negative = false;
		iVal = iValue;
	}
	int valLength = intLength(iVal);
	if (i_length < valLength) {
		i_length = valLength;
		
		delete pi_number;
		pi_number = new int[i_length];
	}
	for (int i = i_length - 1; i >= 0; i--) {
		pi_number[i] = iVal % NUM_SYSTEM;
		iVal = iVal / NUM_SYSTEM;
	}
}

void CNumber::operator=(const CNumber& pcOther)
{
	delete pi_number;
	b_negative = pcOther.b_negative;
	i_length = pcOther.i_length;
	pi_number = new int[i_length];
	for (int i = 0; i < i_length; i++)
		pi_number[i] = pcOther.pi_number[i];
}

CNumber CNumber::operator+(const CNumber& pcOther)
{
	CNumber cRetValue;
	cRetValue = 0;
	if (pcOther.b_negative) {
		v_substraction(cRetValue, *this, pcOther);
	}
	else if (b_negative) {
		v_substraction(cRetValue, pcOther, *this);
	}
	else {
		if (i_length >= pcOther.i_length)
			v_addition(cRetValue, *this, pcOther);
		else
			v_addition(cRetValue, pcOther, *this);
	}
	return cRetValue;
}

CNumber CNumber::operator-(const CNumber& pcOther)
{
	CNumber cRetValue;
	cRetValue = 0;
	if (pcOther.b_negative) {
		if (i_length >= pcOther.i_length)
			v_addition(cRetValue, *this, pcOther);
		else
			v_addition(cRetValue, pcOther, *this);
	}
	else {
		if (*this < pcOther) {
			v_substraction(cRetValue, pcOther, *this);
			cRetValue.b_negative = true;
		}
		else
			v_substraction(cRetValue, *this, pcOther);
	}
	return cRetValue;
}

CNumber CNumber::operator*(const CNumber& pcOther)
{
	CNumber cRetValue;
	cRetValue = 0;
	if (pcOther.b_negative != b_negative)
		cRetValue.b_negative = true;
	v_multiplication(cRetValue, *this, pcOther);

	return cRetValue;
}

CNumber CNumber::operator/(const CNumber& pcOther)
{
	CNumber cRetValue;
	cRetValue = 0;
	if (!(cRetValue == pcOther)) { //dzielenie przez 0 zwraca wynik 0
		if (pcOther.b_negative != b_negative)
			cRetValue.b_negative = true;
		CNumber cAbsoluteOther;
		cAbsoluteOther = pcOther;
		cAbsoluteOther.b_negative = false;
		if (*this > pcOther) {
			v_division(cRetValue, *this, cAbsoluteOther);
		}
	}
	return cRetValue;
}

CNumber CNumber::cDiv(CNumber& pcOther, CNumber** pcRest)
{
	CNumber cRetValue;
	cRetValue = 0;
	*pcRest = new CNumber();
	if (!(cRetValue == pcOther)) {
		if (pcOther.b_negative != b_negative)
			cRetValue.b_negative = true;
		CNumber cAbsoluteOther;
		cAbsoluteOther = pcOther;
		cAbsoluteOther.b_negative = false;
		**pcRest = v_division(cRetValue, *this, cAbsoluteOther);
		if (**pcRest == 0 || b_negative || pcOther.b_negative) {
			delete* pcRest;
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
	if (pcOther.b_negative != this->b_negative) {
		if (pcOther.b_negative)
			return true;
		else
			return false;
	}
	if (b_negative)
		return (*this < pcOther);
	int iThisStartIndex = findStartIndex(*this);
	int iOtherStartIndex = findStartIndex(pcOther);
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
	if (pcOther.b_negative != this->b_negative) {
		if (pcOther.b_negative)
			return false;
		else
			return true;
	}
	if (b_negative)
		return (*this > pcOther);
	int iThisStartIndex = findStartIndex(*this);
	int iOtherStartIndex = findStartIndex(pcOther);
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

bool CNumber::operator==(const CNumber& pcOther)
{
	int iThisStartIndex = findStartIndex(*this);
	int iOtherStartIndex = findStartIndex(*this);
	if ((i_length - iThisStartIndex) != (pcOther.i_length - iOtherStartIndex))
		return false;
	for (int i = 0; i < i_length; i++) {
		if (pi_number[i] != pcOther.pi_number[i]) {
			return false;
		}
	}
	return true;
}
bool CNumber::operator==(const int iValue)
{
	int iThisStartIndex = findStartIndex(*this);
	if ((i_length - iThisStartIndex) != intLength(iValue))
		return false;
	int iVal = iValue;
	for (int i = 0; i < i_length; i++) {
		if (pi_number[i] != (iVal % NUM_SYSTEM)) {
			return false;
		}
		iVal /= NUM_SYSTEM;
	}
	return true;
}

string CNumber::sToStr()
{
	ostringstream oss;
	if (b_negative)
		oss << "-";
	for (int i = 0; i < i_length; i++)
		oss << pi_number[i];
	return oss.str();
}

int intLength(int iVal)
{
	int iResult = 0;
	while (iVal != 0) {
		iResult++;
		iVal = iVal / NUM_SYSTEM;
	}
	return iResult;
}

int CNumber::findStartIndex(const CNumber& cNum)
{
	int iStartIndex = 0;
	while (cNum.pi_number[iStartIndex] == 0) {
		iStartIndex++;
	}
	return iStartIndex;
}


