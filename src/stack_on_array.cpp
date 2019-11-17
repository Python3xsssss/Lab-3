#include "stack_on_array.h"

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
Stack<ValType>::Stack(size_t s = 10000)
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
