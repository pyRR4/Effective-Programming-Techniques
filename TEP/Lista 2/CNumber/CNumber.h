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
	void operator= (const int iValue);
	void operator= (const CNumber &pcOther);
	string toStr();
};

static const int DEFAULT_LENGTH = 5;
static const int DEFAULT_NUM = 1;

