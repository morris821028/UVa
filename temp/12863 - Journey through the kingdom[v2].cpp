#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <set>
#include <algorithm> 
using namespace std;
#define MAXN 512
int V[MAXN][MAXN], R[MAXN][MAXN], C[MAXN][MAXN];
int dist[MAXN][MAXN];
struct Node {
    int r, c, v, h;
    Node(int a=0, int b=0, int d=0, int e=0):
    r(a), c(b), v(d), h(e) {}
    bool operator<(const Node &x) const {
        if (v != x.v)
            return v > x.v;
        return h > x.h;
    }
};
class rangeTree { // simple range tree.
    public:
    set< pair<int, int> > tree[MAXN<<1];
    int Lx, Rx, Ly, Ry;
    void init(int lx, int rx, int ly, int ry) {
        Lx = lx, Rx = rx;
        Ly = ly, Ry = ry;
        for (int i = 0; i < (MAXN<<1); i++)
            tree[i].clear();
        build(1, Lx, Rx);
    }
    void buildRectSet(set< pair<int,int> > &s, int lx, int rx, int ly, int ry) {
    	vector< pair<int, int> > A((rx-lx+1) * (ry-ly+1));
    	int n = 0;
    	for (int i = ly; i <= ry; i++) {
    		for (int j = lx; j <= rx; j++) {
    			A[n++] = make_pair(i, j);
    		}
    	}
    	s = set< pair<int,int> >(A.begin(), A.end());
    }
    void build(int k, int l, int r) {
        if (l == r) {
        	buildRectSet(tree[k], l, r, Ly, Ry);
            return;
        }
        int mid = (l + r)/2;
        build(k<<1, l, mid);
        build(k<<1|1, mid+1, r);
        buildRectSet(tree[k], l, r, Ly, Ry);
    }
    queue<set< pair<int, int> >*> rangeQuery(int lx, int rx) {
    	queue<set< pair<int, int> >*> ret;
    	query(1, Lx, Rx, lx, rx, ret);
    	return ret;
    }
    void query(int k, int l, int r, int x, int y, queue<set< pair<int, int> >*> &ret) {
    	if (x <= l && r <= y) {
    		ret.push(&tree[k]);
    		return;
    	}
    	int mid = (l + r)/2;
    	if (x <= mid)	query(k<<1, l, mid, x, y, ret);
    	if (y > mid)	query(k<<1|1, mid+1, r, x, y, ret);
    }
    void erasePoint(int x, int y) {
    	erase(1, Lx, Ly, x, y);
    }
    void erase(int k, int l, int r, int x, int y) {
    	if (l <= x && x <= r)	tree[k].erase(make_pair(y, x));
    	if (l == r)	return ;
    	int mid = (l + r)/2;
    	if (x < mid)	erase(k<<1, l, mid, x, y);
    	else			erase(k<<1|1, mid+1, r, x, y);
    }
} tree;
int findPath(int n, int m, int sx, int sy, int ex, int ey) {
	tree.init(0, n-1, 0, m-1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dist[i][j] = 0x3f3f3f3f;
        }
    }
    dist[sx][sy] = 0;
    priority_queue<Node> pQ;
    Node u, v;
    int lr, rr, lc, rc, d, x, y;
    pQ.push(Node(sx, sy, 0, abs(sx-ex) + abs(sy-ey)));
    while (!pQ.empty()) {
        u = pQ.top(), pQ.pop();
        queue<Node> Q;
        Q.push(u);
        tree.erasePoint(u.r, u.c);
        if (u.r == ex && u.c == ey)
            return dist[ex][ey];
        while (!pQ.empty() && pQ.top().v == u.v) {
            v = pQ.top(), pQ.pop();
        	tree.erasePoint(v.r, v.c);
            Q.push(v);
            if (v.r == ex && v.c == ey)
                return dist[ex][ey];
        }
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            if (dist[u.r][u.c] + V[u.r][u.c] < u.v)
                continue;
            d = dist[u.r][u.c] + V[u.r][u.c];
            if (d >= dist[ex][ey])
                continue;
            lr = max(0, u.r - R[u.r][u.c]);
            rr = min(n-1, u.r + R[u.r][u.c]);
            lc = max(0, u.c - C[u.r][u.c]);
            rc = min(m-1, u.c + C[u.r][u.c]);
            queue<set< pair<int, int> >*> rQ = tree.rangeQuery(lr, rr);
            while (!rQ.empty()) {
            	set< pair<int, int> >* s = rQ.front();
            	rQ.pop();
            	set< pair<int, int> >::iterator it = lower_bound(s->begin(), s->end(), make_pair(lc, -1));
            	for (; it != s->end() && it->first <= rc; it++) {
                    x = it->second, y = it->first;
                    if (dist[x][y] > d && d < dist[ex][ey]) {
                        dist[x][y] = d;
                        pQ.push(Node(x, y, d + V[x][y], abs(x-ex) + abs(y-ey)));
                    }
                }
            }
        }
    }
    return -1;
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);
    int n, m, q, X[16], Y[16];
    while (scanf("%d %d %d", &n, &m, &q) == 3) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &V[i][j]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &R[i][j]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &C[i][j]);
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &X[i], &Y[i]);
            X[i]--, Y[i]--;
        }
        for (int i = 1; i < q; i++) {
            int r = findPath(n, m, X[i-1], Y[i-1], X[i], Y[i]);
            printf("%d%c", r, i == q - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
/*
 3 4 5
 1 2 1 1
 1 5 3 4
 1 1 6 3
 1 2 3 3
 3 3 1 2
 0 0 0 1
 1 4 0 1
 2 3 0 1
 4 1 3 1
 1 1
 3 4
 1 1
 2 2
 2 2
 */
