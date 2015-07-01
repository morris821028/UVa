#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 100005;
const int MAXD = 2;

class KD_Tree {
public:
    struct PointD {
        int d[MAXD], label;
    };
    struct Node {
        Node *lson, *rson;
        int label, size;
    };
    struct cmp {
        static int sortDidx;
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
    Node buf[MAXN], *root;
    PointD pt[MAXN], *A[MAXN];
    int bufsize, K, N;
    void prepare(int n) {
        N = n;
        bufsize = 0;
        for (int i = 0; i < n; i++)
            A[i] = &pt[i];
        root = build(0, 0, n-1);
    }
    Node* newNode() {
        return &buf[bufsize++];
    }
    Node* build(int k, int l, int r) {
        if(l > r)	return NULL;
        int m = (l + r)/2;
        Node *ret = newNode();
        cmp::sortDidx = k;
        nth_element(A + l, A + m, A + r + 1, cmp());
        ret->label = A[m]->label, ret->size = 1;
        ret->lson = ret->rson = NULL;
        if(l != r) {
            ret->lson = build((k+1)%K, l, m-1);
            ret->rson = build((k+1)%K, m+1, r);
            if (ret->lson)
                ret->size += ret->lson->size;
            if (ret->rson)
                ret->size += ret->rson->size;
        }
        return ret;
    }
    int qlx, qly, qrx, qry;
    int range_search(Node *u, int k, int area[]) {
        if (u == NULL)
            return 0;
        if (qlx <= area[0] && area[1] <= qrx &&
            qly <= area[2] && area[3] <= qry)
            return u->size;
        if (max(qlx, area[0]) > min(qrx, area[1]) ||
            max(qly, area[2]) > min(qry, area[3]))
            return 0;
        int split = pt[u->label].d[k], ret = 0;
        if (qlx <= pt[u->label].d[0] && pt[u->label].d[0] <= qrx &&
            qly <= pt[u->label].d[1] && pt[u->label].d[1] <= qry)
            ret++;
        if (k == 0) {
            swap(area[1], split);
            ret += range_search(u->lson, (k+1)%K, area);
            swap(area[1], split);
            swap(area[0], split);
            ret += range_search(u->rson, (k+1)%K, area);
            swap(area[0], split);
        } else {
            swap(area[3], split);
            ret += range_search(u->lson, (k+1)%K, area);
            swap(area[3], split);
            swap(area[2], split);
            ret += range_search(u->rson, (k+1)%K, area);
            swap(area[2], split);
        }
        return ret;
    }
    int range_query(int lx, int rx, int ly, int ry) {
        int h[] = {1, N, 1, N};
        qlx = lx, qrx = rx, qly = ly, qry = ry;
        return range_search(root, 0, h);
    }
} tree;
int KD_Tree::cmp::sortDidx;
int main() {
    int n, m, x;
    while (scanf("%d %d", &n, &m) == 2) {
        tree.K = 2;
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            tree.pt[i].d[0] = i+1;
            tree.pt[i].d[1] = x;
            tree.pt[i].label = i;
        }
        tree.prepare(n);
        for (int i = 0; i < m; i++) {
            int l, r, a, b;
            scanf("%d %d %d %d", &l, &r, &a, &b);
            int sum = tree.range_query(l, r, a, b);
            printf("%d\n", sum);
        }
    }
    return 0;
}