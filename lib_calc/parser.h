#pragma once
#include "types.h"
#include <vector>

using namespace std;

class Parsing
{
	string infix;
	string postfix;
	string operands = "+-*/";
	int priority[4] = { 1,1,2,2 };
	bool isCorrect(string str);
public:
	Parsing(string inf);
	string getInfix() { return infix; }
	string getPostfix() { return postfix; }
	string toPostfix();
	double Calculate();
};