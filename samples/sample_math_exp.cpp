#include "math_exp.h"
#include <conio.h>

using namespace std;

int main()
{
	string input;
	cout << "Enter the formula using: '0' '1' '2' '3' '4' '5' '6' '7' '8' '9' '0' '+' '-' '*' '/' '(' ')' " << endl;
	getline(cin, input);
	cout << "= " << calc(input) << endl;
	_getch();
}
