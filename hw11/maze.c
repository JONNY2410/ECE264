#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "maze.h"
#include <stdbool.h>
Maze* _read_maze(FILE*);
bool _write_maze(const char*, const Maze*);
void _free_maze(Maze*);
Maze* _malloc_maze(int,int);
void print_maze(Maze*);
static int is_path(Maze *maze, int row, int col){
	if ((row >= 0) && (row < maze->n_row)) {
		if ((col >= 0) && (col < maze->n_col)) {
			return maze->maze_array[row][col] == PATH;
		}
	}
	return 0;
}
static int _pathfinder_helper(Maze *maze, int curr, int curc, int endr, int endc, int count, int* min){
	maze->maze_array[curr][curc] = VISITED;
	if ((curr == endr) && (curc == endc)) { // reach the destination 			
		if(count < *min){
			*min=count;
			maze->maze_array[curr][curc]=PATH;
			return count;
		}
	}
	int found;
	if (is_path(maze, curr-1, curc)) {
		found = _pathfinder_helper(maze, curr-1, curc, endr, endc, count+1, min);
		if ((found != -1)&&(((!(is_path(maze,curr+1,curc))&&(!(is_path(maze,curr,curc+1))&&(!(is_path(maze,curr,curc-1)))))))) {
			maze->maze_array[curr][curc]=PATH;
			return found;
		}	
	}
	if (is_path(maze, curr+1, curc)) {
		found = _pathfinder_helper(maze, curr+1, curc, endr, endc, count+1,min);
		if ((found != -1)&&(((!(is_path(maze,curr-1,curc))&&(!(is_path(maze,curr,curc+1))&&(!(is_path(maze,curr,curc-1)))))))) {
			maze->maze_array[curr][curc]=PATH;
			return found;
		}
	}
	if (is_path(maze, curr, curc+1)) {
		found = _pathfinder_helper(maze, curr, curc+1, endr, endc, count+1,min);
		if ((found != -1)&&(((!(is_path(maze,curr-1,curc))&&(!(is_path(maze,curr+1,curc))&&(!(is_path(maze,curr,curc-1)))))))){
			maze->maze_array[curr][curc]=PATH;
			return found;
		}
	}
	if (is_path(maze, curr, curc-1)) {
		found = _pathfinder_helper(maze, curr, curc-1, endr, endc, count+1,min);
		if ((found != -1)&&(((!(is_path(maze,curr+1,curc))&&(!(is_path(maze,curr-1,curc))&&(!(is_path(maze,curr,curc+1)))))))) {
			maze->maze_array[curr][curc]=PATH;
			return found;
		}
	}
	maze->maze_array[curr][curc]=PATH;
	return -1;

}
static int _direction_helper(Maze *maze, int curr, int curc, int endr, int endc,int count, FILE* dfptr, int* min, int* flag){
	maze->maze_array[curr][curc] = VISITED;
	if ((curr == endr) && (curc == endc)) { // reach the destination 
		if(count==*min){
			int i;
			for (i = 0; i < count; i++) { // create enough space in file
				fputc(VISITED, dfptr);
			}
			*flag=1;
		}
		maze->maze_array[curr][curc]=PATH;
		return count;
	}
	int found;
	if (is_path(maze, curr-1, curc)) {
		found = _direction_helper(maze, curr-1, curc, endr, endc, count+1, dfptr, min,flag);
		if ((found != -1)&&(*flag==1)) {
			fseek(dfptr, -1, SEEK_CUR); // go back one position
			fputc('N', dfptr);
			fseek(dfptr, -1, SEEK_CUR); // go back one position
			return found;
		}
	}
	if (is_path(maze, curr+1, curc)) {
		found = _direction_helper(maze, curr+1, curc, endr, endc, count+1, dfptr, min,flag);
		if ((found != -1)&&(*flag==1)) {
			fseek(dfptr, -1, SEEK_CUR); // go back one position
			fputc('S', dfptr);
			fseek(dfptr, -1, SEEK_CUR); // go back one position
			return found;
		}
	}
	if (is_path(maze, curr, curc+1)) {
		found = _direction_helper(maze, curr, curc+1, endr, endc, count+1, dfptr, min,flag);
		if ((found != -1)&&(*flag==1)) {
			fseek(dfptr, -1, SEEK_CUR); // go back one position
			fputc('E', dfptr);
			fseek(dfptr, -1, SEEK_CUR); // go back one position
			return found;
		}
	}
	if (is_path(maze, curr, curc-1)) {
		found = _direction_helper(maze, curr, curc-1, endr, endc, count+1, dfptr, min,flag);
		if ((found != -1)&&(*flag==1)) {
			fseek(dfptr, -1, SEEK_CUR); // go back one position
			fputc('W', dfptr);
			fseek(dfptr, -1, SEEK_CUR); // go back one position
			return found;
		}
	}
	maze->maze_array[curr][curc]=PATH;
	return -1;
}
Maze* _malloc_maze(int num_rows, int num_cols){
	Maze* maze_real = malloc(sizeof(*maze_real));
	if(maze_real == NULL){
		free(maze_real);
		return NULL;
	}
	maze_real->maze_array = malloc(sizeof(*(maze_real->maze_array))*num_rows);
	if(maze_real->maze_array == NULL){
		free(maze_real->maze_array);
		return NULL;
	}
	for(int i = 0; i < num_rows; i++){
		maze_real->maze_array[i] = malloc(sizeof(**(maze_real->maze_array))*num_cols);
		if(maze_real->maze_array[i] == NULL){
			for(int k = 0; k < i-1; k++){
				free(maze_real->maze_array[k]);
			}
			free(maze_real->maze_array);
			free(maze_real);
			return NULL;
		}
	}
	maze_real->n_row = num_rows;
	maze_real->n_col = num_cols;
	return maze_real;
}
Maze* _read_maze(FILE *fp){
	int row,col,flag,unknown=0;
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
	Maze* maze_loaded = _malloc_maze(row,col);             //reserve enough space to read the maze
	if(maze_loaded != NULL){			//if allocation fails, there is no point to load the file into the struct.
		fseek(fp,0,SEEK_SET);
		for(int j = 0; j < maze_loaded->n_row;j++){
			for(int k = 0; k < maze_loaded->n_col; k++){
				maze_loaded->maze_array[j][k] = fgetc(fp);
			}
			fgetc(fp);                     
		}
	}
	return maze_loaded;
}
bool _write_maze(const char* filename, const Maze* maze){
	int error_flag = 0;
	FILE* fp_new= fopen(filename,"w");
	fseek(fp_new,0,	SEEK_SET);
	for(int i = 0; i < maze -> n_row; i++ ){
		for(int j = 0; j< maze -> n_col; j++){
			error_flag = fputc(maze->maze_array[i][j],fp_new);
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
void _free_maze(Maze* maze){
	for(int i=0; i<maze->n_row;i++){
		free(maze->maze_array[i]);
	}
	free(maze->maze_array);
	free(maze);
}
int dfs_shortest_path_directions(char *maze_file, char *directions_file,Coord source, Coord destination){
	int count = 0;
	int addra = 0;
	int addrb = 0;
	int* min = &addra;
	*min = INT_MAX; 
	FILE* fp = fopen(maze_file,"r");		//open the original maze file
	int* flag = &addrb;
	*flag = 0;
	if(fp==NULL){					//check whether the file exists or not
		return -1;
	}
	Maze* maze_loaded = _read_maze(fp);			
	if(maze_loaded == NULL){			//check whether store maze into maze structure successful
		return -1;
	}
	if((destination.col>maze_loaded->n_col)||(destination.col<0)||(destination.row>maze_loaded->n_row)||(destination.row<0)||(source.col>maze_loaded->n_col)||(source.col<0)||(source.row > maze_loaded->n_row)||(source.row<0)||(maze_loaded->maze_array[source.row][source.col]!= PATH)||(maze_loaded->maze_array[destination.row][destination.col] != PATH)){
		return -1;				//check whether the source and destination are valid or not.	
	}
	//if any of above cause the error, the direction_files will not be created.
	FILE* dfptr = fopen(directions_file,"w");
	if(dfptr == NULL){
		return -1;				//check whether open direction file successfu
	}
	_pathfinder_helper(maze_loaded,source.row,source.col,destination.row,destination.col,count,min);
	_direction_helper(maze_loaded,source.row,source.col,destination.row,destination.col,count,dfptr,min,flag);
	_free_maze(maze_loaded);	
	fclose(fp);	
	fclose(dfptr);
	return *min;
}
int simulate_movement(char *maze_file, char *directions_file, char *visited_file, Coord source, Coord destination)
{
	int row = source.row;
	int col = source.col;
	bool check = 0;
	FILE* fp = fopen(maze_file,"r");
	if(fp == NULL){
		return -1;		
	}
	Maze* maze_loaded = _read_maze(fp);
	if(maze_loaded == NULL){
		return -1;
	}
	FILE* fpd = fopen(directions_file,"r");
	if(fpd == NULL){
		return -1;
	}
	fseek(fpd,0,SEEK_END);
	int size = ftell(fpd);
	size = size + 1;	//the size of the location files only indicates the steps going to move. need to add the source location.
	fseek(fpd,0,SEEK_SET);
	if((destination.col>maze_loaded->n_col)||(destination.col<0)||(destination.row>maze_loaded->n_row)||(destination.row<0)||(source.col>maze_loaded->n_col)||(source.col<0)||(source.row > maze_loaded->n_row)||(source.row<0)||(maze_loaded->maze_array[source.row][source.col]!= PATH)||(maze_loaded->maze_array[destination.row][destination.col] != PATH)){
		return -1;				//check whether the source and destination are valid or not.	
	}
	maze_loaded->maze_array[row][col]=VISITED;		//initial position is visited no matter what
	char direction = fgetc(fpd);
	while(direction!=EOF){
		if(direction=='N'){
			if(maze_loaded->maze_array[row-1][col]==PATH){
				maze_loaded->maze_array[row-1][col]=VISITED;
				row = row - 1;
			}
			else{
				return -1;
			}
		}
		if(direction=='S'){
			if(maze_loaded->maze_array[row+1][col]==PATH){
				maze_loaded->maze_array[row+1][col]=VISITED;
				row = row + 1;
			}
			else{
				return -1;
			}
		}
		if(direction=='E'){
			if(maze_loaded->maze_array[row][col+1]==PATH){
				maze_loaded->maze_array[row][col+1]=VISITED;
				col = col + 1;
			}
			else{
				return -1;
			}
		}
		if(direction=='W'){
			if(maze_loaded->maze_array[row][col-1]==PATH){
				maze_loaded->maze_array[row][col-1]=VISITED;
				col = col - 1;
			}
			else{
				return -1;
			}
		}
		if((direction!='W')&&(direction!='N')&&(direction!='E')&&(direction!='S')&&(direction!=EOF)){
			return -1;
		}
		direction = fgetc(fpd);
	}
	FILE* fpw = fopen(visited_file,"w");
	if(fpw==NULL){
		return -1;
	}
	check = _write_maze(visited_file, maze_loaded);
	if(check==false){
		return -1;
	}	
	_free_maze(maze_loaded);	
	fclose(fp);
	fclose(fpd);
	fclose(fpw);
	if((row==destination.row)&&(col==destination.col)){
		return size;	
	}
	else{
		return -1;
	}
}
