#include "stack_on_array.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
  ASSERT_NO_THROW(Stack<int> s(1));
}


TEST(Stack, can_create_copied_stack)
{
	Stack<int> s(1);
	s.Push(1);
	ASSERT_NO_THROW(Stack<int> s_c(s));
}


TEST(Stack, can_pop_element)
{
	Stack<int> s(5);
	s.Push(3);
	s.Push(1);
	s.Pop();
	EXPECT_EQ(3, s.Top());
}

TEST(Stack, can_push_elem)
{
	Stack<int> s(5);
	ASSERT_NO_THROW(s.Push(14));
}


TEST(Stack, can_get_size)
{
	Stack<int> s(5);
	s.Push(1);
	EXPECT_EQ(1, s.GetSize());
}

TEST(Stack, can_get_top_elem)
{
	Stack<int> s(5);
	s.Push(3);
	EXPECT_EQ(3, s.Top());
}


TEST(Stack, empty_stack_is_empty)
{
	Stack<int> s(10);
	EXPECT_EQ(true, s.Empty());
}

TEST(Stack, not_empty_stack_is_not_empty)
{
	Stack<int> s(1);
	s.Push(1);
	EXPECT_EQ(false, s.Empty());
}

TEST(Stack, full_stack_is_full)
{
	Stack<int> s(5);
	for (size_t i = 0; i < 5; i++)
		s.Push(1);
	EXPECT_EQ(true, s.Full());
}

TEST(Stack, not_full_stack_is_not_full)
{
	Stack<int> s(5);
	s.Push(1);
	EXPECT_EQ(false, s.Full());
}

TEST(Stack, throws_when_gets_top_elem_from_empty_stack)
{
	Stack<int> s(5);
	ASSERT_ANY_THROW(s.Top());
}

TEST(Stack, throws_when_underflow)
{
	Stack<int> s(10);
	ASSERT_ANY_THROW(s.Pop());
}

TEST(Stack, throws_when_overflow)
{
	Stack<int> s(MAX_STACK_SIZE);
	for (size_t i = 0; i < MAX_STACK_SIZE; i++)
		s.Push(1);
	ASSERT_ANY_THROW(s.Push(1));
}


