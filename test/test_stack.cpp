#include "types.h"

#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> st(10));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> st(-1));
}

TEST(Stack, cant_push_if_stack_is_full)
{
	Stack<int> st(3);
	for (int i = 0; i < 3; i++)
		st.push(i);
	ASSERT_ANY_THROW(st.push(4));
}

TEST(Stack, cant_pop_if_stack_is_empty)
{
	Stack<int> st(3);
	ASSERT_ANY_THROW(st.pop());
}

TEST(Stack, can_push_and_pop_element)
{
	Stack<int> st(1);
	st.push(1);
	EXPECT_EQ(1, st.pop());
}

TEST(Stack, full_is_correct)
{
	Stack<int> st(1);
	EXPECT_EQ(false, st.isFull());
	st.push(1);
	EXPECT_EQ(true, st.isFull());
}

TEST(Stack, empty_is_correct)
{
	Stack<int> st(1);
	st.push(1);
	EXPECT_EQ(false, st.isEmpty());
	st.pop();
	EXPECT_EQ(true, st.isEmpty());
}