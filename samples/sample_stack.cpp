#include "stack_on_array.h"
#include <string>
#include <conio.h>

int main()
{
	Stack<char> st;
	std::string tmp;
	std::cin >> tmp;
	bool flag = true;
	size_t i = 0;
	while ((tmp[i] != '\0') && flag)
	{
		if ((tmp[i] == '(') || (tmp[i] == '{') || (tmp[i] == '['))
			st.Push(tmp[i]);
		else if (st.GetSize() > 0)
		{
			char comp = st.Top();
			if ((tmp[i] == ')') && (comp == '(') || (tmp[i] == '}') && (comp == '{') || (tmp[i] == ']') && (comp == '['))
				st.Pop();
			else
				flag = false;
		}
		else
			flag = false;
			
		i++;
	}
	if (st.GetSize() > 0)
		flag = false;
	std::cout << std::endl << flag << std::endl;
	_getch();
}