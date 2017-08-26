#include <bits/stdc++.h>
using namespace std;

struct Plane {
	int l, r, p;
	Plane(int l=0, int r=0, int p=0):
		l(l), r(r), p(p) {}
	bool operator<(const Plane &x) const {
		return l < x.l;
	}
};
int main() {
	int n, cases = 0;
	while (scanf("%d", &n) == 1) {
		Plane A[4096];
		for (int i = 0; i < n; i++) {
			int l, r, p;
			scanf("%*s %d %d %d", &l, &r, &p);
			r += l;
			A[i] = Plane(l, r, p);
		}
		
		sort(A, A+n);
		int ret = 0;
		set< pair<int, int> > S;
		for (int i = 0, prev = 0; i < n; i++) {
			while (!S.empty() && S.begin()->first <= A[i].l)
				prev = max(prev, S.begin()->second), S.erase(S.begin());
			ret = max(ret, prev + A[i].p);
			S.insert(make_pair(A[i].r, prev + A[i].p));
		}
		if (cases++)
			puts("");
		printf("%d\n", ret);
	}
	return 0;
}
