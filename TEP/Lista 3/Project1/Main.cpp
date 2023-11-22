#include <iostream>
#include <string>
#include "ConsoleGUI.h"

using namespace std;

int main() {
	ConsoleGUI* pcConsole = new ConsoleGUI();
	pcConsole->vAsker();
	delete pcConsole;
}