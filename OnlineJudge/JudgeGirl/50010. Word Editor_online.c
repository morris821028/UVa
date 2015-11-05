#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define MAXC 128
#define MAXV 1048576
#define LINK(p, q, r) q->next = r, q->prev = p, p->next = q, r->prev = q
typedef struct Node {
	struct Node *next, *prev;
	int id;
	char c;
} Node;
int A[MAXC], parent[MAXV];
Node nodes[MAXV], *head;
int nIdx = 0;
int toIndex(char c) {
	return c - 'a';
}
int findp(int x) {
	return parent[x] == x ? x : (parent[x] = findp(parent[x]));
}
void joint(int x, int y) {
	x = findp(x), y = findp(y);
	parent[x] = y;
}
Node* new_node(int c) {
	Node *p = &nodes[nIdx];
	p->c = c, p->id = nIdx, parent[nIdx] = nIdx;
	nIdx++;
	return p;
}
void new_chairman(int c) {
	A[c] = nIdx;
	new_node(c+'a');
}
void init() {
	nIdx = 0;
	head = new_node('#');
	head->prev = head->next = head;
	for (int i = 0; i < 26; i++)
		new_chairman(i);
}
void addhead(int c) {
	Node *q = new_node(c), *p = head, *r = head->next;
	LINK(p, q, r);
	joint(q->id, A[c]);
}
void addtail(int c) {
	Node *q = new_node(c), *p = head->prev, *r = head;
	LINK(p, q, r);
	joint(q->id, A[c]);
}
void debug() {
	for (Node *p = head->next; p != head; p = p->next) {
		int q = findp(p->id);
		if (!q)	continue;
		putchar(nodes[q].c);
	}
	puts("");
}
char cmd[16], s1[4], s2[4], S[1<<20];
int main() {
	int x, y;
	init();
	scanf("%s", S);
	for (int i = 0; S[i]; i++)
		addtail(toIndex(S[i]));
	while (scanf("%s", cmd) == 1) {
		if (!strcmp(cmd, "end"))
			break;
		if (!strcmp(cmd, "replace")) {
			scanf("%s %s", s1, s2);
			x = toIndex(s1[0]), y = toIndex(s2[0]);
			if (x == y)
				continue;
			joint(A[x], A[y]);
			new_chairman(x);
		} else if (!strcmp(cmd, "remove")) {
			scanf("%s", s1);
			x = toIndex(s1[0]), joint(A[x], 0);
			new_chairman(x);
		} else if (!strcmp(cmd, "addhead")) {
			scanf("%s", s1);
			addhead(toIndex(s1[0]));
		} else if (!strcmp(cmd, "addtail")) {
			scanf("%s", s1);
			addtail(toIndex(s1[0]));
		} else {
			printf("invalid command %s\n", cmd);
			exit(0);
		}
	}
	debug();
	return 0;
}


