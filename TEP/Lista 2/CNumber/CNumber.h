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
	void operator+ (const int iValue);
	void operator+ (const CNumber& pcOther);
	void operator- (const int iValue);
	void operator- (const CNumber& pcOther);
	void operator* (const int iValue);
	void operator* (const CNumber& pcOther);
	void operator/ (const int iValue);
	void operator/ (const CNumber& pcOther);
	string sToStr();
};

static const int NUM_SYSTEM = 10;
static int intLength(int iVal);
static const int DEFAULT_LENGTH = 5;
static const int DEFAULT_NUM = 1;

