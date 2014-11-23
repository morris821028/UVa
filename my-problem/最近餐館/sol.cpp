#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 8192
#define MAXD 8
#define INF 0x3f3f3f3f
class kdTree {
	public:	
	struct PointD {
		int d[MAXD];
		int label;
	};
	struct Node {
    	Node *lson, *rson;
    	int label;
	};
	struct cmp {
		bool operator()(const PointD* x, const PointD* y) const {
    		return x->d[sortDidx] < y->d[sortDidx];
		}
	};
	struct pQcmp {
	    bool operator() (pair<int, int> &a, pair<int, int> &b) const {
	    	if (a.first != b.first)	return a.first < b.first;
	    	return a.second < b.second;
	    }
	};
	static int sortDidx;
	priority_queue<pair<int, int>, vector< pair<int, int> >, pQcmp> pQ; // <dist, label>
	Node buf[MAXN], *root;
	PointD pt[MAXN], *A[MAXN];
	int bufsize, K;
	int Q[MAXD], max_dist, qM;
	void prepare(int n) {
        bufsize = 0;
        for (int i = 0; i < n; i++)
        	A[i] = &pt[i];
        root = build(0, 0, n - 1);
	}
	Node* build(int k, int l, int r) {
	    if(l > r)	return NULL;
	    int m = (l + r)/2;
	    Node *ret = &buf[bufsize++];
	    sortDidx = k;
	    nth_element(A + l, A + m, A + r + 1, cmp());
	    ret->label = A[m]->label, ret->lson = ret->rson = NULL;
	    if(l != r) {
	        ret->lson = build((k+1)%K, l, m-1);
	        ret->rson = build((k+1)%K, m+1, r);
	    }
	    return ret;
	}
	int dist(int idx) {
	    int ret = 0;
	    for(int i = 0; i < K; i++)
	        ret += (pt[idx].d[i] - Q[i]) * (pt[idx].d[i] - Q[i]);
	    return ret;
	}
	int h_func(int h[]) {
	    int ret = 0;
	    for(int i = 0; i < K; i++)	ret += h[i];
	    return ret;
	}
	void findNearest(Node *u, int k, int h[]) {
	    if(u == NULL || h_func(h) >= max_dist)
	        return;
	    int d = dist(u->label);
	    if (d < max_dist) {
	        pQ.push(make_pair(d, u->label));
	        if (pQ.size() == qM + 1) {
	            max_dist = pQ.top().first, pQ.pop();
	        }
	    }
	    int old_hk = h[k];
	    if (Q[k] <= pt[u->label].d[k]) {
	        if (u->lson != NULL)
	            findNearest(u->lson, (k+1)%K, h);
	        if (u->rson != NULL) {
	            h[k] = (pt[u->label].d[k] - Q[k]) * (pt[u->label].d[k] - Q[k]);
	            findNearest(u->rson, (k+1)%K, h);
	            h[k] = old_hk;
	        }
	    } else {
	        if (u->lson != NULL) {
	            h[k] = (pt[u->label].d[k] - Q[k]) * (pt[u->label].d[k] - Q[k]);
	            findNearest(u->lson, (k+1)%K, h);
	            h[k] = old_hk;
	        }
	        if(u->rson != NULL)
	            findNearest(u->rson, (k+1)%K, h);
	    }
	}
	void query(int p[], int M) {
		for (int i = 0; i < K; i++)
			Q[i] = p[i];
	    max_dist = INF, qM = M;
	    int h[MAXD] = {};
		findNearest(root, 0, h);
	    printf("%d", M);
	    vector<int> ret;
	    while (!pQ.empty())
	        ret.push_back(pQ.top().second), pQ.pop();
	    for (int i = ret.size() - 1; i >= 0; i--)
	    	printf(" %d", ret[i] + 1);
	    puts("");
	}
};	
int kdTree::sortDidx;

kdTree tree;
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, m, q, p[MAXD], x;
	int cases = 0;
    while (scanf("%d %d", &n, &m) == 2) {
    	tree.K = m;
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < m; j++)
    			scanf("%d", &tree.pt[i].d[j]);
    		tree.pt[i].label = i;
    	}
    	tree.prepare(n);
        scanf("%d", &q);
        while (q--) {
        	for (int i = 0; i < m; i++)
        		scanf("%d", &p[i]);
        	scanf("%d", &x);
        	printf("Case %d: ", ++cases);
        	tree.query(p, x);
        }
    }
    return 0;
}
/*
2 2
1 1
3 3
1
2 2
1

3 2
1 1
1 3
3 4
2
2 3
2
2 3
1
*/ 
