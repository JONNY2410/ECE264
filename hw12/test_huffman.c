#include<stdio.h>
#include<stdlib.h>
#include"huffman.h"

int cmp_int(const void* value1, const void* value2){
	char a = *(const int *)(value1);
	char b = *(const int *)(value2);	
	return a-b;	
}

static void print_fn(const void* ptr){
	printf("%d",*(const int*)ptr);
}

void destroy_fn(void* point){
	return;
}

int main(int argc, char* argv[]){
	int array[] = {4,2,1,0,3,0,10,15,14};
	Node * pq = NULL;
	Node * head = pq; 
	for(int i=0; i<9; i++){
		pq_enqueue(&head, &array[i], cmp_int);
	}
	
	printf("en_queue list: ");
	print_node(head,print_fn);

	printf("stack pop: ");
	Node* s_node = stack_pop(&head);
	print_node(s_node,print_fn);
	destroy_node(s_node, destroy_fn);	

	printf("dequeue: ");
	Node* d_node = pq_dequeue(&head);
	print_node(d_node,print_fn);
	destroy_node(d_node,destroy_fn);	

	Node* l_node = remove_last_node(&head);
	printf("remove last node: ");
	print_node(l_node,print_fn);
	destroy_node(l_node,destroy_fn);

	printf("stack push: ");
	stack_push(&head,&array[8]);
	print_node(head,print_fn);	
	
	destroy_node(head,destroy_fn);	
	return EXIT_SUCCESS;
}
