#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

typedef struct Pair {
	int x, lv;
} Pair;
typedef struct Node {
    int key, value;
    struct Node *lson, *rson, *parent;
} Node;
int cmp(const void *a, const void *b) {
	if (((Pair*) a)->x != ((Pair*) b)->x)
		return ((Pair*) a)->x < ((Pair*) b)->x ? -1 : 1;
	return ((Pair*) a)->lv - ((Pair*) b)->lv;
}
void insertCartesianTree(Node *p, Node *u) {
    while (p->value > u->value) {
        p = p->parent;
		assert(p != NULL);
	}
	if (p->rson != NULL)
    	p->rson->parent = u;
    u->lson = p->rson;
    p->rson = u;
    u->parent = p;
}
Node D[1024];
int Dnodesize = 0;
Node* newNode() {
	Node *p = &D[Dnodesize++];
	p->lson = p->rson = p->parent = NULL;
	return p;
}
Node* findNode(Node *u, int x) {
	while (u != NULL) {
		if (u->key == x)	return u;
		if (u->key > x)	
			u = u->lson;
		else
			u = u->rson;
	}
	return NULL;
}
int main() {
	int N, Q, x, y;
	Pair A[1024];
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &A[i].x, &A[i].lv);
			
		qsort(A, N, sizeof(Pair), cmp);
		Dnodesize = 0;
		Node *root = newNode();
		Node *prev = root;
		root->value = INT_MIN;
		for (int i = 0; i < N; i++) {
			Node *curr = newNode();
			curr->value = A[i].lv, curr->key = A[i].x;
			insertCartesianTree(prev, curr);
			prev = curr;
		}
		
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &x, &y);
			Node *u = findNode(root->rson, x);
			Node *v = findNode(root->rson, y);
			int dist = 0;
			while (u != v) {
				if (u->value > v->value)
					u = u->parent;
				else
					v = v->parent;
				dist++;
			}
			printf("%d\n", dist);
		}
	}
	return 0;
}

