#include "math_exp.h"
#include <gtest.h>

TEST(calc, correct_formula)
{
	string s = "(1+2)*3";
	ASSERT_NO_THROW(calc(s));
}

TEST(calc, correct_formula_with_spaces)
{
	string s = "( 1 + 2 )   * 3";
	ASSERT_NO_THROW(calc(s));
}


TEST(calc, too_many_brackets_from_left)
{
	string s = "((((1";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, too_many_brackets_from_right)
{
	string s = "1))))";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, unknown_symbol)
{
	string s = "a+1";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, unfilled_brackets)
{
	string s = "1+()";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, number_only)
{
	string s = "1024";
	EXPECT_EQ(1024, calc(s));
}

TEST(calc, negative_only)
{
	string s = "-1024";
	EXPECT_EQ(-1024, calc(s));
}

TEST(calc, can_calc_sum)
{
	string s = "50+25";
	EXPECT_EQ(75, calc(s));
}

TEST(calc, can_calc_difference)
{
	string s = "50-25";
	EXPECT_EQ(25, calc(s));
}

TEST(calc, can_calc_multiplying)
{
	string s = "10*5";
	EXPECT_EQ(50, calc(s));
}

TEST(calc, can_calc_quotient)
{
	string s = "10/5";
	EXPECT_EQ(2, calc(s));
}

TEST(calc, can_calc_formula_without_brackets)
{
	string s = "10+8-6*4/2";
	EXPECT_EQ(6, calc(s));
}

TEST(calc, can_calc_formula_with_brackets)
{
	string s = "(2-1)*(1-2)/(2-1)";
	EXPECT_EQ(-1, calc(s));
}


TEST(calc, can_calc_formula_with_unary_minus)
{
	string s = "-(1+2)-(-3)";
	EXPECT_EQ(0, calc(s));
}

TEST(calc, can_calc_formula_with_spaces)
{
	string s = "( 1 +2 )*  3";
	EXPECT_EQ(9, calc(s));
}