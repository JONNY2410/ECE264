#include<stdlib.h>
#include"maze.h"
#include<stdio.h>
int main(int argc, char* argv[]){
	int addra=0;
	int addrb=0;
	int* a_num_rows;
	int* a_num_cols;
	int location=0;
	int pathcount=0;
	char type=0;
	int row = 1;
	int col = 4;
	char* newmaze=argv[2];
	a_num_rows = &addra;
	a_num_cols = &addrb;
	FILE * fp;
	fp = fopen(argv[1],"r");
	find_maze_dimensions(fp,a_num_rows,a_num_cols);
	location=find_opening_location(fp);
	pathcount = count_path_locations(fp);
	type = get_location_type(fp,row,col);
	represent_maze_in_one_line(newmaze,fp);
	printf("Dimension of Maze is %d x %d.\n",*a_num_rows,*a_num_cols);
	printf("location:	     %d.\n",location);
	printf("path_count:	     %d.\n",pathcount);
	printf("location type:	     %c.\n",type);
	fclose(fp);
	return 0 ;
}	
