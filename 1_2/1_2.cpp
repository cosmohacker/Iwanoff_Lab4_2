#include "func.h"
#include <iostream>
#include <cmath>

using namespace std;

//6x^5 + 2x^5 - 9x^1 + 25x^0
double staticFunc1(double value) {
	return  (6 * pow(value, 5) + 2 * pow(value, 5) - 9 * pow(value, 1) + 25 * pow(value, 0));
}
//12x^2 + 1x^3 - 7x^1 + 10x^0
double staticFunc2(double value) {
	return  (12 * pow(value, 2) + 1 * pow(value, 3) - 7 * pow(value, 1) + 10 * pow(value, 0));
}

int main()
{
	cout << minFirstDerivative(sin, 2, 5) << endl;
	cout << minFirstDerivative(staticFunc1, 2, 5) << endl;
	cout << minFirstDerivative(sin, 2, 5) << endl;
	cout << minFirstDerivative(staticFunc2, 3, 5) << endl;
}