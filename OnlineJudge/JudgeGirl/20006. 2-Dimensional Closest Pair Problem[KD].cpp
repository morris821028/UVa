#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 250005
#define MAXD 2
#define INF (1LL<<30)
struct kdTree {
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
            if (x->d[sortDidx] != y->d[sortDidx])
                return x->d[sortDidx] < y->d[sortDidx];
            return x->label < y->label;
        }
    };
    static int sortDidx;
    Node buf[MAXN], *root;
    PointD pt[MAXN], *A[MAXN];
    int bufsize, K, qM, n;
    int Q[MAXD], max_dist;
    void prepare(int n) {
        this->n = n;
        bufsize = 0;
        for (int i = 0; i < n; i++)
            A[i] = &pt[i];
        root = build(0, 0, n - 1);
    }
    Node* build(int k, int l, int r) {
        if (l > r)	return NULL;
		if (k >= K)	k = 0;
        int m = (l + r)/2;
        Node *ret = &buf[bufsize++];
        sortDidx = k;
        nth_element(A + l, A + m, A + r + 1, cmp());
        ret->label = A[m]->label, ret->lson = ret->rson = NULL;
        if (l != r) {
            ret->lson = build(k+1, l, m-1);
            ret->rson = build(k+1, m+1, r);
        }
        return ret;
    }
    inline int dist(int idx) {
        int ret = 0;
#if MAXD == 2
		ret += (pt[idx].d[0] - Q[0]) * (pt[idx].d[0] - Q[0]);
		ret += (pt[idx].d[1] - Q[1]) * (pt[idx].d[1] - Q[1]);
#else
        for(int i = 0; i < K; i++)
            ret += (pt[idx].d[i] - Q[i]) * (pt[idx].d[i] - Q[i]);
#endif
        return ret;
    }
    inline int h_func(int h[]) {
        long long ret = 0;
        for(int i = 0; i < K; i++)	ret += h[i];
        return ret;
    }
    int q_label;
    vector< pair<int, int> > report;
    void findNearest(Node *u, int k, int h[]) {
        if(u == NULL || h_func(h) > max_dist)
            return;
        if (u->label != q_label) {
        	int d = dist(u->label);
	        if (d < max_dist)
	        	max_dist = d, report.clear();
	        if (d == max_dist) {
	        	if (q_label < u->label)
	        		report.push_back(make_pair(q_label, u->label));
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
            if(u->rson != NULL)
                findNearest(u->rson, (k+1)%K, h);
            if (u->lson != NULL) {
                h[k] = (pt[u->label].d[k] - Q[k]) * (pt[u->label].d[k] - Q[k]);
                findNearest(u->lson, (k+1)%K, h);
                h[k] = old_hk;
            }
        }
    }
    void query(int p[], int ban) {
        for (int i = 0; i < K; i++)
            Q[i] = p[i];
        int h[MAXD] = {};
        q_label = ban;
        findNearest(root, 0, h);
    }
};
int kdTree::sortDidx;

kdTree tree;
int main() {
    int n;
   	int p[MAXD];
    scanf("%d", &n);
    tree.K = 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++)
            scanf("%d", &tree.pt[i].d[j]);
        tree.pt[i].label = i;
    }
    tree.prepare(n);
    tree.max_dist = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++)
            p[j] = tree.pt[i].d[j];
        tree.query(p, i);
    }
    printf("%.2f %d\n", sqrt(tree.max_dist), tree.report.size());
    for (int i = 0; i < tree.report.size(); i++) {
    	pair<int, int> t = tree.report[i];
    	printf("%d %d\n", t.first+1, t.second+1);
    }
    return 0;
}


