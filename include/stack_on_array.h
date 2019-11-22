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

	friend std::ostream& operator<<(std::ostream& ostr, const Stack& st)
	{
		if (st.top_ind == -1)
			ostr << "Empty";
		else
			for (size_t i = 0; i <= st.top_ind; i++)
				ostr << st.mas[i] << ' ';

		return ostr;
	}
};

template <typename ValType>
void Stack<ValType>::Resize()
{
	if (size == MAX_STACK_SIZE)
		throw "Error: stack overflow";
	size_t new_size = size + size / 3 + 1;
	if (new_size > MAX_STACK_SIZE)
		new_size = MAX_STACK_SIZE;
	ValType* tmp = new ValType[new_size];
	for (size_t i = 0; i < size; i++)
		tmp[i] = mas[i];
	delete[] mas;
	mas = tmp;
	size = new_size;
}

template <typename ValType>
Stack<ValType>::Stack(size_t s)
{
	if (size < 0)
		throw "Error: illegal size";
	size = s;
	mas = new ValType[size];
	top_ind = -1;
}

template <typename ValType>
Stack<ValType>::Stack(const Stack<ValType>& st)
{
	size = st.size;
	mas = new ValType[size];
	for (size_t i = 0; i < size; i++)
		mas[i] = st.mas[i];
	top_ind = st.top_ind;
}

template <typename ValType>
void Stack<ValType>::Push(ValType elem)
{
	if (Full())
		Resize();
	top_ind++;
	mas[top_ind] = elem;
}

template <typename ValType>
ValType Stack<ValType>::Pop()
{
	if (Empty())
		throw "Error: stack underflow";
	top_ind--;
	return mas[top_ind + 1];
}

template <typename ValType>
ValType Stack<ValType>::Top()
{
	if (Empty())
		throw "Error: stack underflow";
	return mas[top_ind];
}
#endif // !_STACK_H_
