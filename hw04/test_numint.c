/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
// do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#ifndef NTEST_STRUCT 
#include "numint.h"
#else
#include "numint_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile

// fill in the correct statements to complete the main function
// we expect four arguments:
//
// the first argument is 1 character from the sets {"1", "2", "3"}
// it specifies the unknown function to be integrated
// 1:  unknown_function_1
// 2:  unknown_function_2
// 3:  unknown_function_3
// otherwise: return EXIT_FAILURE

// to integrate any of the three functions, expect the next three 
// arguments to be the lower limit of the integration (double), 
// the upper limit of the integration (double), and the number of 
// intervals for the integration (int)
//
// if the number of steps is less than 1, set it to 1

// use atof to convert an argument to a double 
// use atoi to convert an argument to an int

// You should declare a variable of type Integrand.  You should use the four 
// arguments to initialize the structure, and pass the structure to the 
// simpson's method

// after printing the integral, return EXIT_SUCCESS

int main(int argc, char * * argv)
{
	//Initialization for the structure and integral
	if(argc == 5){
		double integral = 0.0;
		int option;
		//initialize structure
		Integrand intg_arg;
		intg_arg.n_intervals = 0;
		intg_arg.lower_limit = atof(argv[2]);
		intg_arg.upper_limit = atof(argv[3]);
		intg_arg.func_to_be_integrated = 0;
		int n_intervals = atoi(argv[4]);
		if(n_intervals<1){
			n_intervals=1;
		}
		intg_arg.n_intervals = n_intervals;
		option = atoi(argv[1]);
		if(argv[1][1]=='\0'){
			//chose option
			switch(option){
				case 1:	intg_arg.func_to_be_integrated = unknown_function_1;
						integral = simpson_numerical_integration(intg_arg);
						break;	
				case 2: 
						intg_arg.func_to_be_integrated = unknown_function_2;
						integral = simpson_numerical_integration(intg_arg);
						break;
				case 3:
						intg_arg.func_to_be_integrated = unknown_function_3;
						integral = simpson_numerical_integration(intg_arg);
						break;
				default: 
						return EXIT_FAILURE;
			}	
			printf("%.10e\n", integral);
			return EXIT_SUCCESS;
		}
		else{
			return EXIT_FAILURE;}
	}
	else{
		return EXIT_FAILURE;
	}
}
