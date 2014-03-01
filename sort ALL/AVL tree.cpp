#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define IsLc(X) ((X) == (X)->p->lc)
#define IsRc(X) ((X) == (X)->p->rc)
typedef struct AVLNode {
    int v;
    short h;
    struct AVLNode *p, *lc, *rc;
}AVLNode;
typedef struct AVLTree{
    struct AVLNode *NIL, *root;
}AVLTree;
short Max(short, short);
short Height(AVLTree*, AVLNode*);

AVLNode *AVLMax(AVLTree*, AVLNode*);
AVLNode *AVLMin(AVLTree*, AVLNode*);
AVLNode *AVLFind(AVLTree*, int);
AVLNode *AVLLL(AVLTree*, AVLNode*);
AVLNode *AVLRR(AVLTree*, AVLNode*);
AVLNode *AVLLR(AVLTree*, AVLNode*);
AVLNode *AVLRL(AVLTree*, AVLNode*);

void AVLinit(AVLTree*);
void AVLFree(AVLTree*, AVLNode*);
void AVLPrint(AVLTree*, AVLNode*);
void AVLBalance(AVLTree*, AVLNode*, AVLNode*);
void InsAVL(AVLTree*, int);
void DelAVL(AVLTree*, int);

short Max(short x, short y) {
    return x > y ? x : y;
}
short Height(AVLTree *tree, AVLNode *node) {
    if(node == tree->NIL)    return -1;
    return node->h;
}
void AVLinit(AVLTree *tree) {
    tree->NIL = (AVLNode*)malloc(sizeof(AVLNode));
    tree->root = tree->NIL->p = tree->NIL->lc = tree->NIL->rc = tree->NIL;
}
void AVLFree(AVLTree *tree, AVLNode *now) {
    if(now == tree->NIL)    return;
    if(now->lc != tree->NIL)    AVLFree(tree, now->lc);
    if(now->rc != tree->NIL)    AVLFree(tree, now->rc);
    free(now);
}
void AVLPrint(AVLTree *tree, AVLNode *now) {
    if(now == tree->NIL)    return;
    if(now->lc != tree->NIL)    AVLPrint(tree, now->lc);
    printf("%d -> ", now->v);
    if(now->rc != tree->NIL)    AVLPrint(tree, now->rc);
}
AVLNode *AVLMax(AVLTree *tree, AVLNode *node) {/*Max node*/
    if(node == tree->NIL || node->rc == tree->NIL)    return node;
    return AVLMax(tree, node->rc);
}
AVLNode *AVLMin(AVLTree *tree, AVLNode *node) {/*Min node*/
    if(node == tree->NIL || node->lc == tree->NIL)    return node;
    return AVLMin(tree, node->lc);
}
AVLNode *AVLLL(AVLTree *tree, AVLNode *node) {
    if(node == tree->NIL)    return tree->NIL;
    AVLNode *lc = node->lc;
    if(node->p != tree->NIL) {
        if(IsLc(node))    node->p->lc = lc;
        else    node->p->rc = lc;
    }
    node->lc = lc->rc;
    lc->rc = node;
    lc->p = node->p;
    node->p = lc;
    node->lc->p = node;
    node->h = Max(Height(tree, node->lc), Height(tree, node->rc))+1;
    lc->h = Max(Height(tree, lc->lc), Height(tree, lc->rc))+1;
  
    if(lc->p == tree->NIL)    tree->root = lc;
  
    return lc;
}
AVLNode *AVLRR(AVLTree *tree, AVLNode *node) {
    if(node == tree->NIL) return tree->NIL;
    AVLNode *rc = node->rc;
    if(node->p != tree->NIL) {
        if(IsRc(node))    node->p->rc = rc;
        else    node->p->lc = rc;
    }
    node->rc = rc->lc;
    rc->lc = node;
    rc->p = node->p;
    node->p = rc;
    node->rc->p = node;
    node->h = Max(Height(tree, node->lc), Height(tree, node->rc))+1;
    rc->h = Max(Height(tree, rc->lc), Height(tree, rc->rc))+1;
  
    if(rc->p == tree->NIL)    tree->root = rc;
  
    return rc;
}
AVLNode *AVLLR(AVLTree *tree, AVLNode *node) {
    node->lc = AVLRR(tree, node->lc);
    return AVLLL(tree, node);
}
AVLNode *AVLRL(AVLTree *tree, AVLNode *node) {
    node->rc = AVLLL(tree, node->rc);
    return AVLRR(tree, node);
}
void AVLBalance(AVLTree *tree, AVLNode *node, AVLNode *dest) {
    if(node == dest)    return;
    while(node != dest) {/*node == root*/
        if(Height(tree, node->lc) - Height(tree, node->rc) == 2) {
            if(Height(tree, node->lc->lc) >= Height(tree, node->lc->rc))
                node = AVLLL(tree, node);
            else    node = AVLLR(tree, node);
            node->h = Max(Height(tree, node->lc), Height(tree, node->rc))+1;
        }
        else if(Height(tree, node->rc) - Height(tree, node->lc) == 2) {
            if(Height(tree, node->rc->rc) >= Height(tree, node->rc->lc))
                node = AVLRR(tree, node);
            else node = AVLRL(tree, node);
            node->h = Max(Height(tree, node->lc), Height(tree, node->rc))+1;
        }
        else {
            node->h = Max(Height(tree, node->lc), Height(tree, node->rc))+1;
            node = node->p;
        }
    }
}
void InsAVL(AVLTree *tree, int key) {
    AVLNode *curr = tree->root, *prev = tree->NIL;
    while(curr != tree->NIL) {
        prev = curr;
        if(curr->v > key)    curr = curr->lc;
        else if(curr->v < key)    curr = curr->rc;
        else return;
    }
    curr = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    curr->v = key, curr->p = prev, curr->h = 0;
    curr->lc = curr->rc = tree->NIL;
  
    if(prev == tree->NIL)    tree->root = curr;
    else if(prev->v > key)    prev->lc = curr;
    else    prev->rc = curr;
    AVLBalance(tree, curr, tree->NIL);
}

