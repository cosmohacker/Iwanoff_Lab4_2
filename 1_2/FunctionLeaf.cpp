#include "stdafx.h"
#include "FunctionLeaf.h"

using namespace std;

void FunctionLeaf::inorder()
{
	if (lhs != NULL)	cout << "(";
	if (lhs != NULL)	lhs->inorder();
	cout << '(';
	if (rhs != NULL)	rhs->inorder();
	cout << ')';
	if (rhs != NULL)	cout << ")";
}

FunctionLeaf::FunctionLeaf()
{
	value = "F";
	lhs = NULL;
	rhs = NULL;
}