#include <bits/stdc++.h> 
using namespace std;

// Stern-Brocot tree
int main() {
	int p, q, n;
	while (scanf("%d %d %d", &p, &q, &n) == 3) {
		int64_t p1 = 0, q1 = 1, p2 = 1, q2 = 1;
		int on = n;
		// 0/1, 1/1
		while (true) {
			if (p1 == p && q1 == q)
				break;
			if (p2 == p && q2 == q)
				break;
			int64_t pm = p1+p2, qm = q1+q2;
			if (pm == p && qm == q)
				break;
			if ((double) p*qm <= (double) q*pm) {
				p2 = pm, q2 = qm;
			} else {
				p1 = pm, q1 = qm;
			}
		}
//		printf("%lld/%lld %lld/%lld\n", p1, q1, p2, q2);
		set<pair<int64_t, int64_t>> ret;
		if ((p2 != p || q2 != q) && n)
			ret.insert({p2, q2}), n--, p2 += p, q2 += q;
		if ((p1 != p || q1 != q) && n)
			ret.insert({p1, q1}), n--, p1 += p, q1 += q;

		for (int i = 0; ret.size() <= on; i++) {
			if ((p2 != p || q2 != q) && ret.count({p2, q2}) == 0) {
				ret.insert({p2, q2});
				p2 += p, q2 += q, n--;
			}
			if ((p1 != p || q1 != q) && ret.count({p1, q1}) == 0) {
				ret.insert({p1, q1});
				p1 += p, q1 += q, n--;
			}
		}

		for (auto e : ret) {
			on--;
			printf("M(%lld/%lld)%c", e.first, e.second, " \n"[on==0]);
			if (on == 0)
				break;
		}
	}
	return 0;
}
/*
2  5  4
2  3  3
0  1  2
1  1  2
1  2  5
*/
