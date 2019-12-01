#include "parser.h"
#include <vector>

Parsing::Parsing(string inf = "a + b")
{
	if (!isCorrect(inf)) throw "Incorrect";
	for (int i = 0; i < inf.length(); i++)
		infix += inf[i];
	if (infix.length() < 1) throw "Incorrect";
}

bool Parsing::isCorrect(string str)
{
	string error_symbols = "!@#$%^&№<>{}[]_=,.";
	int count = 0, variable_count = 0, operations_count = 0, length = str.length();
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
			throw ("too many operators");
	}
	if (count != 0)
		throw ("too many / few brackets");
	return true;
}

string Parsing::toPostfix()
{
	Stack<char> symbol_stack(MAX_SIZE);
	string tmp_symbols = "+-*/()";
	int length = infix.length();
	for (int i = 0; i < length; i++)
	{
		if (tmp_symbols.find(infix[i]) == string::npos)
			postfix += infix[i];
		if (infix[i] == '(') symbol_stack.push(infix[i]);
		if (infix[i] == ')')
		{
			char tmp = symbol_stack.pop();
			while (tmp != '(')
			{
				postfix += tmp;
				tmp = symbol_stack.pop();
			}
		}
		if (operands.find(infix[i]) != string::npos)
		{
			if (symbol_stack.isEmpty())
				symbol_stack.push(infix[i]);
			else
			{
				int _index = operands.find(infix[i]);
				while (!symbol_stack.isEmpty())
				{
					char tmp = symbol_stack.pop();
					if (tmp == '(')
					{
						symbol_stack.push(tmp);
						break;
					}
					int __index = operands.find(tmp);
					if (priority[__index] >= priority[_index])
						postfix += tmp;
					else
					{
						symbol_stack.push(tmp);
						break;
					}
				}
				symbol_stack.push(infix[i]);
			}
		}
	}
	while (!symbol_stack.isEmpty())
		postfix += symbol_stack.pop();
	return postfix;
}