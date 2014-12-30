#include <stdio.h> 
#include <algorithm>
using namespace std;

int A[131072];
int pl[131072], pr[131072];
int greedy(int n, int m) {
	int l = A[0], r = m - A[0];
	pl[0] = l, pr[0] = 0;
	for (int i = 1; i < n; i++) {
		if (i&1) {
			pl[i] = min(l - pl[i-1], A[i]);
			pr[i] = A[i] - pl[i];
		} else {
			pr[i] = min(r - pr[i-1], A[i]);
			pl[i] = A[i] - pr[i];
		}
	}
	return pl[n-1] == 0;
}
int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		if (n == 1) {
			printf("%d\n", A[0]);
			continue;
		}
		int L = A[0], R = A[0], mid, ret;
		for (int i = 0; i < n; i++)
			R = max(R, A[i] * 3);
		for (int i = 0, j = n-1; i < n; j = i++)
			L = max(L, A[i] + A[j]);
		ret = L;
		if (n&1) {
			while (L <= R) {
				mid = (L + R)/2;
				if (greedy(n, mid))
					R = mid - 1, ret = mid;
				else
					L = mid + 1;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
