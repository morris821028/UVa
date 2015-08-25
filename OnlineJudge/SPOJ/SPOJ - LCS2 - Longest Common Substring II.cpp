#include <bits/stdc++.h>
using namespace std;

class SuffixAutomaton {
private:
	static const int MAXN = 200005;
	static const int MAXC = 26;
	struct Node {
		Node *next[MAXC], *pre;
		int step;
		int cmx, amx;	// compute LCS
		Node() {
			pre = NULL, step = 0, amx = INT_MAX, cmx = 0;
			memset(next, 0, sizeof(next));
		}
	} _mem[MAXN], *order[MAXN];
	int size, cnt[MAXN];
	Node *root, *tail;
	inline int toIndex(char c) 	{ return c - 'a'; }
	inline char toChar(int c) 	{ return c + 'a'; }
	void init() {
		size = 0;
		root = tail = newNode();
	}
	Node* newNode() {
		Node *p = &_mem[size++];
		*p = Node();
		return p;
	}
	void add(char c, int len) {
		Node *p, *q, *np, *nq;
		c = toIndex(c);
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
	void topo() {	// radix sort
		for (int i = 0; i < size; i++)	cnt[i] = 0;
		for (int i = 0; i < size; i++)	cnt[_mem[i].step]++;
		for (int i = 1; i < size; i++)	cnt[i] += cnt[i-1];
		for (int i = 0; i < size; i++)	order[--cnt[_mem[i].step]] = &_mem[i];
	}
public:
	void build(const char *s) {
		init();
		for (int i = 0; s[i]; i++)	add(s[i], i+1);
		topo();
	}
	void add_match(const char *s) {
		Node *u = root;
		int c, match = 0;
		for (int i = 0; i < size; i++)
			_mem[i].cmx = 0;
		for (int i = 0; s[i]; i++) {
			c = toIndex(s[i]);
			if (u->next[c]) {
				match++, u = u->next[c];
			} else {
				for (; u && u->next[c] == NULL; u = u->pre);
				if (u == NULL)
					match = 0, u = root;
				else
					match = u->step+1, u = u->next[c];
			}
			u->cmx = max(u->cmx, match);
		}
		for (int i = size-1; i >= 0; i--) { // dp update
			u = order[i];
			u->amx = min(u->amx, u->cmx);
			if (u->pre)
				u->pre->cmx = max(u->pre->cmx, min(u->pre->step, u->cmx));
		}
	}
	int lcs() {
		int ret = 0;
		for (int i = 0; i < size; i++)
			ret = max(ret, _mem[i].amx);
		return ret;
	}
} SAM;
char s[16][131072];
int main() {
	int n = 0;
	while (scanf("%s", s[n]) == 1) n++;
	SAM.build(s[0]);
	for (int i = 1; i < n; i++)
		SAM.add_match(s[i]);
	printf("%d\n", SAM.lcs());
	return 0;
}
