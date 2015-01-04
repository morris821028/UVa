#include <stdio.h> 
#include <algorithm>
#include <vector>
using namespace std;

int path[105];
long long llgcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
int dfs(int idx, int n, int i) {
	if (n == 0) {
		long long a = 0, b = 1;
		for (int i = 0; i < idx; i++) {
//			printf("%d ", path[i]);
			long long ta, tb;
			tb = b * path[i] / llgcd(b, path[i]);
			ta = a * (tb / b) + tb / path[i];
			a = ta, b = tb;
			ta = llgcd(a, b);
			a /= ta, b /= ta;
		}
//		puts("");
//		printf("%lld / %lld\n", a, b);
//		getchar();
		if (a == 1 && b == 1)
			return 1;
		return 0;
	}
	for (; i <= n; i++) {
		path[idx] = i;
		if (dfs(idx+1, n - i, i+1))
			return 1;
	}
	return 0;
}
int main() {
	vector<int> A;
	A.push_back(1);
	for (int i = 2; i <= 77; i++)
		if (dfs(0, i, 2))
			A.push_back(i);
	int testcase, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &x, &y);
		if (x > y)	swap(x, y);
		int ret = 0;
		for (int i = 0; i < A.size(); i++)
			ret += x <= A[i] && A[i] <= y;
		int lx = 78, rx = 0x3f3f3f3f;
		if (y >= lx)
			ret +=  min(rx, y) - max(lx, x) + 1;
		printf("%d\n", ret);
	} 
	return 0;
}
