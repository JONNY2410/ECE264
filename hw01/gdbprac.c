#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int beetle = 0x20;
	int iguana = 32;
	int sum;
	char* s= malloc(sizeof(char)*2);
	s= malloc(sizeof(char)*4);
	char* t = malloc(sizeof(char)*8);
	s[2]=4;
	t[8]=s[2];
	free(s);
	free(t);	
	sum = beetle+iguana;
	
	return sum;
	}
