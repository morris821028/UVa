#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#define MAXN 262144
#define MAXS 2048
typedef struct Node {
    char A[MAXS+2];
    int B[MAXS+2];
    int size, bsize;
    struct Node *next, *prev;
} Node;
int midx = 0;
Node _mem[1024];
extern inline void node_init(Node *u) {
    u->size = 0, u->bsize = 0, u->next = u->prev = NULL;
}
extern inline void node_insert(Node *x, int pos, char val, int valcnt) {
    int l = 0, r;
    for (int i = 0; i < x->size; i++) {
    	r = l + x->B[i] - 1;	// [l, r]
    	if (pos == l) {			// insert before
    		memmove(x->A+i+1, x->A+i, x->size-i);
    		memmove(x->B+i+1, x->B+i, sizeof(x->B[0]) * (x->size-i));
    		x->A[i] = val, x->B[i] = valcnt;
    		x->size++, x->bsize += valcnt;
    		return ;
		}
		if (pos > l && pos <= r) {	// split
			char c = x->A[i];
			int v = x->B[i];
			memmove(x->A+i+2, x->A+i, x->size-i);
    		memmove(x->B+i+2, x->B+i, sizeof(x->B[0]) * (x->size-i));
    		x->A[i] = x->A[i+2] = c;
    		x->B[i] = pos - l, x->B[i+2] = v - x->B[i];
    		x->A[i+1] = val, x->B[i+1] = valcnt;
    		x->size += 2, x->bsize += valcnt;
    		return ;
		}
    	l = r+1;
	}
	x->A[x->size] = val, x->B[x->size] = valcnt;
	x->size++, x->bsize += valcnt;
}
extern inline Node* newNode() {
    Node *p = &_mem[midx++];
    node_init(p);
    return p;
}
// UnrolledLinkedList
Node *head, *tail;
int PSIZE = MAXS;
Node* unrolled_init() {
    Node *head = newNode();
    head->size = head->bsize = 2, head->A[0] = '#', head->A[1] = '$';
    head->B[0] = head->B[1] = 1;
    return tail = head;
}
int buf[1<<20][2], bidx = 0;
void debug(Node *head) {
    Node *u = head;
    bidx = 0;
    while (u != NULL) {
        for (int i = 0; i < u->size; i++) {
        	if (bidx == 0 || buf[bidx-1][0] != u->A[i]) {
        		buf[bidx][0] = u->A[i], buf[bidx][1] = u->B[i];
        		bidx++;
			} else {
				buf[bidx-1][1] += u->B[i];
			}
        }
        u = u->next;
    }
    for (int i = 1; i < bidx-1; i++) {
        printf("%c %d ", buf[i][0], buf[i][1]);
    }
    puts("$");
}
extern inline Node* mergeNode(Node *u, Node *v) {
    memcpy(u->A+u->size, v->A, v->size);
    memcpy(u->B+u->size, v->B, sizeof(v->B[0]) * v->size);
    u->next = v->next, u->size += v->size, u->bsize += v->bsize;
    if (v->next)    v->next->prev = u;
    else			tail = u;
    return u;
}
extern inline Node* splitNode(Node *u) {
    Node *v = newNode();
    int n = u->size>>1;
    long long bsz = 0;
    memcpy(v->A, u->A+n, u->size-n);
    memcpy(v->B, u->B+n, sizeof(v->B[0]) * (u->size-n));
    v->size = u->size - n, u->size = n;
    for (int i = 0; i < v->size; i++)
    	bsz += v->B[i];
    v->bsize = bsz, u->bsize -= bsz;
	if (u->next)    u->next->prev = v;
    else            tail = v;
    v->next = u->next, u->next = v;
    v->prev = u;    
    return u;
}
extern inline void relaxList(Node *u, int dir) {
    if (dir == 1) {
        if (u->next != NULL && u->size + u->next->size < PSIZE) {
            mergeNode(u, u->next);
        } else if (u->size > PSIZE) {
            splitNode(u);
        }
    } else {
        if (u->prev != NULL && u->size + u->prev->size < PSIZE) {
            mergeNode(u->prev, u);
        } else if (u->size > PSIZE) {
            splitNode(u);
        }
    }
}
extern inline void insert(Node *ver, int pos, char val, int valcnt) {
    Node *u = ver;
    for (int l = 1, r; u; l = r+1, u = u->next) {
        r = l + u->bsize - 1;
        if (l-1 <= pos && pos <= r || u->next == NULL) {
            node_insert(u, pos - l + 1, val, valcnt);
            relaxList(u, 1);
            return ;
        }
    }
}
extern inline void rinsert(Node *u, char val, int valcnt) {
	node_insert(u, u->bsize-1, val, valcnt);
	relaxList(u, 1);
}
int main() {
    head = unrolled_init();
    char cmd[16], args[3][16];
	int n = 0, m;
	while (scanf("%s", cmd) == 1) {
		if (!strcmp(cmd, "insert")) {
			scanf("%s %s %lld", args[0], args[1], &m);
			int pos = 0, x;
			if (!strcmp(args[0], "left")) {
				pos = 0;
				insert(head, pos+1, args[1][0], m);
			} else if (!strcmp(args[0], "right")) {
				pos = n;
				rinsert(tail, args[1][0], m);
			} else {
				sscanf(args[0], "%d", &x);
				pos = x-1;
				insert(head, pos+1, args[1][0], m);
			}
			n += m;
		} else {
			debug(head);
		}		
	}	
    return 0;
}


