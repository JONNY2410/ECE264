#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

Node *pq_enqueue(Node **pq, const void *new_object, int (*cmp_fn)(const void *, const void *))	
{	
	Node* new = malloc(sizeof(*new));	//allocate a new node for the new_object to insert
	if(new==NULL){				//failure allocate
		return NULL;
	}
	new->ptr = (void*)new_object;		
	new->next = NULL;
	if(new_object == NULL){			//new_object ==NULL, free the pre_allocate memory
		free (new);
		return NULL;
	}
	if(*pq == NULL){			//if its an empty list, the new node become the first node
		new->next = NULL;
		*pq = new;
		return *pq;
	}	
	if(cmp_fn((*pq)->ptr,new_object)>=0){
		new->next = *pq;
		*pq = new;	
		return *pq;
	}
	else{	
		Node* head = *pq;//keep head stay at the beginning of the linked_list
		Node* curr = *pq;
		while((curr->next!=NULL)&&(cmp_fn(curr->next->ptr,new_object)<0)){	//whether reach the end of the linked list or inserted in the middle
			curr=curr->next;
		}
		new->next = curr->next;
		curr->next = new;
		return head;
	}
	
}

Node *pq_dequeue(Node **pq)
{
	if(*pq == NULL){
		return NULL;
	}
	else if(((*pq)->next==NULL)){	//move the first node and assign NULL to pq.
		Node* curr  = *pq;
		*pq = NULL;
		return curr;

	}
	else{
		Node* curr = *pq;
		Node* consq = (*pq)->next;
		*pq = consq;
		curr->next = NULL;
		return curr;
	}
}


Node *stack_push(Node **stack, const void *new_object)
{
	if(new_object == NULL){
		return NULL;
	}	
	Node* new = malloc(sizeof(*new));
	if(new == NULL){
		return NULL;
	}
	new->ptr = (void *)new_object;
	new->next = *stack;
	*stack = new;		//set stack** point to the first node;
	return *stack;
}


Node *stack_pop(Node **stack)
{
	Node* head = pq_dequeue(stack);
	return head;
}


Node *remove_last_node(Node **list)	//this function is correct
{	
	Node *curr = *list;
	Node *consq = (*list)->next; 
	if(list==NULL){
		return NULL;
	}
	else{
		while(consq->next != NULL){
			curr = consq;
			consq = consq->next;	
		}
		curr->next=NULL;
		return consq;		
	}
}


void destroy_node(Node *list, void (*destroy_fn)(void *))
{
	do{
		Node* head = list->next;
		Node* trash = list;		//break the first node from the list
		list->next = NULL;		
		destroy_fn(trash->ptr);		
		free(list);			//free it
		list = head;
	}while(list!=NULL);
	return;
}

/* print an entire linked list                                           */
/* pq is the address of the first Node in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an Node in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */

void print_node(const Node *list, void (*print_fn)(const void *))
{	
	while (list != NULL) {
		// print the memory associated with list->ptr
		print_fn(list->ptr);
		// print an arrow
		fprintf(stdout, "->");
		list = list->next;
	} 
	// print NULL and a newline after that 
	fprintf(stdout, "NULL\n");
}

