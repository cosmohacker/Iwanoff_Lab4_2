#ifndef function
#define function

typedef double (*Function)(double);

const double epsilon = 0.0000001;

double minFirstDerivative(Function f, double x, double y);
double calculateDerivative(Function f, double x, int order);

#endif // function