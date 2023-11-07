#include "CNumber.cpp"
#include "CNumber.h"

using namespace std;

int main() {
	CNumber num2, num3, * rest;
	cout << "dodawanie: " << endl;
	num2 = 2312;
	num3 = -32;
	num2 = num2 + num3;
	cout << "wynik: " << num2.sToStr() << endl;

	cout << "odejmowanie: " << endl;
	num2 = 2312;
	num3 = -32;
	num2 = num2 - num3;
	cout << "wynik: " << num2.sToStr() << endl;

	cout << "mnozenie: " << endl;
	num2 = 2312;
	num3 = -32;
	num2 = num2 * num3;
	cout << "wynik: " << num2.sToStr() << endl;

	cout << "dzielenie: " << endl;
	num2 = 2312;
	num3 = 32;
	num2 = num2 / num3;
	cout << "wynik: " << num2.sToStr() << endl;

	cout << "dzielenie z reszta: " << endl;
	num2 = 2312;
	num3 = 32;
	num2 = num2.cDiv(num3, &rest);
	cout << "wynik: " << num2.sToStr() << "   reszta: " << rest->sToStr() << endl;

	return 0;
}
