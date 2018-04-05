/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

void print_node(Node *list, void (*print_fn)(Node*))
{	
	while (list != NULL) {
		// print the memory associated with list->ptr
		print_fn(list);
		// print an arrow
		fprintf(stdout,"->");
		list = list->next;
	} 
	// print NULL and a newline after that 
	fprintf(stdout, "NULL\n");
}
/*
static void print_fn(Node* list){
	printf("%c:%ld",list->t_node->ch,list->t_node->freq);
}
*/
void write_file(FILE* fp2, Node* head){
	while(head!=NULL){
		fprintf(fp2,"%c",head->t_node->ch);
		fprintf(fp2,"%c",':');
		fprintf(fp2,"%ld",head->t_node->freq);
		fprintf(fp2,"%s","->");	
		head = head->next;
	}	
	fprintf(fp2,"%s","NULL");
	fprintf(fp2,"\n");
}


void destroy_fn(TreeNode* node){
	free(node);
}


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
	FILE *fpw = fopen(argv[2],"w");
	if(fpw==NULL){
		return EXIT_FAILURE;
	}
	fseek(fpw,0,SEEK_SET);
	long int asciicount[256] = {0}; 
	asciicount_fn(asciicount,fp);
	for(int i = 0; i<256; i++){
		fprintf(fpw,"%ld\n",asciicount[i]);
	}
	//  Output file1 end

	Node* head =NULL;
	head = frequency_rank(asciicount);
	FILE* fp2 = fopen(argv[3],"w");
	write_file(fp2,head);		

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
	FILE* fpe = fopen(argv[4],"w");
	int index = -1;
	huffman_code(root,array,index,fpe);	 
	free(tree_head);
	free_tree(root);	
	fclose(fp2);	
	fclose(fp);
	fclose(fpw);
	fclose(fpe);
}

