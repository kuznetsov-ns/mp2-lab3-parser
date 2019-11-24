#include "parser.h"

Parsing::Parsing(string inf = "a + b")
{
	if (!isCorrect(inf)) throw "Incorrect";
	for (int i = 0; i < inf.length(); i++)
		if (inf[i] != ' ')
			infix += inf[i];
	if (infix.length() < 1) throw "Incorrect";
}

bool Parsing::isCorrect(string str)
{
	string error_symbols = "!@#$%^&№<>{}[]_=,.";
	int count = 0, variable_count = 0, operations_count = 0, length = str.length();
	if ((operands.find(str[0] != string::npos)) || (operands.find(str[length - 1]) != string::npos))
		return false;
	for (int i = 0; i < length; i++)
	{
		if (error_symbols.find(str[i]) != string::npos)
			return false;
		if (str[i] == '(') count++;
		if (str[i] == ')') count--;
		if ((str[i] - 'a' >= 0) && (str[i] - 'a' <= 25))
			variable_count++;
		else
			variable_count = 0;
		if (operands.find(str[i]) != string::npos)
			operations_count++;
		else
			operations_count = 0;
		if ((variable_count > 1) || (operations_count > 1))
			return false;
	}
	if (count != 0)
		return false;
	return true;
}
