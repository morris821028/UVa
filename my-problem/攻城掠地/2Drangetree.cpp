#include <bits/stdc++.h>
using namespace std;

class RangeTree { // 2D binary indexed tree
public:
	static const int MAXN = 1024;
    int A[MAXN][MAXN], R, C;
    vector< pair<int, int> > Q;
    void init(int R, int C) {
        this->R = R, this->C = C;
        memset(A, 0, sizeof(A));
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                modify(i, j, 1);
    }
    void modify(int x, int y, int val) {
        for (; x <= R; x += x&(-x)) {
            for (int i = y; i <= C; i += i&(-i)) 
                A[x][i] += val;
        }
    }
    int query(int x, int y) {
        int ret = 0;
        for (; x > 0; x -= x&-x)
            for (int i = y; i > 0; i -= i&(-i))
                ret += A[x][i];
        return ret;
	}
    int rectSum(int lx, int rx, int ly, int ry) {
        return query(rx, ry) - query(lx-1, ry) - query(rx, ly-1) + query(lx-1, ly-1);
    }
    void report(int x, int y) {
    	Q.push_back(make_pair(x, y));
	}
    void fetch(int lx, int rx, int ly, int ry, int tot) {
        if (tot == -1)	{ tot = rectSum(lx, rx, ly, ry); Q.clear(); }
        if (tot == 0)	return;
        if (lx == rx) {
            if (ly == ry) {
                modify(lx, ly, -1);
                report(lx, ly);
                return;
            }
            int cnt = rectSum(lx, rx, ly, (ly + ry)/2);
            if (cnt) 
                fetch(lx, rx, ly, (ly + ry)/2, cnt);
            if (cnt < tot) 
                fetch(lx, rx, (ly + ry)/2 + 1, ry, tot - cnt);
        }
        else {
            int cnt = rectSum(lx, (lx + rx)/2, ly, ry);
            if (cnt) 
                fetch(lx, (lx + rx)/2, ly, ry, cnt);
            if (cnt < tot)
                fetch((lx + rx)/2 + 1, rx, ly, ry, tot - cnt);
        }
    }
} tree;

int main() {
	int R, C, Q;
	int lx, ly, rx, ry;
	while (scanf("%d %d", &R, &C) == 2) {
		tree.init(R, C);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
			tree.fetch(lx, rx, ly, ry, -1);
			printf("%d", (int) tree.Q.size());
			for (auto &e : tree.Q)
				printf(" (%d, %d)", e.first, e.second);
			puts("");
		}
	}
	return 0;
}
