#include <iostream>
#include <string>
#include <vector>
#include "lib_calc/types.h"
#include "lib_calc/parser.h"

using namespace std;

int main() {
	string input;
	double result;
	cout << "Enter expression: ";
	cin >> input;
	cout << endl << input << endl;
	try {
		Parsing parser(input);
		cout << "Infix: " << parser.getInfix() << endl;
		parser.toPostfix();
		cout << "Postfix: " << parser.getPostfix() << endl;
		result = parser.Calculate();
		cout << "Result: " << result << endl;
	} catch (const char* s) {
		cout << s;
	}
	return 0;
}
