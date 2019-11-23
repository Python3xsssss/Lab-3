#include "math_exp.h"
#include "stack_on_array.h"

std::ostream& operator<<(std::ostream& ostr, const Lexeme& lex)
{
	if (const Operation* op = dynamic_cast<const Operation*>(&lex))
		ostr << *op;
	else if (const Literal_const* lit = dynamic_cast<const Literal_const*>(&lex))
		ostr << *lit;
	else
		throw "Illegal type of lexeme";

	return ostr;
}

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
	else
		priority = -1;
}

std::ostream& operator<<(std::ostream& ostr, const Literal_const& lit)
{
	return ostr << lit.value;
}


Literal_const& Literal_const::operator= (double data)
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

std::ostream& operator<<(std::ostream& ostr, const Operation& op)
{
	return ostr << op.symbol;
}


static string readNumber(const string& expr, int& i)
{
	string tmp;
	bool flag = true;
	size_t len = expr.length();
	while ((i < len) && ((expr[i] >= '0') && (expr[i] <= '9') || (expr[i] == '.') && flag))
	{
		tmp.push_back(expr[i]);
		if (expr[i] == '.')
			flag = false;
		i++;
	}
	return tmp;
}

static void operationToStack(const Operation op, vector<Lexeme*>& out, Stack<Operation>& st)
{
	size_t priority = op.priority;

	if (op.symbol != '(')
		while (!st.Empty() &&  (st.Top().symbol != '(') && (st.Top().priority >= priority))
		{
			Operation* cont = new Operation;
			*cont = st.Pop().symbol;
			out.push_back(cont);
		}

	if (op.symbol == ')')
	{
		st.Pop();
	}
	else
		st.Push(op);
}

static int strToInt(string str)
{
	size_t exponent = 1;
	int result = 0;
	size_t digits = str.length();

	for (int i = digits - 1; i >= 0; i--)
	{
		result += (static_cast<int>(str[i]) - static_cast<int>('0')) * exponent;
		exponent *= 10;
	}
	return result;
}

static bool analyze(string expr, vector<Lexeme*>& out)
{
	enum condition { FAILURE = -1, SUCCESS, START, INTERM, END } status = START;

	int i = 0;
	int braces_open = 0;
	size_t len = expr.length();
	bool unary = true;

	while (status > SUCCESS)
	{
		while ((i < len) && (expr[i] == ' '))
			i++;
		char tmp = (i < len) ? expr[i] : '\0';
		switch (status)
		{
		case START:
			if (tmp == '\0')
				status = END;
			else if (tmp == '(')
			{
				Operation* cont = new Operation;
				*cont = tmp;
				out.push_back(cont);
				braces_open++;
			}
			else if (tmp == '-')
			{
				bool flag = true;
				if (out.size() > 0)
				{
					Operation* tmp = dynamic_cast<Operation*>(out.back());
					if (tmp)
						flag = (tmp->symbol == '(');
				}
				if (flag)
				{
					Literal_const* cont = new Literal_const;
					*cont = 0;
					out.push_back(cont);
					i--;
					status = INTERM;
				}
				else
					status = FAILURE;
			}
			else if ((tmp >= '0') && (tmp <= '9'))
			{
				Literal_const* cont = new Literal_const;
				*cont = std::stod(readNumber(expr, i));
				out.push_back(cont);
				i--;
				status = INTERM;
			}
			else
				status = FAILURE;
			break;

		case INTERM:
			if (tmp == '\0')
				status = END;
			else if (tmp == ')')
			{
				braces_open--;
				if (braces_open >= 0)
				{
					Operation* cont = new Operation;
					*cont = tmp;
					out.push_back(cont);
				}
				else
					status = FAILURE;
			}
			else if ((tmp == '+') || (tmp == '-') || (tmp == '*') || (tmp == '/'))
			{
				Operation* cont = new Operation;
				*cont = tmp;
				out.push_back(cont);
				status = START;
			}
			else
				status = FAILURE;
			break;

		case END:
			status = (braces_open == 0) ? SUCCESS : FAILURE;
			break;

		default:
			break;
			
		}

		i++;
	}
	
	return (status == SUCCESS);
}

static vector<Lexeme*> toPolskaNotation(vector<Lexeme*> in)
{
	vector<Lexeme*> out;
	size_t size = in.size();
	Stack<Operation> st;

	for (size_t i = 0; i < size; i++)
	{
		if (Literal_const* tmp = dynamic_cast<Literal_const*>(in[i]))
			out.push_back(tmp);
		else if (Operation* tmp = dynamic_cast<Operation*>(in[i]))
			operationToStack(*tmp, out, st);
	}
	while (!st.Empty())
	{
		Operation* cont = new Operation;
		*cont = st.Pop();
		out.push_back(cont);
	}

	return out;
}

static double arithmetic(Operation op, Stack<double>& values)
{
	double right = values.Pop();
	double left = values.Pop();
	double result = 0.0;
	switch (op.symbol)
	{
		case '+': 
			result = left + right;
			break;

		case '-': 
			result = left - right;
			break;

		case '*': 
			result = left * right;
			break;

		case '/': 
			if (right == 0.0)
				throw "Error: divide by zero";
			result = left / right;
			break;

		default: 
			result = 0;
			break;
	}

	values.Push(result);
	return result;
}

static double polskaToRes(vector<Lexeme*>& in)
{
	Stack<double> values;
	size_t size = in.size();

	for (size_t i = 0; i < size; i++)
	{
		if (Literal_const* tmp = dynamic_cast<Literal_const*>(in[i]))
			values.Push(tmp->value);
		else if (Operation* tmp = dynamic_cast<Operation*>(in[i]))
		{
			arithmetic(*tmp, values);
		}	
	}
	return values.Pop();
}


double calc(string expression)
{
	vector<Lexeme*> checked;
	if (!analyze(expression, checked))
		throw "Incorrect mathematical expression";

	vector<Lexeme*> polska = toPolskaNotation(checked);
	return polskaToRes(polska);
}