#include <bits/stdc++.h>

class SuffixAutomaton {
public:
	static const int MAXN = 500<<1;
	static const int MAXC = 26;
	struct Node {
		Node *next[MAXC], *pre;
		int step;
		Node() {
			pre = NULL, step = 0;
			memset(next, 0, sizeof(next));
		}
	} _mem[MAXN];
	int size;
	Node *root, *tail;	
	void init() {
		size = 0;
		root = tail = newNode();
	}
	Node* newNode() {
		Node *p = &_mem[size++];
		*p = Node();
		return p;
	}
	int toIndex(char c) { return c - 'A'; }
	char toChar(int c) { return c + 'A'; }
	void add(char c, int len) {
		c = toIndex(c);
		Node *p, *q, *np, *nq;
		p = tail, np = newNode();
		np->step = len;
		for (; p && p->next[c] == NULL; p = p->pre)
			p->next[c] = np;
		tail = np;
		if (p == NULL) {
			np->pre = root;
		} else {
			if (p->next[c]->step == p->step+1) {
				np->pre = p->next[c];
			} else {
				q = p->next[c], nq = newNode();
				*nq = *q;
				nq->step = p->step + 1;
				q->pre = np->pre = nq;
				for (; p && p->next[c] == q; p = p->pre)
					p->next[c] = nq;
			}
		}
	}
	void build(const char *s) {
		init();
		for (int i = 0; s[i]; i++)
			add(s[i], i+1);
	}
	void dfs(Node *u, int idx, char path[]) {
		for (int i = 0; i < MAXC; i++) {
			if (u->next[i]) {
				path[idx] = toChar(i);
				path[idx+1] = '\0';
				puts(path);
				dfs(u->next[i], idx+1, path);
			}
		}
	}
	void print() {
		char s[1024];
		dfs(root, 0, s);
	} 
} SAM;

int main() {
	char s[1024];
	while (scanf("%s", s) == 1) {
		SAM.build(s);
		SAM.print();
	}
	return 0;
}
