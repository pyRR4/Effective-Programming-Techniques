#include <iostream>
#include <string>
#include "ConsoleGUI.h"

using namespace std;

int main() {
	ConsoleGUI<double>* pcConsole = new ConsoleGUI<double>();
	pcConsole->vAsker();
	delete pcConsole;
}