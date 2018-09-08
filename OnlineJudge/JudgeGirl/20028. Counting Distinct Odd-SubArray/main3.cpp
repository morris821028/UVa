#include <bits/stdc++.h>
using namespace std;
class SuffixAutomaton {
public:
    static const int MAXN = 32768<<1;
    static const int MAXNODE = 32768;
	static const int MAXSTACK = 32768;
    struct Node;
    struct TNode;
    struct TNode {
		int key;
		Node *val;
		TNode *lson, *rson;
		void init() {
			val = NULL, key = -1;
			lson = rson = NULL;
		}
	} tnodes[MAXNODE];
    struct Node {
    	TNode *next;
        Node *pre;
        int step;
        void init() {
            pre = NULL, step = 0, next = NULL;
        }
    } _mem[MAXN];
    static TNode *tnode_iter[MAXSTACK];
    static int tnode_iter_offset;
	struct TNodeIter {
		int size, index;
		TNodeIter(TNode *root) {
			size = 0, index = 0;
			dfs(root);
		}
		void dfs(TNode *u) {
			if (u == NULL)
				return ;
			tnode_iter[size++] = u;
			dfs(u->lson);
			dfs(u->rson);
		}
		TNode* next() {
			TNode *ret = NULL;
			if (index < size) {
				ret = tnode_iter[index];
				index++;
			}
			return ret;
		}
	};
	
	struct NodeBalancer {
		int index;
		void flatten(TNode *u) {
			if (u == NULL)
				return ;
			flatten(u->lson);
			tnode_iter[index++] = u;
			flatten(u->rson);
		}
		TNode* build(int l, int r) {
			if (l > r)
				return NULL;
			int m = (l+r)/2;
			TNode *u = tnode_iter[m];
			u->lson = build(l, m-1);
			u->rson = build(m+1, r);
			return u;
		}
	    void rebalance(Node *p) {
	    	TNode *root = p->next;
	    	index = 0;
	    	flatten(root);
	    	p->next = build(0, index-1);
		}
	} balancer;
    
    Node* &next(Node *p, const int key) {
    	TNode *root = p->next;
    	TNode *u;
    	if (root == NULL) {
    		u = newTNode();
    		u->key = key;
    		p->next = u;
    		return u->val;
		}
		int dep = 0;
		while (root != NULL) {
			if (root->key == key)
				return root->val;
			dep++;
			if (key < root->key) {
				if (root->lson != NULL) {
					root = root->lson;
				} else {
					u = newTNode();
		    		u->key = key;
		    		root->lson = u;
		    		goto done;
				}
			} else {
				if (root->rson != NULL) {
					root = root->rson;
				} else {
					u = newTNode();
		    		u->key = key;
		    		root->rson = u;
		    		goto done;
				}
			}
		}
		done:
		if (dep > 10)
			balancer.rebalance(p);
		return u->val;
	}
	Node* find(Node *p, const int key) {
    	TNode *root = p->next;
		while (root != NULL) {
			if (root->key == key)
				return root->val;
			if (key < root->key)
				root = root->lson;
			else
				root = root->rson;
		}
		return NULL;
	}
	void cloneNext(Node *p, Node *q) {
		TNodeIter next_it(q->next);
		for (TNode *e = next_it.next(); e != NULL; e = next_it.next()) {
    		Node *v = e->val;
        	int c = e->key;        	
        	Node* &tmp = next(p, c);
        	tmp = v;
		}
	}
    
    int size, tsize;
    Node *root, *tail;	
    void init() {
        size = 0, tsize = 0;
        tnode_iter_offset = 0;
        root = tail = newNode();
    }
    TNode* newTNode() {
    	TNode *p = &tnodes[tsize++];
        assert(tsize < MAXNODE);
        p->init();
        return p;
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
        for (; p && find(p, c) == NULL; p = p->pre) {
        	Node* &link = next(p, c);
            link = np;
        }
        tail = np;
        if (p == NULL) {
            np->pre = root;
        } else {
        	Node* &link = next(p, c);
            if (link->step == p->step+1) {
                np->pre = link;
            } else {
                q = link, nq = newNode();
                *nq = *q, nq->next = NULL;
                cloneNext(nq, q);
                nq->step = p->step + 1;
                q->pre = np->pre = nq;
                for (; p && find(p, c) == q; p = p->pre) {
        			Node* &link = next(p, c);
            		link = nq;
        		}
            }
        }
    }
    void build(const int *s, int n) {
        init();

        for (int i = 0; i < n; i++)
            add(s[i], i+1);
    }
    
    int bfs(int k) {
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
        for (int i = size-1; i >= 1; i--) {
        	Node *u = _mem[b[i]];
        	Node *f = u->pre;
//        	_mem[b[i]].pre->count += _mem[b[i]].count;
		}
    	
    	
    	int dist = 0;
    	queue<pair<Node*, int>> Q;
    	map<Node*, int> R;
    	Q.push({root, 0});
    	int v = 0;
    	while (!Q.empty()) {
    		auto e = Q.front(); Q.pop();
    		v++;
    		int odd = e.second;
    		Node *u = e.first;
    		if (R.count(u) && R[u] != odd)
    			puts("?");
    		
    		R[u] = odd;
    		TNodeIter next_it(u->next);	
    		for (TNode *e = next_it.next(); e != NULL; e = next_it.next()) {
	    		Node *v = e->val;
	        	int i = e->key;
	            if (v) {
	            	if (i&1) {
	            		if (odd < k) {
	            			dist++;
	            			Q.push({v, odd+1});
						}
					} else {
						dist++;
						Q.push({v, odd});
					}
	            }
        	}
		}
		printf("%d\n", v);
		return dist;
    } 
	int count(int k) {
		int dist = bfs(k);
		return dist;
	}
} SAM;
int SuffixAutomaton::tnode_iter_offset = 0;
SuffixAutomaton::TNode *SuffixAutomaton::tnode_iter[SuffixAutomaton::MAXSTACK];
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
