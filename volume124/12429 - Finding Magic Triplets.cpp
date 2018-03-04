#include <bits/stdc++.h> 
using namespace std;
const int MAXK = 100005;
int tree[MAXK];
/*
	a + b^2 = c^3 mod k, 1 <= a <= b <= c
	sweep line algorithm
	add A[c^3%k]++ in decreasing order.
	query b = c to count (a, c) during adding c
	a%k in [1, b%k], # of each value = b/k+1
	a%k in [b%k+1, k], # of each value = b/k
	count (b/k+1)*sum(A[1, b%k]) + (b/k)*sum(A[b%k+1, k])
			= (b/k)*sum(A[1, k]) + sum(A[1, b%k])
*/
void add(int x, int k) {
	while (x <= k)
		tree[x]++, x += x&(-x);
}
int sum(int x) {
	int ret = 0;
	while (x)
		ret += tree[x], x -= x&(-x);
	return ret;
}
int brute(int b, int n, int k) {
	int ret = 0;
	for (int a = 1; a <= b; a++) {
		for (int c = b; c <= n; c++) {
			if ((a+b*b-c*c*c)%k == 0)
				ret++;
		}
	}
	return ret;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, k;
		scanf("%d %d", &n, &k);
		memset(tree, 0, sizeof(tree[0])*(k+1));
		int64_t ret = 0, tot = 0;
		for (int c = n; c > 0; c--) {
			int modc = ((int64_t) c*c*c % k)+1;
			add(modc, k+1), tot++;
			int modb = ((int64_t) c*c % k)+1;
			int64_t tmp = 0;
			tmp += (c/k) * tot;
			int l = modb, r = (modb + c%k);
			if (l == r) {
			} else if (r <= k) {
				tmp += sum(r)-sum(l);
			} else {
				tmp += tot-sum(l)+sum(r-k);
			}
			ret += tmp;
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
1
10  7
*/
