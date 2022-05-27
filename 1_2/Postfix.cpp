#include "stdafx.h"
#include "Postfix.h"

string toPF(string infix)
{
	string postfix = "";
	stack<char> operatorStack;
	char currOp;
	istringstream reader(infix);

	while (!reader.eof())					//while still characters in reader stream to process
	{
		reader >> ws;										//if any ws starting stream, discard it
		while (infix[0] == ' ') infix.erase(0, 1);			//delete any whitespace from infix string	

		if (infix[0] == '(')											//if current symbol is a left paran
		{
			reader >> currOp;												// read in paran
			reader >> ws;													//	and ws

			operatorStack.push(infix[0]);									// push '(' it onto stack
			infix.erase(0, 1);												// erase '(' from infix
		}
		else if (infix[0] == ')')											//if current symbol is a right paran
		{
			reader >> currOp;												//	read in paran
			reader >> ws;													//	  and ws

			infix.erase(0, 1);												// erase ')' from infix

			while (!operatorStack.empty() && operatorStack.top() != '(')	//while still operators in stack and have not yet reached '('
			{
				postfix = postfix + operatorStack.top() + ' ';					//add top of stack to end of postfix string
				operatorStack.pop();											//pop top of stack
			}

			if (operatorStack.top() == '(')		operatorStack.pop();			//if a '(' remains on top of stack, pop it off
		}
		else if (isOperator(infix[0]))	//if first char of infix is an operator character (ex: * / + -)
		{
			//read in operator and any white space between it and operands
			reader >> currOp;
			reader >> ws;

			if (!operatorStack.empty())	//if there are operators in the stack
			{
				if (getPrecedence(infix[0]) > getPrecedence(operatorStack.top()))	//if the precedence of the current operator is greater than the precedence 
				{																	//of operator at top of stack
					operatorStack.push(infix[0]);										//push it onto stack
					infix.erase(0, 1);													//erase it from infix

				}
				else //if precedence lower
				{
					//dump stack into postfix string as long as stack operators are higher precedence than current char being checked
					//  and the stack has operators remaining in it
					while (!operatorStack.empty() && getPrecedence(operatorStack.top()) > getPrecedence(infix[0]))
					{
						postfix = postfix + operatorStack.top() + ' ';
						operatorStack.pop();
					}

					operatorStack.push(infix[0]);	//push scanned operator onto stack
					infix.erase(0, 1);				//erase scanned operator from infix string
				}
			}
			else						//if no operators in stack
			{
				operatorStack.push(infix[0]);	//push this operator onto stack
				infix.erase(0, 1);				//  then erase it from infix string
			}

		}
		else //first char of infix is not an operator
		{
			if (isNum(infix[0]))	//if character is numeric
			{
				int opand;				//int var to hold the number
				reader >> opand;		//read it in with the istringstream
				postfix = postfix + to_string(opand) + ' ';		//append it to postfix string

																//while the first character of infix string is numeric, erase it
				while (isNum(infix[0]))
				{
					infix.erase(0, 1);
				}
			}
			else if (isVar(infix[0]))	//if character is a valid variable character (a-z OR A-Z)
			{
				char opand;					//char var to hold variable symbol
				reader >> opand;			//read it from istringstream
				postfix = postfix + opand + ' ';	//append it to postfix string

				infix.erase(0, 1);			//erase it
			}

		}
	}

	while (!operatorStack.empty())
	{
		postfix = postfix + operatorStack.top() + ' ';
		operatorStack.pop();
	}
	reader >> currOp;

	return postfix;
}

bool isOperator(char c)
{
	if (c == '^' || c == '+' || c == '-' || c == '*' || c == '/')	 return true;
	return false;
}
bool isOperand(char c)
{
	if (c >= 'a' && c <= 'z') return true;
	if (c >= '0' && c <= '9') return true;
	return false;
}
bool isOperand(string s)
{
	if (isNum(s))	return true;
	if (isVar(s[0]))	return true;
	return false;
}
bool isNum(string s)
{
	if (isNum(s[0])) return true;
	if (s.length() > 1 && s[0] == '-' && isNum(s[1])) return true;
	return false;
}

bool isNum(char c)
{
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool isVar(char c)
{
	if (c >= 'a' && c <= 'z') return true;
	return false;
}
int	 getPrecedence(char c)
{
	if (c == '^')					  return 4;
	else if (c == '*' || c == '/')	  return 3;
	else if (c == '-')				  return 2;
	else if (c == '+')				  return 1;
	else							  return 0;
}

double evalPF(string& pf)
{
	double currOpand, lhs, rhs, newOpand;
	string token;
	char currOp;
	stack <double> operands;
	double result = 0.0;

	istringstream reader(pf);
	while (reader >> token)
	{
		if (isNum(token))
		{
			currOpand = stod(token); //convert string token to double
			operands.push(currOpand);

		}
		else if (isOperator(token[0]))
		{
			currOp = token[0];

			rhs = operands.top();
			operands.pop();
			lhs = operands.top();
			operands.pop();

			switch (currOp)
			{
			case '+':	newOpand = lhs + rhs;
				operands.push(newOpand);
				break;

			case '-':	newOpand = lhs - rhs;
				operands.push(newOpand);
				break;

			case '*':	newOpand = lhs * rhs;
				operands.push(newOpand);
				break;

			case '/':	newOpand = lhs / rhs;
				operands.push(newOpand);
				break;

			case '^':	newOpand = pow(lhs, rhs);
				operands.push(newOpand);
				break;

			}
		}
		else if (token[0] == 'l')
		{
			string function, value;
			function = token;
			reader >> value;
			currOpand = stod(value);
			newOpand = log(currOpand);
			operands.push(newOpand);
		}
	}

	result = operands.top();
	operands.pop();
	return result;

}