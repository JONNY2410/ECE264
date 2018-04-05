#include <stdio.h>
#include <limits.h>
#include "hw02.h"
#include <stdlib.h>
int main(int argc, char* argv[])
{
	print_integer(0,36,"$");
	printf("\n");

	print_integer(1,2,"");
	printf("\n");

	print_integer(8,2,"");
	printf("\n");

	print_integer(-8,2,"");
	printf("\n");

	print_integer(10,16,"&");
	printf("\n");

	print_integer(-17,16,"&");
	printf("\n");

	print_integer(INT_MAX,2,"");
	printf("\n");

	print_integer(INT_MIN,2,"");
	printf("\n");

	print_integer(INT_MAX,16,"&");
	printf("\n");

	print_integer(INT_MIN,16,"&");
	printf("\n");

	print_integer(65536,36,"0x");
	printf("\n");

	print_integer(-65536,36,"0x");
	printf("\n");

	print_integer(INT_MAX,2,"0b");
	print_integer(INT_MAX,16,"*0x");
	printf("\n");

	return EXIT_SUCCESS;
}
