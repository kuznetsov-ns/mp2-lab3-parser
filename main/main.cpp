#include <iostream>
#include <string>
#include "types.h"
#include "parser.h"

using namespace std;

int main()
{
	string input;
	cout << "Enter expression: ";
	cin >> input;
	cout << endl << input << endl;
	try
	{
		Parsing parser(input);
		cout << "Infix: " << parser.getInfix() << endl;
		parser.toPostfix();
		cout << "Postfix: " << parser.getPostfix() << endl;
	}
	catch (const char* s)
	{
		cout << s;
	}
	return 0;
}