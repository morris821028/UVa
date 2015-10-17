#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define MAXN 400005
typedef struct Node {
    struct Node *ch[2], *fa;
    int val, size;
} Node;
Node _mem[MAXN];
struct Node *EMPTY;
Node node_init() {
	Node u;
    u.ch[0] = u.ch[1] = u.fa = NULL;
    u.val = 0, u.size = 1;
    return u;
}
bool is_root(Node *u) {
    return u->fa->ch[0] != u && u->fa->ch[1] != u;
}
void pushdown() {

}
void pushup(Node *u) {
    if (u->ch[0] != EMPTY)	pushdown(u->ch[0]);
    if (u->ch[1] != EMPTY)	pushdown(u->ch[1]);
    u->size = 1 + u->ch[0]->size + u->ch[1]->size;
}
//
int bufIdx;
Node *root;
void splay_init() {
    EMPTY = &_mem[0];
    EMPTY->fa = EMPTY->ch[0] = EMPTY->ch[1] = EMPTY;
    EMPTY->size = EMPTY->val = 0;
    bufIdx = 1; 
}
Node* newNode() {
    Node *u = &_mem[bufIdx++];
    *u = node_init();
    u->fa = u->ch[0] = u->ch[1] = EMPTY;
    return u;
}
void rotate(Node *x) {
    Node *y;
    int d;
    y = x->fa, d = y->ch[1] == x ? 1 : 0;
    x->ch[d^1]->fa = y, y->ch[d] = x->ch[d^1];
    x->ch[d^1] = y;
    if (!is_root(y))
        y->fa->ch[y->fa->ch[1] == y] = x;
    x->fa = y->fa, y->fa = x;
    pushup(y);
}
void deal(Node *x) {
    if (!is_root(x))	deal(x->fa);
    pushdown(x);
}
Node* find_rt(Node *x) {
    for (; x->fa != EMPTY; x = x->fa);
    return x;
}
void splay(Node *x, Node *below) {
    Node *y, *z;
    deal(x);
    while (!is_root(x) && x->fa != below) {
        y = x->fa, z = y->fa;
        if (!is_root(x) && y->fa != below) {
            if (y->ch[0] == x ^ z->ch[0] == y)
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
    pushup(x);
    if (x->fa == EMPTY)	root = x;
}
Node* build(int l, int r, Node *p, char s[]) {
    if (l > r)	return EMPTY; 
    int mid = (l + r)/2;
    Node *t = newNode();
    t->val = s[mid], t->fa = p;
    t->ch[0] = build(l, mid-1, t, s);
    t->ch[1] = build(mid+1, r, t, s);
    pushup(t);
    if (p == EMPTY)	root = t;
    return t;
}
char buf[1<<20], *bufptr;
void debug(Node *u){
    if (u == EMPTY) return;
    pushdown(u);
    debug(u->ch[0]);
    (*bufptr) = u->val, bufptr++;
    debug(u->ch[1]);
}
Node* kthNode(int pos) {
	Node *u = root;
	for (int t; u != EMPTY;) {
		pushdown(u);
		t = u->ch[0]->size;
		if (t+1 == pos)	return u;
		if (t >= pos)
			u = u->ch[0];
		else
			pos -= t+1, u = u->ch[1];
	}
	return EMPTY;
} 
void insert(int pos, int val) {
	Node *p, *q, *r;
	p = kthNode(pos), q = kthNode(pos+1);
	r = newNode();
	splay(p, EMPTY);
	splay(q, root);
	r->val = val, q->ch[0] = r, r->fa = q;
	splay(r, EMPTY);
}
void erase(int pos) {
	Node *p, *q;
	p = kthNode(pos-1), q = kthNode(pos+1);
	splay(p, EMPTY), splay(q, root);
	q->ch[0] = EMPTY;
	splay(q, EMPTY);
}

int main() {
	splay_init();
	root = build(0, 1, EMPTY, "#$");
	char cmd[16], args[2][16];
	int n = 0;
	while (scanf("%s", cmd) == 1) {
		if (!strcmp(cmd, "insert")) {
			scanf("%s %s", args[0], args[1]);
			int pos = 0, x;
			if (!strcmp(args[0], "left")) {
				pos = 0;
			} else if (!strcmp(args[0], "right")) {
				pos = n;
			} else {
				sscanf(args[0], "%d", &x);
				pos = x-1;
			}
			insert(pos+1, args[1][0]);
			n++;
		} else {
			scanf("%s", args[0]);
			int pos = 0, x;
			if (!strcmp(args[0], "left")) {
				pos = 0;
			} else if (!strcmp(args[0], "right")) {
				pos = n-1;
			} else {
				sscanf(args[0], "%d", &x);
				pos = x-1;
			}
			erase(pos+2);
			n--;
		}
	}
	bufptr = buf;
	debug(root);
	char *s = buf+1;
	int cnt = 1, mx = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == s[i-1]) {
			cnt++;
		} else {
			if (cnt > mx)
				mx = cnt;
			cnt = 1;
		}
	}
	cnt = 1;
	for (int i = 1; i <= n; i++) {
		if (s[i] == s[i-1]) {
			cnt++;
		} else {
			if (cnt == mx)
				printf("%c ", s[i-1]);
			cnt = 1;
		}
	}
	printf("%d\n", mx);
	return 0;
}
