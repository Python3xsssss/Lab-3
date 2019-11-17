#include "stack_on_list.h"

template <typename ValType>
Stack<ValType>::Stack(const Stack<ValType> &st)
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

template <typename ValType>
Stack<ValType>::~Stack()
{
	while (top != nullptr)
		Pop();
}

template <typename ValType>
void Stack<ValType>::Push(ValType elem)
{
	if (size == MAX_STACK_SIZE)
		throw "Error: stack overflow";
	Node<ValType> *tmp = new Node<ValType>;

	tmp->data = elem;
	tmp->next = top;
	top = tmp;
	size++;
}
template <typename ValType>
ValType Stack<ValType>::Stack::Pop()
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

template <typename ValType>
ValType Stack<ValType>::Top()
{
	if (size == 0)
		throw "Error: stack underflow";
	return top->data;
}
