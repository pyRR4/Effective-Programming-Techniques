#pragma once
#include <string>

using namespace std;

class CNumber
{
private:
	int* pi_number;
	int i_length;
public:
	CNumber();
	CNumber(int iNumber, int iLength);
	~CNumber();
	void reallocate(int iNewLength);
	void operator= (const int iValue);
	void operator= (const CNumber &pcOther);
	CNumber operator+ (const int iValue);
	CNumber operator+ (const CNumber& pcOther);
	CNumber operator- (const int iValue);
	CNumber operator- (const CNumber& pcOther);
	CNumber operator* (const int iValue);
	CNumber operator* (const CNumber& pcOther);
	CNumber operator/ (const int iValue);
	CNumber operator/ (const CNumber& pcOther);
	bool operator> (const int iValue);
	bool operator> (const CNumber& pcOther);
	bool operator< (const int iValue);
	bool operator< (const CNumber& pcOther);
	int findStartIndex();
	string sToStr();
};

static const int NUM_SYSTEM = 10;
static int intLength(int iVal);
static const int DEFAULT_LENGTH = 5;
static const int DEFAULT_NUM = 0;

