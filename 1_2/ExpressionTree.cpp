#include "stdafx.h"
#include "ExpressionTree.h"
#include "FunctionLeaf.h"

using namespace std;

ExpressionTree::ExpressionTree()
{
	value = "";
	lhs = NULL;
	rhs = NULL;
}


ExpressionTree* ExpressionTree::clone()
{
	ExpressionTree* temp = new ExpressionTree();
	temp->value = value;							//copies to temp value and a clone of
	if (lhs != NULL)  temp->lhs = lhs->clone();		// its lhs and rhs
	if (rhs != NULL) temp->rhs = rhs->clone();
	return temp;
}

void ExpressionTree::construct(string PF)
{
	stack<ExpressionTree*> treeStack;		//will help to obey the order of operations
	ExpressionTree* T1, * T2;				//	specified by the postfix string
	string val = "";

	while (PF.length() > 0)
	{

		if (PF[0] == ' ')
		{
			PF.erase(0, 1);				//remove whitespace
		}
		else if (isOperand(PF))
		{
			while (isOperand(PF))
			{
				val += PF[0];			//add any operands to val
				PF.erase(0, 1);
			}

			ExpressionTree* t;			//make a new expression tree with val
			t = new ExpressionTree();
			t->value = val;
			treeStack.push(t);
			val = "";
		}
		else if (isOperator(PF[0]))
		{
			val += PF[0];
			PF.erase(0, 1);

			T1 = treeStack.top();
			treeStack.pop();
			T2 = treeStack.top();
			treeStack.pop();

			ExpressionTree* t;
			t = new ExpressionTree();		//take two trees off stack and make a new tree 
			t->value = val;					//with operator value, then push its ptr on the stack
			t->lhs = T2;
			t->rhs = T1;
			treeStack.push(t);
			val = "";
		}
	}	//END LOOP

	value = treeStack.top()->value;
	lhs = treeStack.top()->lhs;
	rhs = treeStack.top()->rhs;
	treeStack.pop();
}

void ExpressionTree::inorder()
{
	if (lhs != NULL)	cout << "(";
	if (lhs != NULL)	lhs->inorder();
	cout << ' ' << value << ' ';
	if (rhs != NULL)	rhs->inorder();
	if (rhs != NULL)	cout << ")";
}

void ExpressionTree::display()
{
	if (lhs != NULL)	lhs->inorder();
	cout << ' ' << value << ' ';
	if (rhs != NULL)	rhs->inorder();
	cout << endl;
}

void ExpressionTree::destroy()
{
	if (lhs != NULL)	lhs->destroy();
	if (rhs != NULL)	rhs->destroy();
	//cout << "Deleting " << value << endl;
	delete this;
}

