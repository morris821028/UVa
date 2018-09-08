#include <bits/stdc++.h>
using namespace std;
class SuffixAutomaton {
public:
    static const int MAXN = 32768<<1;
    struct Node {
    	map<int, Node*> next;
        Node *pre;
        int step, count;
        void init() {
            pre = NULL, step = 0, count = 0;
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
		np->count = 1;
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
				nq->count = 0;
                for (; p && p->next[c] == q; p = p->pre)
                    p->next[c] = nq;
            }
        }
    }
    void build(const int *s, int n) {
        init();

        for (int i = 0; i < n; i++)
            add(s[i], i+1);
        
        // build right set
        static int w[MAXN] = {}, b[MAXN] = {};
        for (int i = 0; i <= n; i++)
        	w[i] = 0;        	
        for (int i = 0; i < size; i++)
        	w[_mem[i].step]++;
        for (int i = 1; i <= n; i++)
        	w[i] += w[i-1];
        for (int i = 0; i < size; i++)
        	b[--w[_mem[i].step]] = i;
        for (int i = size-1; i >= 1; i--)
        	_mem[b[i]].pre->count += _mem[b[i]].count;
    }
    
    void dfs(Node *u, int k, int &diff, int &dist, int odd) {
    	for (auto e : u->next) {
        	Node *v = e.second;
        	int i = e.first;
            if (v) {
            	if (i&1) {
            		if (odd < k) {
            			dist++, diff += v->count;
            			dfs(v, k, diff, dist, odd+1);
					}
				} else {
					dist++, diff += v->count;
					dfs(v, k, diff, dist, odd);
				}
            }
        }
    } 
	pair<int, int> count(int k) {
		int diff = 0, dist = 0;
		dfs(root, k, diff, dist, 0);
		return {diff, dist};
	}
    
    void dfs(Node *u, int idx, int path[]) {
        for (auto e : u->next) {
        	Node *v = e.second;
        	int i = e.first;
            if (v) {
                path[idx] = toChar(i);
                for (int j = 0; j <= idx; j++)
                	printf("%d ", path[j]);
                printf("---- %d\n", v->count);
                dfs(v, idx+1, path);
            }
        }
    }
    void print() {
    	int s[1024];
        dfs(root, 0, s);
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
    	printf("%d\n", ret.second);
//        SAM.print();
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
