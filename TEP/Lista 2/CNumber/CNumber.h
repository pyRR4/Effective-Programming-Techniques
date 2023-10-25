#pragma once

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
	string sToStr();
	void operator= (const int iValue);
	void operator= (const CNumber &pcOther);
	void reallocate(int iLength);
};

static int intLength(int iVal);
static const int DEFAULT_LENGTH = 5;
static const int DEFAULT_NUM = 1;

