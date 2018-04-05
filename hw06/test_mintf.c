#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>
#include "mintf.h"
int main(int argc, char* augv[]){

	mintf("Does the code work?\n");	
	mintf("print 1, %d \n",1024);
	mintf("ok, looks decimal works, how about hex %x\n",1024);
	mintf("how about binary, int_min: %x\n",INT_MIN);
	mintf("int_max %x\n",INT_MAX);
	mintf("int_min in binary: %b\n", INT_MIN);
	mintf("good, good, let's try some double, my favorite double is %$\n",INT_MIN-0.99);
	mintf("great, other double like %$\n",INT_MAX+0.99);
	mintf("some strings maybe? : %s\n", "Jonny is a cool kid");
	mintf("characters? : %c\n",'Y');
	mintf("end with %%\n\n\n\n");
	
	return EXIT_SUCCESS;

}
