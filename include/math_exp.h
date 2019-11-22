#pragma once
#ifndef _MATH_EXP_H_
#define _MATH_EXP_H_

#include <string>
#include <vector>
#include "stack_on_array.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

struct Lexeme
{
	virtual ~Lexeme() {}
	friend std::ostream& operator<<(std::ostream& ostr, const Lexeme& lex);
};

struct Operation : public Lexeme
{
	char symbol;
	int priority;

	Operation() : symbol(' '), priority(-1) {}
	Operation(char);
	Operation(const Operation&);
	~Operation() {}
	Operation& operator= (char);
	Operation& operator= (const Operation&);

	friend std::ostream& operator<<(std::ostream& ostr, const Operation& op);

private:
	void setPriority();
};

struct Literal_const : public Lexeme
{
	double value;

	Literal_const() : value(0) {}
	Literal_const(double data) : value(data) {}
	Literal_const(const Literal_const& cs) : value(cs.value) {}
	~Literal_const() {}
	Literal_const& operator= (double);
	Literal_const& operator= (const Literal_const&);

	friend std::ostream& operator<<(std::ostream& ostr, const Literal_const& lit);
};

double calc(string formula);
#endif
