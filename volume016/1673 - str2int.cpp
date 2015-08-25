#include <bits/stdc++.h>
using namespace std;

class SuffixAutomaton {
private:
	static const int MAXN = 262144;
	static const int MAXC = 11;
	struct Node {
		Node *next[MAXC], *pre;
		int step;
		int way, sum;
		Node() {
			pre = NULL, step = 0;
			memset(next, 0, sizeof(next));
			way = 0;
			sum = 0;
		}
	} _mem[MAXN], *order[MAXN];
	int size, cnt[MAXN];
	Node *root, *tail;
	inline int toIndex(char c) 	{ 
		if (isdigit(c))	return c - '0';
		return 10;
	}
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
	int unique_sum(const char *s) {
		int ret = 0;
		root->way = 1;
		for (int i = 0; i < size; i++) {
			Node *u = order[i];
			ret = (ret + u->sum)%2012;
			for (int j = 0; j < 10; j++) {
				if (i == 0 && j == 0)
					continue;
				if (u->next[j]) {
					u->next[j]->way += u->way;
					u->next[j]->sum += (u->sum * 10 + u->way * j)%2012;
					u->next[j]->way %= 2012;
					u->next[j]->sum %= 2012;
				}
			}
		}
		return ret;
	}
} SAM;
char s[262144];
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		char *ptr = s;
		for (int i = 0; i < n; i++) {
			scanf("%s", ptr);
			for (; *ptr; ptr++);
			*ptr = '$', ptr++, *ptr = '\0';
		}
		SAM.build(s);
		printf("%d\n", SAM.unique_sum(s));
	}
	return 0;
}
