#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
unordered_set<int64_t> S;
int mxdep = 0;
int64_t ret[MAXN], tmp[MAXN];
inline int64_t __llgcd(int64_t a, int64_t b) {
	if (a < INT_MAX && b < INT_MAX)
		return __gcd(a, b);
	int64_t t;
	while (a%b)
		t = a, a = b, b = t%b;
	return b;
}
int64_t lower(int64_t a, int64_t b) {
	return b/a+1;
}
void store() {
	for (int i = mxdep; i >= 0; i--) {
		if (ret[i] == tmp[i])
			continue;
		if (ret[i] < tmp[i])
			return;
		memcpy(ret, tmp, sizeof(ret[0])*(mxdep+1));
		return;
	}
}
int dfs(int dep, int64_t a, int64_t b, int64_t l) {
	if (dep == mxdep) {
		if (b%a || S.count(b/a))
			return 0;
		tmp[dep] = b/a;
		store();
		return 1;
	}
	int has = 0;
	for (int64_t i = max(l, lower(a, b)); ; i++) {
		if (b*(mxdep+1-dep) <= i*a)
			break;
		if (S.count(i))
			continue;
		tmp[dep] = i;
		int64_t nb = b*i;
		int64_t na = a*i-b;
		int64_t g = __llgcd(na, nb);
		if (dfs(dep+1, na/g, nb/g, i+1))
			has = 1;
	}
	return has;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int64_t a, b, x;
		int k;
		scanf("%lld %lld %d", &a, &b, &k);
		S.clear();
		for (int i = 0; i < k; i++) {
			scanf("%lld", &x);
			S.insert(x);
		}
		for (mxdep = 0; ; mxdep++) {
			memset(ret, 0x3f, sizeof(ret));
			if (dfs(0, a, b, lower(a, b)))
				break;
		}
		printf("Case %d: ", ++cases);
		printf("%lld/%lld=", a, b);
		for (int i = 0; i <= mxdep; i++)
			printf("1/%lld%c", ret[i], "+\n"[i==mxdep]);
	}
	return 0;
}
/*
5
2  3  0
19  45  0
2  3  1  2
5  121  0
5  121  1  33
*/
