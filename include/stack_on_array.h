#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>

#define MAX_STACK_SIZE 10000

typedef unsigned int size_T;

template <typename ValType>
class Stack
{
private:
	ValType* mas;
	size_T size;
	size_T top_ind;
	void Resize()
	{
		if (size == MAX_STACK_SIZE)
			throw "Error: stack overflow";
		size_T new_size = size + size / 3 + 1;
		if (new_size > MAX_STACK_SIZE)
			new_size = MAX_STACK_SIZE;
		ValType* tmp = new ValType[new_size];
		for (size_T i = 0; i < size; i++)
			tmp[i] = mas[i];
		delete[] mas;
		mas = tmp;
		size = new_size;
	}

public:
	Stack(size_T s = 10000)
	{
		if (size < 0)
			throw "Error: illegal size";
		size = s;
		mas = new ValType[size];
		top_ind = -1;
	}

	Stack(const Stack<ValType> &st)
	{
		size = st.size;
		mas = new ValType[size];
		for (size_T i = 0; i < size; i++)
			mas[i] = st.mas[i];
		top_ind = st.top_ind;
	}

	~Stack() { delete[] mas; }

	bool Full() { return (top_ind + 1 == size); }
	bool Empty() { return (top_ind == -1); }
	size_T GetSize() { return top_ind + 1; }

	void Push(ValType elem)
	{
		if (Full())
			Resize();
		top_ind++;
		mas[top_ind] = elem;
	}

	ValType Pop()
	{
		if (Empty())
			throw "Error: stack underflow";
		top_ind--;
		return mas[top_ind + 1];
	}

	ValType Top()
	{
		if (Empty())
			throw "Error: stack underflow";
		return mas[top_ind];
	}
};

#endif // !_STACK_H_
