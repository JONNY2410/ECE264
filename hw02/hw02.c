/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include<stdio.h>
#include "hw02.h"

void print_integer(int n, int radix, char* prefix){
	long int num = n;	// using long int incase the INT_MIN cause the data ovweflow	
	int counter = 0;	//counter used to count the iteration times.
	long int sign_convert;	//holder for the number after its sign being convetered.
	long int value_n;		//remain the original value wont be changed by operation.
	int quotient;
	int remainder;

	if (num<0){		//Convert negative number to positve number
		sign_convert = -num;
		num = sign_convert;
		fputc('-',stdout);	//print out the "-" sign
	}
	value_n = num;		//assign the value n to another variable preventing its value from changing
	quotient = num / radix;
	remainder = num % radix;
	if(quotient==0){
		if(remainder<10){
			while(*prefix!='\0'){
				fputc(*prefix++,stdout);
			}
			fputc(remainder+'0',stdout);
		}
		else{
			while(*prefix!='\0'){
				fputc(*prefix++,stdout);
			}
			fputc(remainder+'W',stdout);
		} 
	}
	else{
		while(*prefix!='\0'){			//print the prefix
			fputc(*prefix++,stdout);
		}
		while(quotient!=0){
			remainder = num % radix;
			quotient = num / radix;
			num = quotient;
			counter++;
		}
		if(remainder<10){
			fputc(remainder+'0',stdout);
		}
		else {
			fputc(remainder+'W',stdout);
		}
		while(counter>1){ 
			counter--;
			num = value_n;
			for(int i = counter; i > 0; i--){
				remainder = num % radix;
				quotient = num / radix;
				num = quotient; 
			}
			if(remainder<10){
				fputc(remainder+'0',stdout);
			}
			else{
				fputc(remainder+'W',stdout);
			} 
		}    
	}
}

