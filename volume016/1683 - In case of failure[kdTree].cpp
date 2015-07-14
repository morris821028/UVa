#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 262144
#define MAXD 2
#define INF (1LL<<60)
class kdTree {
public:
    struct PointD {
        long long d[MAXD];
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
    struct pQcmp {
        bool operator() (pair<long long, int> &a, pair<long long, int> &b) const {
            if (a.first != b.first)	return a.first < b.first;
            return a.second < b.second;
        }
    };
    static int sortDidx;
    priority_queue<pair<long long, int>, vector< pair<long long, int> >, pQcmp> pQ; // <dist, label>
    Node buf[MAXN], *root;
    PointD pt[MAXN], *A[MAXN];
    int bufsize, K, qM, n;
    long long Q[MAXD], max_dist;
    void prepare(int n) {
        this->n = n;
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
    long long dist(int idx) {
        long long ret = 0;
        for(int i = 0; i < K; i++)
            ret += (long long)(pt[idx].d[i] - Q[i]) * (pt[idx].d[i] - Q[i]);
        return ret;
    }
    long long h_func(long long h[]) {
        long long ret = 0;
        for(int i = 0; i < K; i++)	ret += h[i];
        return ret;
    }
    void findNearest(Node *u, int k, long long h[]) {
        if(u == NULL || h_func(h) >= max_dist)
            return;
        long long d = dist(u->label);
        if (d <= max_dist) {
            pQ.push(make_pair(d, u->label));
            while (pQ.size() >= qM + 1)
                max_dist = pQ.top().first, pQ.pop();
        }
        long long old_hk = h[k];
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
    void randomSearch(int ban) {
        max_dist = INF;
        long long d;
        for (int i = 0; i < 100; i++) {
            int x = rand()%n;
            if (x == ban)	continue;
            d = dist(x);
            if (d <= max_dist) {
                pQ.push(make_pair(d, x));
                while (pQ.size() >= qM + 1)
                    max_dist = pQ.top().first, pQ.pop();
            }
        }
    }
    void query(long long p[], int M, int ban) {
        for (int i = 0; i < K; i++)
            Q[i] = p[i];
        max_dist = INF, qM = M;
        long long h[MAXD] = {};
        randomSearch(ban);
        findNearest(root, 0, h);
        vector<int> ret;
        while (!pQ.empty())
            ret.push_back(pQ.top().second), pQ.pop();
        for (int i = (int) ret.size() - 1; i >= 0; i--) {
            if (ret[i] == ban)	continue;
            printf("%lld\n", dist(ret[i]));
            break;
        }
    }
};
int kdTree::sortDidx;

kdTree tree;
int main() {
    int n;
    long long p[MAXD];
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        tree.K = 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++)
                scanf("%lld", &tree.pt[i].d[j]);
            tree.pt[i].label = i;
        }
        tree.prepare(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++)
                p[j] = tree.pt[i].d[j];
            tree.query(p, 2, i);
        }
    }
    return 0;
}
/*
 2
 10
 17 41
 0 34
 24 19
 8 28
 14 12
 45 5
 27 31
 41 11
 42 45
 36 27
 15
 0 0
 1 2
 2 3
 3 2
 4 0
 8 4
 7 4
 6 3
 6 1
 8 0
 11 0
 12 2 
 13 1 
 14 2 
 15 0
 */ 
