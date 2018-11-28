#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int MAXQ = 500005;
struct Planet {
	int64_t x, y, z;
	Planet() {}
	Planet(int x, int y, int z):
		x(x), y(y), z(z) {}
	int64_t dist2(const Planet &p) const {
		return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) + (z-p.z)*(z-p.z);
	}
} P[MAXN];

struct Query {
	int64_t d1, d2;
	int i;
	Query() {}
	Query(int64_t r1, int64_t r2, int x) {
		d1 = r1*r1, d2 = r2*r2, i = x;
	}
	bool operator<(const Query &q) const {
		if (d1 != q.d1)
			return d1 < q.d1;
		return d2 < q.d2;
	}
} Q[MAXQ];

struct BIT {
	int tree[MAXN], n;
	void init(int n) {
		this->n = n;
		memset(tree, 0, sizeof(tree[0])*(n+1));
	}
	int sum(int x) {
		int ret = 0;
		while (x)
			ret += tree[x], x -= x&(-x);
		return ret;
	}
	void inc(int x) {
		while (x <= n)
			tree[x]++, x += x&(-x);
	}
} tree;

int main() {
	int n, m;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			int32_t x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			P[i] = Planet(x, y, z);
		}

		vector<int64_t> D1, D2;
		vector<pair<int64_t, int64_t>> D;
		D1.reserve(n-2), D2.reserve(n-2);
		for (int i = 2; i < n; i++) {
			int64_t d1 = P[0].dist2(P[i]);
			int64_t d2 = P[1].dist2(P[i]);
			D1.push_back(d1), D2.push_back(d2);
			D.push_back({d1, d2});
		}

		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int r1, r2;
			scanf("%d %d", &r1, &r2);
			Q[i] = Query(r1, r2, i);
		}

		static int ret[MAXQ];
		sort(D1.begin(), D1.end());
		sort(D2.begin(), D2.end());

		for (int i = 0; i < m; i++) {
			int c1, c2;
			c1 = upper_bound(D1.begin(), D1.end(), Q[i].d1) - D1.begin();
			c2 = upper_bound(D2.begin(), D2.end(), Q[i].d2) - D2.begin();
			ret[i] = c1 + c2;
		}

		sort(D.begin(), D.end());
		sort(Q, Q+m);

		D2.resize(unique(D2.begin(), D2.end())-D2.begin());
		tree.init(D2.size());

		for (int i = 0, j = 0; i < m; i++) {
			while (j < D.size() && D[j].first <= Q[i].d1) {
				int p = upper_bound(D2.begin(), D2.end(), D[j].second) - D2.begin();
				tree.inc(p);
				j++;
			}
			int p = upper_bound(D2.begin(), D2.end(), Q[i].d2) - D2.begin();
			ret[Q[i].i] -= tree.sum(p);
		}

		for (int i = 0; i < m; i++)
			printf("%d\n", ret[i]);
	}
	return 0;
}
/*
5
1 1 1
5 5 5
2 2 2
3 3 3
4 4 4
4
1 1
2 1
2 2
6 6
*/