//Transforms the ExpressionTree called on into an ExpressionTree representing its derivative
void ExpressionTree::deriv()
{
	ExpressionTree* T1, * T2, * T3, * T4, * T5;
	if (isVar(value[0]))		value = "1";		//base case: value at root of this subtree is x	which makes its derivative one
	else if (isNum(value[0]))	value = "0";		//base case: value at root of this subtree is numeric which makes its derivative zero 
	else
	{
		switch (value[0])
		{	//For add and sub, only need to take deriv of lhs and rhs
		case '+':	//add tree derivs
		case '-':	//sub tree derivs
			lhs->deriv();
			rhs->deriv();
			break;
		case '*':	//product rule

					//Clones of lhs and rhs to use for T1*T2' + T3*T4' (product rule)
			T1 = lhs->clone();
			T2 = rhs->clone();

			T3 = rhs->clone();
			T4 = lhs->clone();


			value = "+";		//instead of multiplying left and right sides, we add 2 products
			lhs->value = "*";	//make the value in lhs and rhs multiplication operators
			rhs->value = "*";

			//destroy any children more than 1 separation away to avoid orphans
			if (lhs->lhs != NULL)		lhs->lhs->destroy();
			if (lhs->lhs != NULL)   lhs->rhs->destroy();

			//apply product rule with cloned trees
			lhs->lhs = T1;
			lhs->rhs = T2;
			T2->deriv();

			if (rhs->lhs != NULL)	rhs->lhs->destroy();
			if (rhs->rhs != NULL)	rhs->rhs->destroy();

			rhs->lhs = T3;
			rhs->rhs = T4;
			T4->deriv();

			break;
		case '/':	//quotient rule

					//T1 and T4 are numerators
					//T2, T3, and T5 are denominators
					//clones of lhs and rhs to use for (T1*T2' - T3*T4')/(T5^2)
			T1 = lhs->clone();
			T2 = rhs->clone();

			T3 = rhs->clone();
			T4 = lhs->clone();
			T5 = rhs->clone();

			//lhs will be a subtraction tree
			lhs->value = "-";

			//multipy deriv of num by den funct
			if (lhs->lhs == NULL)	lhs->lhs = new ExpressionTree();
			lhs->lhs->value = "*";
			if (lhs->lhs->lhs != NULL)	lhs->lhs->lhs->destroy();
			if (lhs->lhs->rhs != NULL)	lhs->lhs->rhs->destroy();

			lhs->lhs->lhs = T1;		//num
			lhs->lhs->rhs = T2;		//den	
			T1->deriv();

			//multiply deriv of den by num funct
			if (lhs->rhs == NULL)	lhs->rhs = new ExpressionTree();	//make a new tree to hold * if necessary
			lhs->rhs->value = "*";
			if (lhs->rhs->lhs != NULL)	lhs->rhs->lhs->destroy();		//if there are already existing branches, cut them
			if (lhs->rhs->rhs != NULL)	lhs->rhs->rhs->destroy();		//	to replace with T3 and T4
			lhs->rhs->lhs = T3;		//den
			lhs->rhs->rhs = T4;		//num
			T3->deriv();

			rhs->value = "^";
			rhs->lhs = T5;
			if (rhs->rhs == NULL)	rhs->rhs = new ExpressionTree();
			rhs->rhs->value = "2";
			if (rhs->rhs->lhs != NULL)
			{
				rhs->rhs->lhs->destroy();
				rhs->rhs->lhs = NULL;
			}
			if (rhs->rhs->rhs != NULL)
			{
				rhs->rhs->rhs->destroy();
				rhs->rhs->rhs = NULL;
			}

			break;
		case '^':	//power law
			ExpressionTree * base = lhs->clone();	//allows for chain rule if enter for ex (x+2)^2
			ExpressionTree* power = rhs->clone();
			value = "*";
			lhs->destroy();
			rhs->destroy();
			lhs = NULL;
			rhs = NULL;

			if (isNum(power->value) && isNum(base->value))
			{
				value = "0";
			}
			else if (isNum(power->value))
			{
				rhs = new ExpressionTree();
				rhs->value = "^";

				double powerDouble = stod(power->value);
				int decIndex;

				rhs->rhs = new ExpressionTree();
				rhs->rhs->value = to_string((powerDouble - 1));
				decIndex = rhs->rhs->value.find('.');
				rhs->rhs->value = rhs->rhs->value.substr(0, decIndex + 2);	//set number of decimal places for number values that have been altered

				rhs->lhs = base->clone();


				if (!isOperand(base->value))
				{
					ExpressionTree* toDeriv;
					toDeriv = base->clone();
					toDeriv->deriv();
					lhs = new ExpressionTree();
					lhs->value = "*";
					lhs->lhs = toDeriv;
					lhs->rhs = power->clone();
				}
				else
				{
					lhs = power->clone();
				}


			}
			else					//	TODO: exponential functions
			{


				lhs = new ExpressionTree();
				lhs->value = "^";

				lhs->lhs = base->clone();
				lhs->rhs = power->clone();

				if (power->lhs != NULL && power->rhs != NULL)		//chain rule if there is more than a single numeric value in power
				{
					rhs = new ExpressionTree();
					rhs->value = "*";
					rhs->lhs = power->clone();
					rhs->lhs->deriv();
					rhs->rhs = new FunctionLeaf();
					rhs->rhs->lhs = new ExpressionTree();
					rhs->rhs->lhs->value = "ln";
					rhs->rhs->rhs = base->clone();

				}
				else											//do exponential function differentiation rule w/o chain rule
				{
					rhs = new FunctionLeaf();

					rhs->lhs = new ExpressionTree();
					rhs->lhs->value = "ln";

					rhs->rhs = new ExpressionTree();
					rhs->rhs = base->clone();
				}

			}


			power->destroy();
			base->destroy();

			break;
		}
	}
}

