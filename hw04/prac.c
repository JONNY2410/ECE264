#include <stdlib.h>

typedef struct{
	int ale;
	int amp;
}Ant;

typedef struct{
	double bag;
	char bib;
	char* bug;
}Bat;

int main(int argc, char** argv){
	Ant ari={
		.ale = 9,
		.amp = 7	
	};
	Ant* a_ari = &ari;
	a_ari = a_ari;
	Bat bev ={
		.bag = 3.7,
		.bib = 'q',
		.bug = "bro"
	};
	Bat* a_bev = &bev;
	a_bev = a_bev;
	int ira[3]={3,4};
	ira[3] = ira[3];
	return EXIT_SUCCESS;	
}



