/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

void free_tree(TreeNode* node){
	if((node->right!=NULL)){
		free_tree(node->right);
	}
	if(node->left!=NULL){
		free_tree(node->left);
	}
	free(node);
}

int main(int argc, char* argv[]) 
{
	if(argc!=5){
		return EXIT_FAILURE;
	}

	//Output file1 start
	FILE *fp = fopen(argv[1],"r");
	fseek(fp,0,SEEK_SET);
	if(fp==NULL){
		return EXIT_FAILURE;
	}
	long int asciicount[256] = {0}; 
	asciicount_fn(asciicount,fp);
	Node* head =NULL;
	head = frequency_rank(asciicount);
	//	print_node(head,print_fn);// debugging purpose
	Node* tree_head = NULL;
	tree_head = build_tree(&head);
	TreeNode* root = tree_head->t_node;
	int count = 0;
	while(root->right!= NULL){
		count++;
		root = root->right;
	}
	root = tree_head->t_node;
	char adda;
	char* array = &adda;
	for(int i = 0;i<count;i++){
		array[i] = '\0';
	}
	FILE* fpe = fopen(argv[2],"w");
	int index = 0;
	huffman_code(root,array,index,fpe);	
	//output_file_1 end

	//output_file_2 start
	root = tree_head->t_node;
	FILE* fpc = fopen(argv[3],"w");
	post_traverse(root,fpc);
	fputc('0',fpc);
	fclose(fpc);
	//output_file_2 end;

	//Output file 3 start
	FILE* fpch = fopen(argv[3],"r");
	char address;
	char* header = &address;
	fseek(fpch,0,SEEK_END);
	long int size = ftell(fpch);
	fseek(fpch,0,SEEK_SET);
	for(int i=0;i<size;i++){	
		header[i] = fgetc(fpch);
	}	
	fclose(fpch);
	FILE* tmp = fopen(argv[4],"w");
	bit_stream(tmp,header);
	fclose(tmp);
	free(tree_head);
	free_tree(root);	
	fclose(fp);
	fclose(fpe);
}
