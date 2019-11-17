#pragma once
#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>

#define MAX_STACK_SIZE 10000

typedef std::size_t size_t;

template <typename ValType>
class Stack
{
private:
	ValType* mas;
	size_t size;
	size_t top_ind;
	void Resize();

public:
	Stack(size_t s = 10000);

	Stack(const Stack<ValType>&);

	~Stack() { delete[] mas; }

	bool Full() { return (top_ind + 1 == size); }
	bool Empty() { return (top_ind == -1); }
	size_t GetSize() { return top_ind + 1; }

	void Push(ValType elem);

	ValType Pop();

	ValType Top();
};

#endif // !_STACK_H_
