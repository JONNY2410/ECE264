#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "mintf.h"
void mintf(const char *format,...){
	int i = 0;			//pointer initialization
	long int hold = 0;		//temporary storage of data
	char* address = 0;		//access the address of the string
	long double hold2 = 0;		//temporary storage of the data
	long int divider=0;		//used to hold the quotient
	long int decimal = 0;		//used to hold 2 digits after decimal places
	long int digit_num = 0;		//used to hold all digits before decimal point
	va_list arg_pointer;	
	va_start (arg_pointer, format);
	while(format[i]!='\0'){
		if((format[i]=='%')&&((format[i+1]=='d')||(format[i+1]=='x')||(format[i+1]=='b')||(format[i+1]=='$')||(format[i+1]=='s')||(format[i+1]=='c')||(format[i+1]=='%'))){
			switch(format[i+1]){
				/*b */	case	0x62:
					hold = va_arg(arg_pointer, long int);
					if(hold==2147483648){
						fputc('-',stdout);
					}
					print_integer(hold,2,"0b");
					i++;	
					break;
				/*c*/	case	0x63:
					hold = va_arg(arg_pointer, long int);
					fputc(hold,stdout);
					i++;
					break;
				/*d*/	case	0x64:
					hold = va_arg(arg_pointer, long int);
					if(hold==2147483648){
						fputc('-',stdout);
					}
					print_integer(hold,10,"");
					i++;
					break;
				/*s*/	case	0x73:
					address = va_arg(arg_pointer, char*);
					while(*address!='\0'){
						fputc(*address,stdout);
						address++;
					}
					i++;
					break;

				/*x*/	case	0x78:
					hold = va_arg(arg_pointer, long int);
					if(hold==2147483648){
						fputc('-',stdout);
					}
					print_integer(hold,16,"0x");
					i++;
					break;
				/*$*/	case	0x24:
					hold2 = va_arg(arg_pointer, double);
					if(hold2<0){	
						fputc('-',stdout);
						hold2=-hold2;
					}
					fputc('$',stdout);
					hold2 = hold2 * 100;
					hold2 = (long int)hold2;
					divider = hold2/100;
					divider = divider*100;
					decimal = hold2-divider;
					digit_num = divider/100;
					print_integer(digit_num,10,"");
					fputc('.',stdout);
					if(decimal==0){
						fputc('0',stdout);
						fputc('0',stdout);
					}
					else{
						if(decimal<10){
							fputc('0',stdout);
							print_integer(decimal,10,"");					
						}
						else{
							print_integer(decimal,10,"");
						}
					}
					i++;
					break;
				/*%*/	case	0x25:
					fputc('%',stdout);
					i++;
					break;
				default:break;
			}
		}
		else{
			fputc(format[i],stdout);
		}
		i++;
	}
	va_end (arg_pointer);
}
void print_integer(int n, int radix, char* prefix){
	long int num = n;   // using long int incase the INT_MIN cause the data ovweflow    
	int counter = 0;    //counter used to count the iteration times.
	long int sign_convert = 0;  //holder for the number after its sign being convetered.
	long int value_n = 0;       //remain the original value wont be changed by operation.
	long int quotient = 0;
	long int remainder = 0;
	if(num==-2147483648){
		num=-num;
	}
	if ((num<0)){     //Convert negative number to positve number
		sign_convert = -num;
		num = sign_convert;
		fputc('-',stdout);  //print out the "-" sign
	}
	value_n = num;      //assign the value n to another variable preventing its value from changing
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
		while(*prefix!='\0'){           //print the prefix
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
