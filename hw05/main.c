#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#include "util.h"
#include "fourier.h"
#include "math.h"
int main(int argc, char ** argv) {
	if(argc==6){
		Integrand integrand = {
			.upper_limit = atof(argv[3]),  // TODO: change to the real value
			.lower_limit = atof(argv[2]), // TODO: change to the real value
			.n_intervals = atoi(argv[4]),    // TODO: change to the real value

		};
		if(integrand.n_intervals <1){
		   integrand.n_intervals=1;
		}
		int n_terms = atoi(argv[5]);         // TODO: change to the real value
		if(n_terms<1){
			n_terms = 1;
		}
		if(argv[1][1]=='\0'){
			switch(atoi(argv[1])){
				case 1: integrand.func_to_be_integrated = unknown_function_1;
					break;
				case 2:
					integrand.func_to_be_integrated = unknown_function_2;
					break;
				case 3:
					integrand.func_to_be_integrated = unknown_function_3;
					break;
				default:
					return EXIT_FAILURE;
			}		
		}
		Fourier fourier = {
			.intg      = integrand,
			.n_terms   = n_terms,		//	this line has been modified by Jonny
			.a_i       = malloc(sizeof(*fourier.a_i) * n_terms),
			.b_i       = malloc(sizeof(*fourier.b_i) * n_terms)
		};

		// If allocation of fourier.a_i and/or fourier.b_i failed, then free the
		// one that didn't fail and then exit with EXIT_FAILURE.
		if (fourier.a_i == NULL || fourier.b_i == NULL) {
			free(fourier.a_i);  // free(..) has not effect if its argument is NULL
			free(fourier.b_i);
			return EXIT_FAILURE;
		}
		if((fourier.n_terms>=1)&&((fourier.intg.upper_limit-fourier.intg.lower_limit)!=0)){
			fourier_coefficients(fourier);
		}
		else{
			return EXIT_FAILURE;
		}

		print_fourier_coefficients(fourier.a_i, fourier.b_i,fourier.n_terms);	//get all the coefficients.
		function_plot(unknown_function_3,integrand.lower_limit,integrand.upper_limit,fourier.a_i,fourier.b_i,fourier.n_terms,"aux.m");	
		free(fourier.a_i);
		free(fourier.b_i);

		return EXIT_SUCCESS;
	}
	else{
		return EXIT_FAILURE;
	}
} 
