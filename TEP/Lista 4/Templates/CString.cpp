#include "CString.h"
#include <vector>

CString::CString()
{
	s_value = "";
}

CString::CString(string sValue)
{
	s_value = sValue;
}

void CString::operator=(const CString& pcOther)
{
	s_value = pcOther.s_value;
}

void CString::operator=(const string& pcOther)
{
	s_value = pcOther;
}

bool CString::operator==(const string& pcOther)
{
	if (s_value.compare(pcOther) == 0)
		return true;
	else
		return false;
}

bool CString::operator==(const CString& pcOther)
{
	if (s_value.compare(pcOther.s_value) == 0)
		return true;
	else
		return false;
}

CString CString::operator+(const CString& pcOther)
{
	return s_value + pcOther.s_value;
}

CString CString::operator-(const CString& pcOther)
{
	int iThisLength = s_value.size();
	int iOtherLength = pcOther.s_value.size();
	string retValue = s_value;
	if (iOtherLength > iThisLength)
		return retValue;
	bool bLoopEnd = false;
	int iDeletionIndex;
	
	int i = iThisLength - iOtherLength;
	while (!bLoopEnd && i >= 0) {
		int iTmp = i;
		int iOtherTmp = 0;
		while (s_value[iTmp] == pcOther.s_value[iOtherTmp] && !bLoopEnd) {
			if ((iOtherTmp + 1) == iOtherLength) {
				bLoopEnd = true;
				iDeletionIndex = i;
			}
			else {
				iTmp++;
				iOtherTmp++;
			}
		}
		i--;
	}
	if (bLoopEnd) {
		retValue = "";
		for (int j = 0; j < iThisLength; j++) {
			if (!(j >= iDeletionIndex && j < (iDeletionIndex + iOtherLength)))
				retValue += s_value[j];
		}
	}
	return retValue;
}

CString CString::operator/(const CString& pcOther)
{
	int iThisLength = s_value.size();
	int iOtherLength = pcOther.s_value.size();
	string retValue = s_value;
	if (iOtherLength > iThisLength)
		return retValue;
	vector<int> vecDeletionIndexes;
	bool bLoopEnd;
	for (int i = 0; i < iThisLength; i++) {
		int iTmp = i;
		int iOtherTmp = 0;
		bLoopEnd = false;
		while (s_value[iTmp] == pcOther.s_value[iOtherTmp] && !bLoopEnd) {
			if ((iOtherTmp + 1) == iOtherLength) {
				bLoopEnd = true;
				vecDeletionIndexes.push_back(i);
				i += (iOtherLength - 1);
			}
			else {
				iTmp++;
				iOtherTmp++;
			}
		}
	}
	bool bToDelete = false;
	if (!vecDeletionIndexes.empty()) {
		retValue = "";
		int iCurrIndex;
		for (int i = 0; i < iThisLength; i++) {
			if (bToDelete && i == (iCurrIndex + iOtherLength))
				bToDelete = false;
			if (!bToDelete) {
				retValue += s_value[i];
			}
			if (!vecDeletionIndexes.empty() && i == vecDeletionIndexes.front()) {
				iCurrIndex = vecDeletionIndexes.front();
				bToDelete = true;
				vecDeletionIndexes.erase(vecDeletionIndexes.begin());
			}
		}
	}
	return retValue;
}

CString CString::operator*(const CString& pcOther)
{
	int iOtherLength = pcOther.s_value.size();
	int iThisLength = s_value.size();
	if (iOtherLength == 0 || iThisLength == 0)
		return s_value;
	string retValue = "";
	for (int i = 0; i < iThisLength; i++) {
		retValue += s_value[i];
		if (s_value[i] == pcOther.s_value[0]) {
			retValue += pcOther.s_value.substr(1);
		}
	}
	return retValue;
}

string CString::sToString()
{
	return s_value;
}
