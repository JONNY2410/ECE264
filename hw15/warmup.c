#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct {
	int x;
	int y;
}Point;

char* _error_handle(char* message_error){
	char* error = malloc((strlen(message_error)+1)*sizeof(*message_error));
	strcpy(error,message_error);
	return error;
}

char* read_file(const char* path, char** error){
	FILE* fp = fopen(path, "r");
	fseek(fp,0,SEEK_END);
	long int size = ftell(fp);
	char* heap_content = malloc((size+1)*sizeof(*heap_content));
	if(heap_content==NULL){
		char* message = "malloc error";
		*error = _error_handle(message);
		fclose(fp);
		return NULL;
	}

	fseek(fp,0,SEEK_SET);
	int num_return = fread(heap_content,size,1,fp);
	heap_content[size] = '\0';	
	if((num_return!=1)&&(!feof(fp))){
		char* message = "fread error";
		*error = _error_handle(message);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return heap_content;
}

void write_file(const char* path, const char* contents, char** error){
	FILE* fp = fopen(path,"w");
	fseek(fp,0, SEEK_SET);
	int length = strlen(contents);
	int leng = fwrite(contents,length,1,fp);
	if(leng!=1){
		char* message = "fwrite error";
		*error = _error_handle(message);
		fclose(fp);
	}
	fclose(fp);
}

void write_point(char* path, Point p, char** error){
	FILE* fp = fopen(path,"w");
	fseek(fp,0,SEEK_SET);
	int leng1 = fwrite(&(p.x),sizeof(p.x),1,fp);
	if((leng1!=1)&&(!feof(fp))){
		char* message = "fwrite error";
		*error = _error_handle(message);
		fclose(fp);
		printf("%s",*error);
	}
	else{
		int leng2 = fwrite(&(p.y),sizeof(p.y),1,fp);
		if((leng2!=1)&&(!feof(fp))){
			char* message = "fwrite error";
			*error = _error_handle(message);
			fclose(fp);
			printf("%s",*error);
		}
	}
	fclose(fp);
}

Point read_point(const char* path,char** error){
	FILE* fp = fopen(path,"r");
	fseek(fp,0,SEEK_SET);
	Point p;
	int leng1 = fread(&(p.x),sizeof(p.x),1,fp);
	if(leng1!=1){
		char* message = "fread error";
		*error = _error_handle(message);
		fclose(fp);
		printf("%s",*error);
		return p;
	}
	else{
		int leng2 = fread(&(p.y),sizeof(p.y),1,fp);
		if(leng2!=1){
			char* message = "fread error";
			*error = _error_handle(message);
			fclose(fp);
			printf("%s",*error);
			return p;	
		}
	}
	fclose(fp);
	return p;
}

int main(int argc, char* argv[]){
	const char* path = "test.txt";
	const char* file = "new_file";
	char* file2 = "new_file2";
	char* error = NULL;
	Point p;
	p.x = 1;
	p.y = 2; 	
	const char* content = "this is the new content";
	char* output = read_file(path, &error);
	if(error!=NULL){
		printf("%s",error);
		free(error);
		return EXIT_FAILURE;
	}

	write_file(file, content, &error);
	if(error!=NULL){
		printf("%s",error);
		free(error);
		return EXIT_FAILURE;
	}
	write_point(file2,p,&error);
	if(error!=NULL){
		printf("%s",error);
		free(error);
		return EXIT_FAILURE;
	}
	read_point(path,&error);
	if(error!=NULL){
		printf("%s",error);
		free(error);
		return EXIT_FAILURE;
	}
	free(output);
	return EXIT_SUCCESS;
}
