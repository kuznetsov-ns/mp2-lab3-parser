#include "parser.h"
#include <iostream>
#include <vector>

using namespace std;

Parsing::Parsing(string inf)
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
		if (operands.find(infix[i + 1]) != string::npos)
			if (i != length)
				postfix += ' ';
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

double Parsing::Calculate()
{
	if (infix.length() == 0) toPostfix();
	int lenght = postfix.length();
	Stack<double> result(MAX_SIZE);
	string Values;
	double* values = new double[lenght];
	for (int i = 0; i < lenght; i++)
	{
		if (operands.find(postfix[i]) == string::npos)
		{
			double tmp;
			if ((postfix[i] < 48) || (postfix[i] > 57))
			{
				if (postfix[i] != ' ')
				{
					if (Values.find(postfix[i]) == string::npos)
					{
						Values += postfix[i];
						cout << "Enter the value of " << postfix[i] << ": ";
						cin >> tmp;
						values[Values.length() - 1] = tmp;
					}
					else
						tmp = values[Values.find(postfix[i])];
				}
				else
					continue;
			}
			else
			{
				string number;
				while (postfix[i] != ' ')
				{	
					number += postfix[i];
					if (operands.find(postfix[i + 1]) != string::npos)
						break;
					i++;
				}
				tmp = stoi(number);
			}
			result.push(tmp);
		}
		else
		{
			double fValue, sValue, tValue;
			sValue = result.pop();
			fValue = result.pop();
			switch (postfix[i])
			{
			case '+':
				tValue = fValue + sValue;
				break;
			case '-':
				tValue = fValue - sValue;
				break;
			case '*':
				tValue = fValue * sValue;
				break;
			case '/':
				tValue = fValue / sValue;
				break;
			}
			result.push(tValue);
		}
	}
	delete[] values;
	return result.pop();
}