#include "huffman.h"
#include<stdio.h>
#include<stdlib.h>

int cmp_int(int value1, int value2){	
	return value1-value2;	
}

long int* asciicount_fn(long int* asciicount, FILE* fp){
	unsigned char ch = 0;
	do{	
		ch = fgetc(fp);
		if(feof(fp)){
			break;
		}
		asciicount[ch]++;
	}while(ch!=EOF);
	return asciicount;
}

Node* frequency_rank(long int* asciicount){
	Node* head = NULL ;
	for(int i=0;i<256;i++){
		if(asciicount[i]!=0){
			head = _pq_enqueue(&head,i,asciicount[i],cmp_int);
		}	
	}
	return head;	
}

Node *_pq_enqueue(Node **pq, int character, long int freq_ct, int (*cmp_fn)(int, int))	
{	
	Node* new = malloc(sizeof(*new));
	if(new == NULL){
		return NULL;
	}
	TreeNode* new_tn = malloc(sizeof(*new_tn));	//allocate a new node for the new_object to insert
	if(new_tn==NULL){				//failure allocate
		return NULL;
	}
	new_tn->ch =(unsigned char)character;
	new_tn->freq = freq_ct;		
	new_tn->left = NULL;
	new_tn->right = NULL;
	new->t_node = new_tn;

	if((*pq) == NULL){			//if its an empty list, the new node become the first node
		new->next = NULL;
		*pq = new;
		return *pq;
	}	
	if(cmp_fn((*pq)->t_node->freq,freq_ct)>0){
		new->next = *pq;
		*pq = new;	
		return *pq;
	}

	else{	
		Node* head = *pq;//keep head stay at the beginning of the linked_list
		Node* curr = *pq;

		while(((curr->next!=NULL)&&(cmp_fn(curr->next->t_node->freq,freq_ct)<0))){	//whether reach the end of the linked list or inserted in the middle
			curr=curr->next;
		}

		if((curr->next!=NULL)&&(cmp_fn(curr->next->t_node->freq,freq_ct)==0)){
			if(curr->next->next != NULL){
				while(curr->next->t_node->freq==curr->next->next->t_node->freq){
					curr=curr->next;
					if(curr->next->next==NULL){
						break;
					}
				}
			}
			if(cmp_fn((int)(curr->next->t_node->ch),character)<0){

				new->next = curr->next->next;
				curr->next->next = new;
				return head;
			}
		}
		new->next = curr->next;
		curr->next = new;
		return head;
	}

}

void _destroy_fn(Node *list, void (*destroy_fn)(TreeNode*))
{
	do{
		Node* head = list->next;
		Node* trash = list;		//break the first node from the list
		list->next = NULL;		
		destroy_fn(trash->t_node);		
		free(list);			//free it
		list = head;
	}while(list!=NULL);
	return;
}


Node *_pq_dequeue(Node **pq)
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

Node* build_tree(Node **pq)
{
  
  while((*pq)->next!=NULL){
    
		Node* junc_n = malloc(sizeof(*junc_n));
		if(junc_n==NULL){
			return NULL;
		} 
		TreeNode* junc_tn = malloc(sizeof(*junc_tn));
		if(junc_tn == NULL){
			return NULL;
		}
		Node* child_a = _pq_dequeue(pq);
		Node* child_b = _pq_dequeue(pq);
		junc_tn->freq = child_a->t_node->freq + child_b->t_node->freq; 
		junc_tn->left = child_a->t_node;
		junc_tn->right = child_b->t_node;
		free(child_a);
		free(child_b);
		junc_n->t_node = junc_tn;
		 tree_enqueue(pq,junc_n);	
	}
	return *pq;
}

Node* tree_enqueue(Node** pq, Node* branch){
	if((*pq) == NULL){			//if its an empty list, the new node become the first node
		branch->next = NULL;
		*pq = branch;
		return *pq;
	}
	if(((*pq)->t_node->freq)>(branch->t_node->freq)){
		branch->next = *pq;	
		*pq = branch;
		return *pq;		
	}
	else{
		Node* head = *pq;//keep head stay at the beginning of the linked_list
		Node* curr = *pq;
		while((curr->next!=NULL)&&(curr->next->t_node->freq <= branch->t_node->freq)){	//whether reach the end of the linked list or inserted in the middle
			curr=curr->next;
		}
		branch->next = curr->next;
		curr->next = branch;
		return head;
	}		
}

void huffman_code(TreeNode* root, char* array, int index, FILE* fpe){
	index++;
	if((root->left==NULL)&&(root->right==NULL)){
		array[index] = root->ch;	
		fprintf(fpe,"%c%c",array[index],':');
		for(int i = 0;i<=index-1;i++){
			fprintf(fpe,"%c",array[i]);
		}
		fprintf(fpe,"\n");
	}
	else{
		array[index] = '0';
		huffman_code(root->left,array,index,fpe);	
		array[index] = '1';
		huffman_code(root->right,array,index,fpe);
	}
}

