#include<stdio.h>
#include<stdlib.h>
typedef struct Nodedata {
	
} Nodedata;
typedef struct Treenode {
    int size, h, key;
    
    struct Treenode *p, *lch, *rch; 
} AVL_node;
typedef struct Tree {
    struct Treenode *root; 
} AVL_tree; 
#define ISLSON(X)   ((X)==(X)->p->lch) 
#define ISRSON(X)   ((X)==(X)->p->rch)

void AVL_init(AVL_tree *tree) { 
    tree =(AVL_tree *) malloc(sizeof(AVL_tree));
    tree->root = NULL;
} 
AVL_node *AVL_succnode(const AVL_node *node) {
    AVL_node *pi = node->rch;
    while(pi->lch != NULL) 
        pi = pi->lch;
    return pi; 
} 
AVL_node *AVL_prevnode(const AVL_node *node) {
    AVL_node *pi = node->lch;
    while(pi->rch != NULL) 
        pi = pi->rch;
    return pi; 
} 
int Height(AVL_node *t) {
    return t == NULL ? -1 : t->h; 
} 
int Size(AVL_node *t) {
    return t == NULL ? 0 : t->size; 
} 
int MaxOf(int x, int y) {
    return x > y ? x : y; 
} 
void AVL_LL_rotate(AVL_tree *tree,  AVL_node *node) {
    AVL_node *t = node->lch;
    
    node->lch = t->rch;
    node->rch = node;
    t->p = node->p;
    
    if(ISLSON(node))
    	node->p->lch = t;
    else node->p->rch = t;
	node->p = t; 
    t->h =  MaxOf(Height(t->rch), Height(t->lch))+1;
    node->h =  MaxOf(Height(node->rch), Height(node->lch))+1;
    t->size =  Size(t->lch) + Size(t->rch) +1;
    node->size =  Size(node->lch) + Size(node->rch) +1;
} 

void AVL_RR_rotate(AVL_tree *tree,  AVL_node *node) {
    AVL_node *t = node->rch;
    
    node->rch = t->lch;
    node->lch = node;
    t->p = node->p;
    
    if(ISLSON(node))
    	node->p->lch = t;
    else node->p->rch = t;
	node->p = t;  
    t->h =  MaxOf(Height(t->rch), Height(t->lch))+1;
    node->h =  MaxOf(Height(node->rch), Height(node->lch))+1;
    t->size =  Size(t->lch) + Size(t->rch) +1;
    node->size =  Size(node->lch) + Size(node->rch) +1;
}
void AVL_LR_rotate(AVL_tree *tree,  AVL_node *node) {
    AVL_RR_rotate (tree, node->lch), AVL_LL_rotate (tree, node); 
}
void AVL_RL_rotate(AVL_tree *tree,  AVL_node *node) {
    AVL_LL_rotate (tree, node->rch), AVL_RR_rotate (tree, node);
}
void AVL_balance(AVL_tree *tree, AVL_node *node, AVL_node *dest) {
	
    do {
		printf("1*\n");
    	if(Height(node->lch)-Height(node->rch) == 2) {
            if(Height(node->lch->lch) > Height(node->lch->rch))
                    AVL_LL_rotate(tree, node);
            else
                    AVL_LR_rotate(tree, node); 
			printf("2*\n");
        } 
        else if((Height(node->rch)-Height(node->lch) == 2)) {
            if(Height(node->rch->rch) > Height(node->rch->lch)) 
                    AVL_RR_rotate(tree, node);
            else
                    AVL_RL_rotate(tree, node);
            printf("3*\n");
        } 
        printf("4*\n");
        node->h =  MaxOf(Height(node->rch), Height(node->lch))+1;
        printf("5*\n");
        node->size =  Size(node->lch) + Size(node->rch) +1;
        printf("6*\n");
        if(node == dest) break;
        node = node->p; 
        printf("7*\n");
    } 
    while(1) ;
} 
void AVL_insert(AVL_tree *tree, const int key) {
    
    AVL_node *pi = tree->root, *pj = pi;
    int rank = 1;
    while(pi != NULL) {
        pj = pi;
        if(key > pi->key) 
            pi = pi->rch;
         else if(key < pi->key)
			pi = pi->lch, rank += pi->rch->size + 1;  
		else {break;}
		
    }
    printf("%d\n",rank);
    AVL_node *newnode = (AVL_node *)malloc(sizeof(AVL_node)); 
    newnode->p = pj; 
    newnode->h = 0; 
    newnode->lch = newnode->rch = NULL;
    newnode->key = key;
    newnode->size = 1; 
    
    if(pj == tree->root) 
        tree->root = newnode;
    else if(key > pj->key) 
        pj->rch = newnode;
    else
        pj->lch = newnode; 
	AVL_balance(tree, newnode, tree->root);
} 
void AVL_delete(AVL_tree *tree, const int key) {
    AVL_node *pi = tree->root, *pj = pi;
    
    while(pi != NULL) {
        pj = pi; 
        if(key > pi->key) 
            pi = pi->rch;
        else if(key < pi->key)
			pi = pi->lch;  
		else {pi = AVL_prevnode(pi);break;}
    }
	while(pi != NULL) {
		pj->key = pi->key, pj = pi;
		pi = AVL_prevnode(pi);
		if(pi == NULL)	{
			pi = AVL_succnode(pi);
			if(pi == NULL)	{
				pj->p->rch = NULL;
				AVL_balance(tree, pj->p, tree->root);
				free (pj);
			}
		}
	}
} 
void AVL_freetree(AVL_node *node) {
	if(node->lch != NULL) AVL_freetree(node->lch);
	if(node->rch != NULL) AVL_freetree(node->rch);
	free (node);
}
int Input() {  
    char cha;  
    int x=0;
    while(cha = getchar())
        if(cha!=' ' && cha != '\n') break;  
    x = cha-48;  
    while(cha = getchar()) {
        if(cha == ' ' || cha == '\n') break;  
        x = x*10+cha-48;  
    }
    return x;  
}
main()
{
    AVL_tree *tree = (AVL_tree *) malloc(sizeof(AVL_tree));
    tree->root = NULL;
    int N, M, a;
    while(scanf("%d",&N)==1) {
    	//AVL_init(tree);
    	//printf("%d\n", (tree)->root);
        for(a = 1 ; a <= N; a++) {
            M = Input();
            AVL_insert(tree, M);
        }
        AVL_freetree((tree)->root);
    } 
    return 0;
}
/*
in
6 
1
5
6
3
4
2
out
1
1
1
3
3
5

*/
