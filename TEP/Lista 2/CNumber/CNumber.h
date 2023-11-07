#pragma once
#include <string>

using namespace std;

class CNumber
{
private:
	int* pi_number;
	int i_length;
	bool b_negative;
	void v_addition(CNumber& pcSum, const CNumber& pcIngredient1, const CNumber& pcIngredient2);
	void v_substraction(CNumber& pcDifference, const CNumber& pcMinuend, const CNumber& pcSubtrahend);
	void v_multiplication(CNumber& pcProduct, const CNumber& pcElement1, const CNumber& pcElement2);
	CNumber v_division(CNumber& pcQuotient, const CNumber& pcDividend, const CNumber& pcDivider);
public:
	CNumber();
	CNumber(bool bNegative, int iNumber, int iLength);
	~CNumber();
	void reallocate(int iNewLength);
	void operator= (const int iValue);
	void operator= (const CNumber &pcOther);
	CNumber operator+ (const CNumber& pcOther);
	CNumber operator- (const CNumber& pcOther);
	CNumber operator* (const CNumber& pcOther);
	CNumber operator/ (const CNumber& pcOther);
	CNumber cDiv(CNumber& pcOther, CNumber** pcRest);
	bool operator> (const int iValue);
	bool operator> (const CNumber& pcOther);
	bool operator< (const int iValue);
	bool operator< (const CNumber& pcOther);
	bool operator== (const CNumber& pcOther);
	bool operator== (const int iValue);
	int findStartIndex(const CNumber& cNum);
	string sToStr();
};

static const int NUM_SYSTEM = 10;
static int intLength(int iVal);
static const int DEFAULT_LENGTH = 5;
static const int DEFAULT_NUM = 0;
static const bool DEFAULT_NEGATIVE = false;