void DelAVL(AVLTree *tree, int key) {
    AVLNode *node = AVLFind(tree, key);
    if(node == tree->NIL)    return;
    AVLNode *temp = AVLMin(tree, node->rc);
    if(temp == tree->NIL) {
        AVLNode *tmpp = node->p;
        if(node->p == tree->NIL) tree->root = node->lc;
        if(IsLc(node))    node->p->lc = node->lc;
        else    node->p->rc = node->lc;
        node->p->h = Max(Height(tree, node->p->lc), Height(tree, node->p->rc))+1;
        node->lc->p = node->p;
        AVLBalance(tree, tmpp, tree->NIL);
    }
    else {
        AVLNode *tmpp = temp->p;       
        if(node->p == tree->NIL) tree->root = temp;
        if(IsLc(node))    node->p->lc = temp;
        else    node->p->rc = temp;
        if(temp != node->rc) {
            temp->rc->p = temp->p;
            temp->p->lc = temp->rc;
            temp->rc = node->rc;
            node->rc->p = temp;
        }
        node->lc->p = temp;
        temp->lc = node->lc, temp->p = node->p;
        if(tmpp != node)    AVLBalance(tree, tmpp, tree->NIL);
    }
    free(node);
}
AVLNode *AVLFind(AVLTree *tree, int key) {
    AVLNode *curr = tree->root;
    while(curr != tree->NIL) {
        if(curr->v > key)    curr = curr->lc;
        else if(curr->v < key)    curr = curr->rc;
        else return curr;
    }
    return tree->NIL;
}
main() {
    int a, k, n, op, Mod;
	freopen("in1.txt", "rt", stdin);   
	freopen("out5.txt", "w+t", stdout);
    AVLTree Tree;
    AVLinit(&Tree);
    clock_t st, ed;
    st = clock();
    while(scanf("%d", &n) == 1)
		InsAVL(&Tree, n);	
	ed = clock();
	printf("%f\n", (float)(ed - st )/CLOCKS_PER_SEC);
    AVLFree(&Tree, Tree.root);

    return 0;
}
