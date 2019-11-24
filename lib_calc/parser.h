#pragma once
#include "types.h"

using namespace std;

class Parsing
{
	string infix;
	string postfix;
	string operands = "()+-*/";
	int priority[6] = { -1,-1,1,1,2,2 };
	bool isCorrect(string st);
public:
	Parsing(string inf = "a + b");
	string getInfix() { return infix; }
	string getPostfix() { return postfix; }
	string toPostfix();
	double Calculate();
};