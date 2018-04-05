#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"bmp.h"

int main(){
	char* error = NULL;
	FILE* fp = fopen("airplane.bmp","r");
	FILE* fp_w = fopen("To_be_write","w");	
	FILE* crop = fopen("crop_bmp.bmp","w");
	BMPImage* image = NULL;
	BMPImage* crop_image = NULL;
	image = read_bmp(fp,&error);
	if(image==NULL){
		if(error!=NULL){
			printf("%s",error);
			free(error);
			fclose(fp);
			fclose(fp_w);
			return 0;
		}
	}
	write_bmp(fp_w,image,&error);
	if(error!=NULL){
		printf("%s",error);
		free_bmp(image);
		free(error);
		fclose(fp);
		fclose(fp_w);
		return 0;
	}
	crop_image = crop_bmp(image,300,200,200,200,&error);
	if(crop_image!=NULL){
		write_bmp(crop,crop_image,&error);
		free_bmp(crop_image);
	}
	else{
		printf("%s",error);
		free_bmp(image);
		free(error);
		fclose(fp);
		fclose(fp_w);
		fclose(crop);
		return 0;
	}
	free_bmp(image);
	fclose(crop);
	fclose(fp);
	fclose(fp_w);
	printf("Image crop success");
	return 0;
}