void ExpressionTree::simplify()
{
	if (isNum(value))	return;
	if (isVar(value[0]))	return;

	switch (value[0])
	{
	case '*':
		if (lhs->value == "0" || rhs->value == "0")
		{
			value = "0";
			lhs->destroy();
			rhs->destroy();
			lhs = NULL;
			rhs = NULL;
		}
		else if (isNum(lhs->value) && isNum(rhs->value))
		{
			double a, b;
			int decIndex;
			a = stod(lhs->value);
			b = stod(rhs->value);
			value = to_string(a * b);
			decIndex = value.find('.');
			value = value.substr(0, decIndex + 2);
			lhs->destroy();
			rhs->destroy();
			lhs = NULL;
			rhs = NULL;
		}
		else if (lhs->value == "1" || lhs->value == "1.0")
		{
			ExpressionTree* T1;
			T1 = rhs->clone();
			lhs->destroy();
			rhs->destroy();
			value = T1->value;
			lhs = T1->lhs;
			rhs = T1->rhs;
		}
		else if (rhs->value == "*")
		{
			if (isNum(lhs->value) && isNum(rhs->lhs->value))
			{
				ExpressionTree* T1;
				T1 = rhs->rhs->clone();
				double num1 = stod(lhs->value);
				double num2 = stod(rhs->lhs->value);
				rhs->lhs->destroy();
				rhs->rhs->destroy();
				double prod = num1 * num2;
				int decIndex;

				lhs->value = to_string(prod);
				decIndex = lhs->value.find('.');
				lhs->value = lhs->value.substr(0, decIndex + 2);
				rhs = T1;
			}

		}
		break;
	case '+':
		if (lhs->value == "0")
		{
			ExpressionTree* T1;
			T1 = rhs->clone();		//clone rhs
			rhs->destroy();				// delete it
			lhs->destroy();
			value = T1->value;		//	take value and ptrs 
			lhs = T1->lhs;			//	from T1
			rhs = T1->rhs;
		}
		else if (rhs->value == "0")
		{
			ExpressionTree* T1;
			T1 = lhs->clone();
			rhs->destroy();
			lhs->destroy();
			value = T1->value;
			lhs = T1->lhs;
			rhs = T1->rhs;
		}
		break;
	case '-':
		if (rhs->value == "0")
		{
			ExpressionTree* T1;
			T1 = lhs->clone();
			rhs->destroy();
			lhs->destroy();
			value = T1->value;
			lhs = T1->lhs;
			rhs = T1->rhs;

		}

		break;
	case '^':
		if (rhs->value == "1" || rhs->value == "1.0")	//if it's to the power of 1, make this tree
		{													//remove the power and make this tree the base tree
			ExpressionTree* T1;
			T1 = lhs->clone();
			rhs->destroy();
			lhs->destroy();
			value = T1->value;
			lhs = T1->lhs;
			rhs = T1->rhs;
		}
		break;
	}
	if (lhs != NULL)	lhs->simplify();
	if (rhs != NULL)	rhs->simplify();
}

void ExpressionTree::postfix(string& pf)
{
	if (lhs != NULL)		lhs->postfix(pf);
	if (rhs != NULL)		rhs->postfix(pf);
	pf += ' ' + value;
}