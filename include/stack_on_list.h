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
	template <typename ValType>
	struct Node
	{
		ValType data;
		Node<ValType> *next;
	};

	Node<ValType> *top;
	size_t size;

public:
	Stack() : top(nullptr), size(0) {}

	Stack(const Stack<ValType>&);

	~Stack();

	void Push(ValType);

	ValType Pop();

	ValType Top();

	size_t GetSize() { return size; }
	bool Empty() { return (size == 0); }
	bool Full() { return (size == MAX_STACK_SIZE); }
};

#endif
