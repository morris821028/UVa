#include <stdio.h>
#include <algorithm>
using namespace std;

int n, A[131072];
int BIT[131072];

void modify(int x, int val) {
	while (x <= n) {
		BIT[x] += val;
		x += x&(-x);
	}
}
int query(int x) {
	int ret = 0;
	while (x) {
		ret += BIT[x];
		x -= x&(-x);
	}
	return ret;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n); 
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		
		for (int i = 0; i <= n; i++)
			BIT[i] = 0;
		long long ret = 0;
		for (int i = 0; i < n; i++) {
			ret += n - A[i];
			ret += n - i - 1;
			ret -= i - query(A[i]-1);
			modify(A[i], 1);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3
3
1 2 3
5
5 4 3 2 1
5
5 3 2 1 4
*/
