#pragma once

#include "types.h"


class Parsing
{
	Stack<std::string> st;
public:
	Parsing(std::string _input);
	static void priority();
	static void stack();
};