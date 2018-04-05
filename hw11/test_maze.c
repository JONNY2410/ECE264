#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
int main(int argc, char* argv[]) 
{
	int s_row = 0;
	int s_col = 0;
	int d_row = 0;
	int d_col = 0;
	int dfs_return = 0;
	int smu_return = 0;
	char address = 0;
	char* check_valid = &address;		//check whether the strtol conert only valid symbol	
	Coord s_coord;
	Coord d_coord;
	if (argc < 2) 
	{
		return EXIT_FAILURE;
	}

	if (strcmp("-m", argv[1]) == 0) {
		if (argc != 8) { 
			return EXIT_FAILURE; 
		}
		s_row = strtol(argv[4],&check_valid,10);
		if(*check_valid != '\0'){
			return EXIT_FAILURE;
		}	
		s_col = strtol(argv[5],&check_valid,10);
		if(*check_valid != '\0'){
			return EXIT_FAILURE;
		}
		d_row = strtol(argv[6],&check_valid,10);
		if(*check_valid != '\0'){
			return EXIT_FAILURE;
		}
		d_col = strtol(argv[7],&check_valid,10);
		if(*check_valid != '\0'){
			return EXIT_FAILURE;
		}
		s_coord.row = s_row;
		s_coord.col = s_col;
		d_coord.row = d_row;
		d_coord.col = d_col;
		dfs_return =dfs_shortest_path_directions(argv[2],argv[3],s_coord,d_coord);
		printf("%d\n",dfs_return);	
	}
	else if(strcmp("-s",argv[1]) == 0) {
		if(argc != 9){
			return EXIT_FAILURE;
		}
		s_row = strtol(argv[5],&check_valid,10);
		if(*check_valid != '\0'){
			return EXIT_FAILURE;
		}	
		s_col = strtol(argv[6],&check_valid,10);
		if(*check_valid != '\0'){
			return EXIT_FAILURE;
		}
		d_row = strtol(argv[7],&check_valid,10);
		if(*check_valid != '\0'){
			return EXIT_FAILURE;
		}
		d_col = strtol(argv[8],&check_valid,10);
		if(*check_valid != '\0'){
			return EXIT_FAILURE;
		}
		s_coord.row = s_row;
		s_coord.col = s_col;
		d_coord.row = d_row;
		d_coord.col = d_col;
		smu_return = simulate_movement(argv[2],argv[3],argv[4],s_coord,d_coord);	
		printf("%d\n",smu_return);
	}

	return EXIT_SUCCESS;
}
