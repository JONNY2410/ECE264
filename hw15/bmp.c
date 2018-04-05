#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include"bmp.h"
char* _error_handle(char* message_error){
	char* error = malloc((strlen(message_error)+1)*sizeof(*message_error));
	strcpy(error,message_error);
	return error;
}

BMPImage* read_bmp(FILE* fp, char** error){		//read data is not success
	fseek(fp,0, SEEK_END);
	long int size_file = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	BMPImage *image = malloc(sizeof(*image));
	if(image==NULL){
		char* message_error = "malloc failure";
		*error = _error_handle(message_error);
		return NULL;
	}
	long int check1 = fread(&(image->header),BMP_HEADER_SIZE,1,fp);	
	if(check1!=1){
		char* message_error = "invalid fread";
		*error = _error_handle(message_error);
		free(image);
		return NULL;
	}

	if((check_bmp_header(&(image->header),fp) == false)){
		char* message_error = "invalid header";
		*error = _error_handle(message_error);
		free(image);
		return NULL;
	}	

	unsigned char* data = malloc(image->header.image_size_bytes);
	if(data==NULL){
		char* message_error = "malloc failure";
		*error = _error_handle(message_error);
		free(image);
		return NULL;
	}

	long int check2 = fread(data,sizeof(*data),size_file - BMP_HEADER_SIZE,fp);
	if(check2!=(size_file - BMP_HEADER_SIZE)){
		char* message_error = "fread failure";
		*error = _error_handle(message_error);
		free_bmp(image);
		return NULL;
	}
	image->data = data;
	return image;
}

bool check_bmp_header(BMPHeader* bmp_hdr, FILE* fp){
	fseek(fp,0,SEEK_END);
	long int size = ftell(fp); 
	fseek(fp,BMP_HEADER_SIZE,SEEK_SET);	 
	if(bmp_hdr->type != 0x4d42){
		return false;	 
	}		
	if(bmp_hdr->offset != BMP_HEADER_SIZE){
		return false;
	}
	if(bmp_hdr->dib_header_size != DIB_HEADER_SIZE){
		return false;
	}
	if(bmp_hdr->num_planes != 1){
		return false;
	}
	if(bmp_hdr->compression != 0){
		return false;
	}
	if((bmp_hdr->num_colors!=0)||(bmp_hdr->important_colors!=0)){
		return false;
	}
	if(bmp_hdr->bits_per_pixel!=24){
		return false;
	}
	if(bmp_hdr->size != size){		//size of file
		return false;
	}
	long int wid = (bmp_hdr->bits_per_pixel) * (bmp_hdr->width_px)/8;
	if((wid%4) != 0){
		wid = wid+(4-(wid%4));
	}
	if((wid*(bmp_hdr->height_px)!= bmp_hdr->image_size_bytes)||(size - BMP_HEADER_SIZE != bmp_hdr->image_size_bytes)){
		return false;
	}			
	return true;
}

void free_bmp(BMPImage* image){
	free(image->data);
	free(image);
}

bool write_bmp(FILE* fp, BMPImage* image, char** error){
	fseek(fp,0,SEEK_SET);
	long int check1 = fwrite(&(image->header),BMP_HEADER_SIZE,1,fp);	
	if(check1 != 1){
		return false;
	}
	long int check2 = fwrite((image->data),1,(image->header.size) - BMP_HEADER_SIZE,fp);	
	if(check2 != (image->header.size - BMP_HEADER_SIZE)){
		return false;
	}
	return true;
}

BMPImage* crop_bmp(BMPImage* image, int x, int y, int w, int h, char** error){
	long int width_in_byte = w*(image->header.bits_per_pixel)/8;
	int new_padding = 0;
	if(width_in_byte % 4 != 0){
		new_padding = 4 - (width_in_byte%4);
		width_in_byte = width_in_byte + new_padding;		//width in byte of the new bmp with padding
	}
	long int old_row_size = (image->header.width_px)*(image->header.bits_per_pixel)/8;		//width in byte of the original bmp with padding
	int padding = 4 - (old_row_size%4);	
	if((old_row_size%4)!=0){
		old_row_size = old_row_size + padding;
	}
	BMPImage* crop_image = malloc(sizeof(*crop_image));
	if(crop_image==NULL){
		char* message_error = "malloc failure";
		*error = _error_handle(message_error);
		return NULL;
	}
	crop_image->header = image->header;				//setting the new header information	
	crop_image->header.height_px = h;
	crop_image->header.width_px = w;
	crop_image->header.size = width_in_byte * h + BMP_HEADER_SIZE;	
	crop_image->header.image_size_bytes = width_in_byte * h;
	unsigned char* crop_data = malloc(width_in_byte*h);	//image data
	if(crop_data==NULL){
		char* message_error = "malloc failure";
		*error = _error_handle(message_error);
		return NULL;
	}
	long int index_new = 0;			//tracking the data inside of the crop_image->data
	long int index_old = 0;			//tracking the data inside of the image->data	
	for(int row = 0; row < (image->header.height_px);row++){
		if((row < (image->header.height_px - y))&&(row >= (image->header.height_px - y - h))){
			for(int col = 0; col < (image->header.width_px); col++){
				if((col >= x)&&(col <= x+w-1)){
					for(int i=0;i<(image->header.bits_per_pixel)/8;i++){
						crop_data[index_new] = image->data[index_old];
						index_old++;
						index_new++;
					}	
				}
				else{	
					for(int i=0;i<(image->header.bits_per_pixel)/8;i++){
						index_old++;
					}	
				}
			}
			if(padding!=4){
				for(int i=0;i<padding;i++){
					index_old++;
				}
			}
			for(int j=0; j<new_padding; j++){
				crop_data[index_new] = 0x00;
				index_new++; 
			}	
		}
		else{
			for(int i = 0; i<old_row_size;i++){
				index_old++;
			}
		}
	}
	crop_image->data = crop_data;	
	return crop_image;	
}
