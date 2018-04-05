#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void find_maze_dimensions(FILE * fp, int * num_rows, int * num_cols){
	*num_rows = *num_cols = 0;
	int unknown = 0;			//the value that is going to be output in the maze
	int row = 0;				//number of rols
	int col = 0;				//num of cols
	int flag = 0;				//flag for jump out of loop
	fseek(fp,0,SEEK_SET);			//set the pointer to the beginning of the file
	do{
		unknown = fgetc(fp);
		while(unknown != '\n'){
			if(flag ==0){
				col++;
			}
			unknown = fgetc(fp);
		}
		flag = 1;
		row++;
	}while(fgetc(fp)!= EOF);
	*num_rows = row;	
	*num_cols = col;
}

int find_opening_location(FILE * fp) {
	fseek(fp,0,SEEK_SET);
	int unknown = 0;			//the value in the maze
	int location = 0;			//the locatio of the opening
	unknown = fgetc(fp);
	while(unknown!=PATH){
		location++;
		unknown = fgetc(fp);
	}	
	return location;
}

int count_path_locations(FILE * fp) {
	fseek(fp,0,SEEK_SET);
	int path = 0;
	int unknown = 0;
	unknown = fgetc(fp);	
	while(unknown!= EOF){
		if(unknown == PATH){
			path++;	
		}
		unknown = fgetc(fp);
	}
	return path;
}

char get_location_type(FILE * fp, int row, int col) {
	char unknown = 0;			//the type at specific location
	char looper = 0;			//track each character
	int row_count=0;			//track the current rols and colums in the file
	int col_count=0;			//track the current role and columns in the file
	fseek(fp,0,SEEK_SET);
	if((row_count == row)&&(col_count==col)){
		unknown = fgetc(fp);
	}
	else{
		while(row_count!=row){
			looper = fgetc(fp);
			while(looper!='\n'){
				looper = fgetc(fp);
			}
			row_count++;
		}
		looper = fgetc(fp);	
		while(col_count!=col){
			looper = fgetc(fp);
			col_count++;
		}
		unknown = looper;
	}
	if(unknown==PATH){
		return PATH;
	}
	else{
		return WALL;
	} 
}

int represent_maze_in_one_line(char * filename, FILE * fp) {
	FILE *fp_new;
	char unknown = 0;
	int num = 0;	
	int error_flag= 0;				//file write error check 
	fp_new = fopen(filename,"w");		//write into the file pointed by the address filename	
	if(fp_new == NULL){
		return MAZE_WRITE_FAILURE;
	}	
	fseek(fp_new,0,SEEK_SET);		//set file pointer to the beginning of the output file
	fseek(fp,0,SEEK_SET);			//set file pointer to the beginning of the file
	unknown = fgetc(fp);
	while(unknown != EOF){			
		if(unknown!='\n'){
			error_flag = fputc(unknown,fp_new);
			if(error_flag == EOF){
				return MAZE_WRITE_FAILURE;
			}
			unknown = fgetc(fp);
			num++; 
		}
		else{
			unknown = fgetc(fp);
		}
	}
	fclose(fp_new);	
	return num;
}
