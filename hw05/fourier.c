#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L
double simpson_numerical_integration(Integrand intg_arg) {
	double integral = 0.0;
	double upper_limit = intg_arg.upper_limit;
	double lower_limit = intg_arg.lower_limit;
	int n_intervals = intg_arg.n_intervals;
	double lowbound = 0;
	double highbound = 0;
	double midpoint = 0;
	double interval = (upper_limit - lower_limit)/n_intervals;
	//using counters to get the simpson rule work
	for(int i = 0; i < n_intervals; i++){
		lowbound = lower_limit + i*interval;
		highbound = lower_limit + (i+1)* interval;
		midpoint = (lowbound + highbound)/2;
		integral = integral + ((highbound-lowbound)/6)*(intg_arg.func_to_be_integrated(lowbound) + 4*(intg_arg.func_to_be_integrated(midpoint)) + intg_arg.func_to_be_integrated(highbound));
	}
	return integral;
}

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, double (*cos_sin)(double)) {
	double integral = 0.0;
	double upper_limit = intg_arg.upper_limit;
	double lower_limit = intg_arg.lower_limit;
	double L  = (upper_limit-lower_limit)/2;
	int n_intervals = intg_arg.n_intervals;
	double lowbound = 0;
	double highbound = 0;
	double midpoint = 0;
	double interval = (upper_limit - lower_limit)/n_intervals;
	//using counters to get the simpson rule work
	for(int i = 0; i < n_intervals; i++){
		lowbound = lower_limit + i*interval;
		highbound = lower_limit + (i+1)* interval;
		midpoint = (lowbound + highbound)/2;
		integral = integral + ((highbound-lowbound)/6)*(intg_arg.func_to_be_integrated(lowbound)*(cos_sin(n*M_PI*lowbound/L)) + 4*(intg_arg.func_to_be_integrated(midpoint)*(cos_sin(n*M_PI*midpoint/L))) + intg_arg.func_to_be_integrated(highbound)*(cos_sin(n*M_PI*highbound/L)));
	}
	return integral;
}
void fourier_coefficients(Fourier fourier_arg) {
	for (int i = 0; i < fourier_arg.n_terms; i++) {
		fourier_arg.a_i[i] = (1/((fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit)/2))*simpson_numerical_integration_for_fourier(fourier_arg.intg, i, cos);
		fourier_arg.b_i[i] = (1/((fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit)/2))*simpson_numerical_integration_for_fourier(fourier_arg.intg, i, sin);
	}
}
