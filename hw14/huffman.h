#include<stdio.h>
#include<stdlib.h>
typedef struct _TreeNode {
	long int freq; // freq (weight) of char
	unsigned char ch; // character
	int mark;
	struct _TreeNode * left; // left
	struct _TreeNode * right; // right
} TreeNode;

typedef struct _Node {
	TreeNode* t_node;
	struct _Node *next;
} Node;

typedef struct _link{
	char bit;
	struct _link *next;
} link;

Node* tree_enqueue(Node**, Node*);
Node* build_tree(Node**);
Node *_pq_enqueue(Node **pq, int, long int freq_ct,int (*cmp_fn)(int,int));
void _destroy_fn(Node *list, void (*destroy_fn)(TreeNode *));
Node *_pq_dequeue(Node **pq);
long int* asciicount_fn(long int*, FILE*);
Node* frequency_rank(long int*);
void huffman_code(TreeNode*,char*, int,FILE*);
void post_traverse(TreeNode*,FILE*);
void bit_stream(FILE*,char*);
