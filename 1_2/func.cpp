#include <iostream>
#include <cmath>
#include "func.h"

using namespace std;

//I'm calculating derivative here.
double calculateDerivative(Function f, double a, int order)
{
	if (order == 0)
		return f(a);

	double x = calculateDerivative(f, a + epsilon, order - 1);
	double y = calculateDerivative(f, a - epsilon, order - 1);

	return (x - y) / (2 * epsilon);
}

//Finding minimum first derivative.
double minFirstDerivative(Function f, double x, double y)
{
	double min = calculateDerivative(f, y, 0);
	double tmp;
	for (int i = y - 1; i <= x; i--)
	{
		tmp = calculateDerivative(f, i, 0);
		if (min > tmp)
			min = tmp;
	}
	return min;
}