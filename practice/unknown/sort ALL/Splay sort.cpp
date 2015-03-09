#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define IsLc(X) ((X) == (X)->p->lc)
#define IsRc(X) ((X) == (X)->p->rc)
typedef struct SpNode {
    int v;
    struct SpNode *p, *lc, *rc;
}SpNode;
typedef struct SpTree{
    struct SpNode *NIL, *root;
}SpTree;

SpNode *SpMax(SpTree*, SpNode*);
SpNode *SpMin(SpTree*, SpNode*);
SpNode *SpFind(SpTree*, int);

void Spinit(SpTree*);
void SpFree(SpTree*, SpNode*);
void SpPrint(SpTree*, SpNode*);
void SpZig(SpTree*, SpNode*);
void SpZag(SpTree*, SpNode*);
void SpSplay(SpTree*, SpNode*, SpNode*);
void InsSp(SpTree*, int);
void DelSp(SpTree*, int);

void Spinit(SpTree *tree) {
    tree->NIL = (SpNode*)malloc(sizeof(SpNode));
    tree->root = tree->NIL->p = tree->NIL;
}
void SpFree(SpTree *tree, SpNode *now) {
    if(now == tree->NIL)    return;
    if(now->lc != tree->NIL)    SpFree(tree, now->lc);
    if(now->rc != tree->NIL)    SpFree(tree, now->rc);
    free(now);
}
void SpPrint(SpTree *tree, SpNode *now) {
    if(now == tree->NIL)    return;
    if(now->lc != tree->NIL)    SpPrint(tree, now->lc);
    printf("%d -> ", now->v);
    if(now->rc != tree->NIL)    SpPrint(tree, now->rc);
}
SpNode *SpMax(SpTree *tree, SpNode *node) {/*Max node*/
    if(node == tree->NIL || node->rc == tree->NIL)    return node;
    return SpMax(tree, node->rc);
}
SpNode *SpMin(SpTree *tree, SpNode *node) {/*Min node*/
    if(node == tree->NIL || node->lc == tree->NIL)    return node;
    return SpMin(tree, node->lc);
}
void SpZig(SpTree *tree, SpNode *node) {
    /*<right-rotate>*/
    SpNode *lc = node->lc;
    lc->p = node->p;
    if(node == tree->root)    tree->root = lc;
    else if(IsLc(node))        node->p->lc = lc;
    else    node->p->rc = lc;
    
    node->p = lc;
    node->lc = lc->rc;
    lc->rc->p = node;
    lc->rc = node;
}
void SpZag(SpTree *tree, SpNode *node) {
    /*<left-rotate>*/
    SpNode *rc = node->rc;
    rc->p = node->p;
    if(node == tree->root)    tree->root = rc;
    else if(IsLc(node))        node->p->lc = rc;
    else    node->p->rc = rc;
    
    node->p = rc;
    node->rc = rc->lc;
    rc->lc->p = node;
    rc->lc = node;
}
void SpSplay(SpTree *tree, SpNode *node, SpNode *dest) {
    if(node == dest)    return;
    while(node->p != dest) {
        if(node->p->p == dest) {
            if(IsLc(node))/*Zig*/
                SpZig(tree, node->p);
            else/*Zag*/
                SpZag(tree, node->p);
        }
        else if(IsLc(node)) {
            if(IsLc(node->p)) {/*Zig-Zig*/
                SpZig(tree, node->p->p);
                SpZig(tree, node->p);
            }
            else {/*Zig-Zag*/
                SpZig(tree, node->p);
                SpZag(tree, node->p);
            }
        }
        else {
            if(IsRc(node->p)) {
                SpZag(tree, node->p->p);
                SpZag(tree, node->p);
            }
            else {
                SpZag(tree, node->p);
                SpZig(tree, node->p);
            }
        }
    }
}
void InsSp(SpTree *tree, int key) {
    SpNode *curr = tree->root, *prev = tree->NIL;
    while(curr != tree->NIL) {
        prev = curr;
        if(curr->v > key)    curr = curr->lc;
        else if(curr->v < key)    curr = curr->rc;
        else return;
    }
    curr = (SpNode*)malloc(sizeof(SpNode));
    curr->v = key;
    curr->p = prev;
    curr->lc = curr->rc = tree->NIL;
    if(prev == tree->NIL)    tree->root = curr;
    else if(prev->v > key)    prev->lc = curr;
    else    prev->rc = curr;
    SpSplay(tree, curr, tree->NIL);
}

void DelSp(SpTree *tree, int key) {
    SpNode *node = SpFind(tree, key);
    if(node == tree->NIL)    return;
    SpSplay(tree, node, tree->NIL);
    if(node->lc == tree->NIL && node->rc == tree->NIL)
        free(node), tree->root = tree->NIL;
    else {
        SpNode *temp = SpMin(tree, node->rc);
        if(temp == tree->NIL) {
            tree->root = node->lc;
            node->lc->p = tree->NIL;
        }
        else {
            if(temp != node->rc) {
                temp->rc->p = temp->p;
                temp->p->lc = temp->rc;
                temp->rc = node->rc;
            }
            temp->lc = node->lc;
            node->lc->p = temp,    node->rc->p = temp;
            temp->p = tree->NIL, tree->root = temp;
        }
        free(node);
    }
}
SpNode *SpFind(SpTree *tree, int key) {
    SpNode *curr = tree->root;
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
	freopen("out4.txt", "w+t", stdout);
    SpTree Tree;
    Spinit(&Tree);
    clock_t st, ed;
    st = clock();
    while(scanf("%d", &n) == 1)
		InsSp(&Tree, n);	
	ed = clock();
	printf("%f\n", (float)(ed - st )/CLOCKS_PER_SEC);
    SpFree(&Tree, Tree.root);

    return 0;
}
