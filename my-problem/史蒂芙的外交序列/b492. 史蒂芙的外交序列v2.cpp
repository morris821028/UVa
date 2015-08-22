#include <bits/stdc++.h> 
using namespace std;

const int MOD = 1000000007;
void exgcd(int x, int y, int &g, int &a, int &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
int inverse(int x, int p) {
    int g, b, r;
    exgcd(x, p, g, r, b);
    if (g < 0)	r = -r;
    return (r%p + p)%p;
}
class SegementTree {
public:
	static const int MAXN = 1000000;
	struct Node {
		Node *lson, *rson;
		int sum, prod;
	    Node() {
	    	lson = rson = NULL;
	    	prod = 1, sum = 0;
	    }
	} nodes[MAXN];
	int nodesize, L, R;
	Node* init(int l, int r) {
		nodesize = 0;
		L = l, R = r;
		Node* root = build(l, r);
		return root;
	}
	Node* newNode() {
		Node *u = &nodes[nodesize++];
		*u = Node();
		return u;
	}
	Node* cloneNode(Node *p) {
		Node* u = &nodes[nodesize++];
		*u = *p;
		return u;
	}
	Node* build(int l, int r) {
	    if (l > r)  return NULL;
	    Node *u = newNode();
	    if (l == r) {
		} else {
			int m = (l + r)/2;
	    	u->lson = build(l, m);
	    	u->rson = build(m+1, r);
		}
	    return u;
	}
	Node* change(Node *p, int x, long long val, int l, int r) {
		Node *u = cloneNode(p);
		u->prod = (u->prod * val)%MOD, u->sum++;
	    if (l == r) {
	    } else {
	    	int mid = (l + r)/2;
	    	if (x <= mid)
	        	u->lson = change(p->lson, x, val, l, mid);
	    	else
	     		u->rson = change(p->rson, x, val, mid+1, r);
	    }
	    return u;
	}
	Node* change(Node *p, int x, long long val) {
		return change(p, x, val, L, R);
	}
	
	int QV, QD;
	void find(Node *v1, int x, int l, int r) {
		if (1 <= l && r <= x) {
	    	QV = (long long)QV * v1->prod % MOD;
	    	QD += v1->sum;
	    	return ;
	    }
	    int mid = (l + r)/2;
	    if (x <= mid) {
	        find(v1->lson, x, l, mid);
	    } else {
			find(v1->lson, x, l, mid);
			find(v1->rson, x, mid+1, r);
		}
	}
	pair<int, int> find(Node *v1, int x) {
		QV = 1, QD = 0;
	    find(v1, x, L, R);
	    return {QD, QV};
	}
} tree;
const int MAXN = 65536;
SegementTree::Node *root[MAXN];
int main() {
	int N, Q, A[MAXN];
	int L, R, K;
	while (scanf("%d %d", &N, &Q) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
			
		root[0] = tree.init(1, N);
		for (int i = 1; i <= N; i++)
			root[i] = tree.change(root[i-1], A[i], A[i]);
		
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d", &L, &R, &K);
			int a, b;
			pair<int, int> r;
			r = tree.find(root[R], K);
			a = r.first, b = r.second;
			r = tree.find(root[L-1], K);
			a -= r.first, b = (long long) b * inverse(r.second, MOD)%MOD;
			if (a == 0) {
				printf("0 0\n");
			} else {
				printf("%d %d\n", a, b);
			}
		}
	}
	return 0;
}

