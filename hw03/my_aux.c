#include <math.h>
#include <stdio.h>
double function_to_be_integrated(double x)
{
	double result;
	result = pow(1.001,x);
	return result;
}
