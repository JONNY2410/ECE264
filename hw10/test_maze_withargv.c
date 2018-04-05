#include<stdlib.h>
#include<stdio.h>
#include "maze.h"
void _print_Maze(Maze*);		//since the actual output of the taller and wider maze are redirect into a new file. This function is implemented to print out the readed maze, taller_maze and wider_maze directly when test_maze being called.

int main(int argc, char** argv){
	FILE* fp;
	fp = fopen(argv[1],"r");
	Maze* maze=read_maze(fp);
	write_maze("original_maze",maze);
	Maze* taller_maze = make_taller(maze);
	write_maze("taller_maze",taller_maze);
	Maze* wider_maze = make_wider(maze);
	write_maze("wider_maze",wider_maze);

	_print_Maze(maze);
	fputc('\n',stdout);
	_print_Maze(taller_maze);
	fputc('\n',stdout);
	_print_Maze(wider_maze);
	fputc('\n',stdout);
	free_maze(maze);
	free_maze(taller_maze);
	free_maze(wider_maze);
	fclose(fp);
	return 0;
}

void _print_Maze(Maze* maze_print){
	for(int i = 0; i < maze_print -> num_rows; i++ ){
		for(int j = 0; j< maze_print -> num_cols; j++){
			fputc(maze_print->cells[i][j],stdout);
		}
	fputc('\n',stdout); 
	}
	return;
}

