#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>

#define MAX_STACK_SIZE 10000

typedef unsigned int size_t;

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

	Stack(const Stack<ValType> &st)
	{
		size = st.size;
		top = nullptr;
		Node<ValType> *input_node = st.top;
		Node<ValType> *cur_node, *prev_node = nullptr;
		while (input_node != nullptr)
		{
			cur_node = new Node<ValType>;
			cur_node->data = input_node->data;
			cur_node->next = nullptr;

			if (top == nullptr)
			{
				top = cur_node;
				prev_node = cur_node;
			}
			else
			{
				prev_node->next = cur_node;
				prev_node = prev_node->next;
			}

			input_node = input_node->next;
		}
	}

	~Stack()
	{
		while (top != nullptr)
			Pop();
	}

	void Push(ValType elem)
	{
		if (size == MAX_STACK_SIZE)
			throw "Error: stack overflow";
		Node<ValType> *tmp = new Node<ValType>;

		tmp->data = elem;
		tmp->next = top;
		top = tmp;
		size++;
	}

	ValType Pop()
	{
		if (size == 0)
			throw "Error: stack underflow";

		Node<ValType> *tmp;
		ValType tmp_data = top->data;

		tmp = top;
		top = top->next;
		delete tmp;
		size--;

		return tmp_data;
	}

	ValType Top()
	{
		if (size == 0)
			throw "Error: stack underflow";
		return top->data;
	}

	size_t GetSize() { return size; }
	bool Empty() { return (size == 0); }
	bool Full() { return (size == MAX_STACK_SIZE); }
};

#endif
