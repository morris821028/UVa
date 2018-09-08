#include <bits/stdc++.h>
using namespace std;
class SuffixAutomaton {
public:
    static const int MAXN = 32768<<1;
    struct Node {
    	map<int, Node*> next;
        Node *pre;
        int step;
        void init() {
            pre = NULL, step = 0;
            next.clear();
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
        p->init();
        return p;
    }
    int toIndex(int c) { return c; }
    int toChar(int c) { return c; }
    void add(int c, int len) {
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
    void build(const int *s, int n) {
        init();

        for (int i = 0; i < n; i++)
            add(s[i], i+1);
    }
    
    void dfs(Node *u, int k, int &dist, int odd) {
    	for (auto e : u->next) {
        	Node *v = e.second;
        	int i = e.first;
            if (v) {
            	if (i&1) {
            		if (odd < k) {
            			dist++;
            			dfs(v, k, dist, odd+1);
					}
				} else {
					dist++;
					dfs(v, k, dist, odd);
				}
            }
        }
    } 
	int count(int k) {
		int dist = 0;
		dfs(root, k, dist, 0);
		return dist;
	}
} SAM;
int main() {
    int s[32768];
    int n, k;
    while (scanf("%d %d", &n, &k) == 2) {
    	for (int i = 0; i < n; i++)
    		scanf("%d", &s[i]);
        SAM.build(s, n);
    	auto ret = SAM.count(k);
    	printf("%d\n", ret);
    }
    return 0;
}
/*
4 1 
1 2 3 4

4 2
1 1 2 3 

8
8 
*/ 
