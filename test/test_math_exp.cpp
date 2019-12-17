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

TEST(calc, real_number_without_integer_part)
{
	string s = "1+.38";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, real_number_with_too_many_points)
{
	string s = "1+1.38.3";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, real_number_with_point_only)
{
	string s = "1+.";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, formula_without_numbers)
{
	string s = "-(--)";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, unary_minus_without_open_bracket)
{
	string s = "3+-5";
	ASSERT_ANY_THROW(calc(s));
}

TEST(calc, double_unary_minus)
{
	string s = "--5";
	ASSERT_ANY_THROW(calc(s));
}


TEST(calc, can_calc_number_only)
{
	string s = "1024";
	EXPECT_EQ(1024.0, calc(s));
}

TEST(calc, can_calc_negative_only)
{
	string s = "-1024";
	EXPECT_EQ(-1024.0, calc(s));
}

TEST(calc, can_calc_double_negative_only)
{
	string s = "-(-1024)";
	EXPECT_EQ(1024.0, calc(s));
}

TEST(calc, can_calc_negative_zero)
{
	string s = "-0";
	EXPECT_EQ(0.0, calc(s));
}

TEST(calc, can_calc_real_number_without_frac_part)
{
	string s = "1+1.";
	EXPECT_EQ(2.0, calc(s));
}

TEST(calc, can_calc_sum)
{
	string s = "50+25";
	EXPECT_EQ(75.0, calc(s));
}

TEST(calc, can_calc_difference)
{
	string s = "50-25";
	EXPECT_EQ(25.0, calc(s));
}

TEST(calc, can_calc_multiplying)
{
	string s = "10*5";
	EXPECT_EQ(50.0, calc(s));
}

TEST(calc, can_calc_quotient)
{
	string s = "7.5/5";
	EXPECT_EQ(1.5, calc(s));
}

TEST(calc, can_calc_formula_without_brackets)
{
	string s = "10+8-6*4/2";
	EXPECT_EQ(6.0, calc(s));
}

TEST(calc, can_calc_formula_with_brackets)
{
	string s = "(2-1)*(1-2)/(2-1)";
	EXPECT_EQ(-1.0, calc(s));
}


TEST(calc, can_calc_formula_with_unary_minus)
{
	string s = "-(1+2)-(-3)";
	EXPECT_EQ(0.0, calc(s));
}

TEST(calc, can_calc_formula_with_spaces)
{
	string s = "( 1 +2 )*  3";
	EXPECT_EQ(9.0, calc(s));
}

TEST(calc, can_calc_test_1)
{
	string s = "1+2*3";
	EXPECT_EQ(7.0, calc(s));
}

TEST(calc, can_calc_test_2)
{
	string s = "1*2+3";
	EXPECT_EQ(5.0, calc(s));
}