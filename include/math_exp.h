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
};

struct Operation : public Lexeme
{
	char symbol;
	size_t priority;

	Operation(char);
	Operation(const Operation&);
	~Operation() {}
	Operation& operator= (char);
	Operation& operator= (const Operation&);

private:
	void setPriority();
};

struct Literal_const : public Lexeme
{
	int value;

	Literal_const(int data) : value(data) {}
	Literal_const(const Literal_const& cs) : value(cs.value) {}
	~Literal_const() {}
	Literal_const& operator= (int);
	Literal_const& operator= (const Literal_const&);
};

int calc(string formula);
#endif
