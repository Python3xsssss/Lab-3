#include "math_exp.h"

Operation::Operation(char sym)
{
	symbol = sym;
	setPriority();
}

Operation::Operation(const Operation& op)
{
	symbol = op.symbol;
	priority = op.priority;
}

Operation& Operation::operator= (char sym)
{
	symbol = sym;
	setPriority();

	return *this;
}

Operation& Operation::operator= (const Operation& op)
{
	if (this == &op)
		return *this;

	symbol = op.symbol;
	priority = op.priority;

	return *this;
}

void Operation::setPriority()
{
	if ((symbol == '(') || (symbol == ')'))
		priority = 0;
	else if ((symbol == '+') || (symbol == '-'))
		priority = 1;
	else if ((symbol == '*') || (symbol == '/'))
		priority = 2;
}


Literal_const& Literal_const::operator= (int data)
{
	value = data;
	return *this;
}

Literal_const& Literal_const::operator= (const Literal_const& cs)
{
	if (this == &cs)
		return *this;

	value = cs.value;
	return *this;
}


static string readNumber(const string& expr, size_t& start_pos)
{
	string tmp;
	size_t i = start_pos;
	size_t len = expr.length();
	while ((i < len) && (expr[i] >= '0') && (expr[i] <= '9'))
	{
		tmp.push_back(expr[i]);
		i++;
	}
	return tmp;
}

static void operationToStack(const char tmp, vector<Lexeme>& out, Stack<Operation>& st)
{
	Operation op = tmp;
	size_t priority = op.priority;

	if (tmp != '(')
		while (!st.Empty() &&  (st.Top().symbol != '(') && (st.Top().priority >= priority))
		{
			Operation cont = st.Pop().symbol;
			out.push_back(cont);
		}

	if (tmp == ')')
		st.Pop();
	else
		st.Push(op);
}

static int strToInt(string str)
{
	size_t exponent = 1;
	int result = 0;
	size_t digits = str.length();

	for (size_t i = digits - 1; i > 0; i--)
	{
		result += (static_cast<int>(str[i]) - static_cast<int>('0')) * exponent;
		exponent *= 10;
	}

	return result;
}

static bool analyzeToPolskaNotation(string expr, vector<Lexeme>& out)
{
	enum condition { FAILURE = -1, SUCCESS, START, INTERM, END } status = START;

	size_t i = 0;
	size_t braces_open = 0;
	size_t len = expr.length();
	Stack<Operation> st;

	while (status > SUCCESS)
	{
		char tmp = expr[i];
		switch (status)
		{
			case START:
			{
				if (tmp == '\0')
					status = END;
				else if (tmp == '(')
					braces_open++;
				else if (tmp == '-')
				{
					Literal_const cont = 0;
					out.push_back(cont);
					i--;
					status = INTERM;
				}
				else if ((tmp >= '0') && (tmp <= '9'))
				{
					Literal_const cont = strToInt(readNumber(expr, i));
					out.push_back(cont);
					i--;
					status = INTERM;
				}
				else
					status = FAILURE;
				break;
			}

			case INTERM:
			{
				if (tmp == '\0')
					status = END;
				else if (tmp == ')')
				{
					braces_open--;
					status = (braces_open >= 0) ? INTERM : FAILURE;
				}
				else if ((tmp == '+') || (tmp == '-') || (tmp == '*') || (tmp == '/'))
				{
					operationToStack(tmp, out, st);
					status = START;
				}
				else
					status = FAILURE;
				break;
			}

			case END:
			{
				status = (braces_open == 0) ? SUCCESS : FAILURE;
				break;
			}

			default:
			{
				break;
			}
			
		}
		i++;
	}
	
	return status;
}

static int arithmetic(Operation op, Stack<int>& values)
{
	int right = values.Pop();
	int left = values.Pop();
	switch (op.symbol)
	{
		case '+': return left + right;

		case '-': return left - right;

		case '*': return left * right;

		case '/': return left / right;

		default: return 0;
	}
}

static int polskaToRes(vector<Lexeme>& in)
{
	Stack<int> values;
	size_t size = in.size();
	int result;

	for (size_t i = 0; i < size; i++)
	{
		if (Literal_const* tmp = dynamic_cast<Literal_const*>(&in[i]))
			values.Push(tmp->value);
		else if (Operation* tmp = dynamic_cast<Operation*>(&in[i]))
			result = arithmetic(*tmp, values);
	}
}


int calc(string expression)
{
	vector<Lexeme> polska;
	if (!analyzeToPolskaNotation(expression, polska))
		throw "Incorrect mathematical expression";
	else
		return polskaToRes(polska);
}