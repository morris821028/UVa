#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAXN (1<<19)
#define ALPHA 0.75
const double LOG_ALPHA = log2(1.f / ALPHA);
typedef struct Char {
	char c;
	int cnt;
} Char;
typedef struct Node {
    struct Node *lson, *rson;
    int size, wsz;
    Char x;
} Node;

Node nodes[MAXN], *trash[MAXN], *root;
Char flatbuf[MAXN];
int bufsize, size, flatsz;
void init_tree() {
	size = bufsize = 0;
	root = NULL;
}
void init_node(Node *u) {
	u->lson = u->rson = NULL;
    u->size = u->wsz = 1;
}
Char clone_char(char c, int cnt) {
	Char x;
	x.c = c, x.cnt = cnt;
	return x;
}
void update_node(Node *u) {
	u->size = 1, u->wsz = u->x.cnt;
	if (u->lson) {
		u->size += u->lson->size;
		u->wsz += u->lson->wsz;
	}
	if (u->rson) {
		u->size += u->rson->size;
		u->wsz += u->rson->wsz;
	}
}
Node* new_node()  {
	Node *ret = &nodes[bufsize++];
	init_node(ret);
	return ret;
}
extern inline int log2int(int x){
    return __builtin_clz((int)1)-__builtin_clz(x);
}
extern inline int isbad(Node *u) {
	if (u->lson && u->lson->size > u->size * ALPHA)
		return 1;
	if (u->rson && u->rson->size > u->size * ALPHA)
		return 1;
	return 0;
}
Node* build(int l, int r) {
	if (l > r)	return NULL;
	int mid = (l + r)>>1;
	Node *ret = trash[mid];
	init_node(ret);
	ret->x = flatbuf[mid];
    ret->lson = build(l, mid-1);
    ret->rson = build(mid+1, r);
	update_node(ret);
	return ret;
}
void flatten(Node *u) {
	if (u == NULL)	return ;
	flatten(u->lson);
	trash[flatsz] = u;
	flatbuf[flatsz++] = u->x;
	flatten(u->rson);
}
bool insert_node(Node **u, int dep, int pos, Char x) {
	if (*u == NULL) {
		*u = new_node(), (*u)->x = x, update_node(*u);
		return dep <= 0;
	}
	int t = 0, lsz = (*u)->lson ? (*u)->lson->wsz : 0, wsz = (*u)->x.cnt;
	if (pos <= lsz+1) {
		t = insert_node(&((*u)->lson), dep-1, pos, x);
	} else if (pos > lsz + wsz) {
		t = insert_node(&((*u)->rson), dep-1, pos-lsz-wsz, x);
	} else {
		int remain = pos-lsz-1;
		insert_node(&((*u)->rson), dep-1, 0, clone_char((*u)->x.c, (*u)->x.cnt-remain));
		insert_node(&((*u)->rson), dep-1, 0, x);
		(*u)->x.cnt = remain;
	}
	update_node(*u);
	if (t && !isbad(*u))
		return 1;
	if (t) {
		flatsz = 0;
		flatten(*u);
		*u = build(0, flatsz-1);
	}
	return 0;
}
void insert(int pos, Char x) {
	insert_node(&root, log2int(size) / LOG_ALPHA, pos, x);
}
int buf[1<<20][2], bidx = 0;
void debug(Node *u) {
	if (u == NULL)	return ;
	debug(u->lson);
	if (bidx == 0 || buf[bidx-1][0] != u->x.c)
		buf[bidx][0] = u->x.c, buf[bidx][1] = u->x.cnt, bidx++;
	else
		buf[bidx-1][1] += u->x.cnt;
	debug(u->rson);
}
void print_tree() {
	bidx = 0;
	debug(root);
	for (int i = 0; i < bidx; i++)
        printf("%c %d ", buf[i][0], buf[i][1]);
    puts("$");
}
int main() {
    init_tree();
    char cmd[16], args[3][16];
	int n = 0, m;
	while (scanf("%s", cmd) == 1) {
		if (!strcmp(cmd, "insert")) {
			scanf("%s %s %d", args[0], args[1], &m);
			int pos = -1, x;
			if (!strcmp(args[0], "left")) {
				pos = 1;
			} else if (!strcmp(args[0], "right")) {
				pos = n+1;
			} else {
				sscanf(args[0], "%d", &x);
				pos = x;
			}
			Char c = {args[1][0], m};
			insert(pos, c);
			n += m;
		} else {
			print_tree();
		}
	}	
    return 0;
}
