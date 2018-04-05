#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"maze.h"
Maze* malloc_maze(int num_rows, int num_cols){
	Maze* maze_real = malloc(sizeof(*maze_real));
	if(maze_real == NULL){
		return NULL;
	}
	maze_real->cells = malloc(sizeof(*(maze_real->cells))*num_rows);
	if(maze_real->cells == NULL){
		return NULL;
	}
	for(int i = 0; i < num_rows; i++){
		maze_real->cells[i] = malloc(sizeof(**(maze_real->cells))*num_cols);
		if(maze_real->cells[i] == NULL){
			for(int k = 0; k < i-1; k++){
				free(maze_real->cells[k]);
			}
			free(maze_real->cells);
			free(maze_real);
			return NULL;
		}
	}
	maze_real->num_rows = num_rows;
	maze_real->num_cols = num_cols;
	return maze_real;
}

void free_maze(Maze* maze){
	for(int i=0; i<maze->num_rows;i++){
		free(maze->cells[i]);
	}
	free(maze->cells);
	free(maze);
}

Maze* read_maze(FILE *fp){
	int row = 0,col=0,flag=0,unknown=0;
	fseek(fp,0,SEEK_SET);
	do{
		unknown = fgetc(fp);
		while(unknown != '\n'){
			if(flag==0){
				col++;
			}
			unknown = fgetc(fp);
		}
		flag = 1;
		row++;
	}while(fgetc(fp)!= EOF);
	Maze* maze_loaded = malloc_maze(row,col);		//reserve enough space to read the maze

	fseek(fp,0,SEEK_SET);
	for(int j = 0; j < maze_loaded->num_rows;j++){
		for(int k = 0; k < maze_loaded->num_cols; k++){
			maze_loaded->cells[j][k] = fgetc(fp);
		}
		fgetc(fp);			//there might be problem here
	}
	return maze_loaded;	
}

bool write_maze(const char* filename, const Maze* maze){
	FILE* fp_new;
	int error_flag = 0;
	fp_new= fopen(filename,"w");
	fseek(fp_new,0,	SEEK_SET);
	for(int i = 0; i < maze -> num_rows; i++ ){
		for(int j = 0; j< maze -> num_cols; j++){
			error_flag = fputc(maze->cells[i][j],fp_new);
			if(error_flag == EOF){
				return false;
			} 
		}
		error_flag = fputc('\n',fp_new);
		if(error_flag == EOF){
			return false;
		}
	}
	fclose(fp_new);
	return true;
}

Maze* make_taller(const Maze* orig){
	int rows = (orig->num_rows)*2-1;
	int cols = orig->num_cols;
	Maze* taller_maze = malloc_maze(rows,cols);
	taller_maze->num_rows = rows;
	taller_maze->num_cols = cols;
	for(int i=0; i<rows;i++){
		if(i < orig->num_rows){
			for(int j=0;j<orig->num_cols;j++){
				taller_maze->cells[i][j]=orig->cells[i][j];	
			}
		}
		if(i >= orig->num_rows){
			for(int j=0; j<orig->num_cols; j++){
				taller_maze->cells[i][j]=orig->cells[rows-1-i][j];
			}
		}
	}
	return taller_maze;
}

Maze* make_wider(const Maze* orig){
	int rows = orig->num_rows;
	int cols = orig->num_cols*2-1;
	int center_row = (rows-1)/2;
	int center_col = (orig->num_cols)-1;
	int counter = 0;
	Maze* wider_maze = malloc_maze(rows,cols);
	wider_maze->num_rows = rows;
	wider_maze->num_cols = cols;
	for(int i=0; i< orig->num_rows;i++){
		for(int j = 0; j < cols; j++){
			if(j<orig->num_cols){
				wider_maze->cells[i][j] = orig->cells[i][j];
			}	
			if(j>=orig->num_cols){
				wider_maze->cells[i][j] = orig->cells[i][cols-1-j];
			}	
		}
	}
	while((wider_maze->cells[center_row+1][center_col-counter]!=PATH)&&(wider_maze->cells[center_row-1][center_col-counter] != PATH)&&(wider_maze->cells[center_row][center_col-(counter+1)]!=PATH)){
		wider_maze->cells[center_row][center_col-counter]=PATH;
		wider_maze->cells[center_row][center_col+counter]=PATH;
		counter++;
	}
	wider_maze->cells[center_row][center_col-counter]=PATH;
	wider_maze->cells[center_row][center_col+counter]=PATH;
	return wider_maze;
}
