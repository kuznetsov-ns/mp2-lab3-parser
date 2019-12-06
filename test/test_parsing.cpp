#include "parser.h"

#include <gtest.h>

TEST(Postfix, can_parse_string)
{
	string tmp = "a+b*c";
	Parsing parse(tmp);
	parse.toPostfix();
	ASSERT_NO_THROW(parse.toPostfix());
}

TEST(Postfix, throw_when_parse_empty_string)
{
	string tmp;
	ASSERT_ANY_THROW(Parsing parse(tmp););
}

TEST(Postfix, throw_when_parse_string_with_too_many_brackets)
{
	string tmp = "((a+b)";
	ASSERT_ANY_THROW(Parsing parse(tmp));
	tmp = "(a+b))";
	ASSERT_ANY_THROW(Parsing parse(tmp));
}

TEST(Postfix, throw_when_parse_string_with_few_brackets)
{
	string tmp = "(a+b";
	ASSERT_ANY_THROW(Parsing parse(tmp));
	tmp = "a+b)";
	ASSERT_ANY_THROW(Parsing parse(tmp));
}

TEST(Postfix, throw_when_too_many_operands)
{
	string tmp = "1++2";
	ASSERT_ANY_THROW(Parsing parse(tmp));
}

TEST(Postfix, throw_when_string_contain_error_symbols)
{
	string tmp = "@1+2";
	ASSERT_ANY_THROW(Parsing parse(tmp));
}

TEST(Postfix, can_calculate)
{
	string tmp = "1+2*3";
	Parsing parse(tmp);
	parse.toPostfix();
	EXPECT_EQ("1 2 3*+", parse.getPostfix());
	double result = parse.Calculate();
	EXPECT_EQ(7, result);
}