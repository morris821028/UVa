#include <stdio.h>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

int kThDiff(int A[], int n, long long m) {
	int mx = A[0], mn = A[0];
	for (int i = 0; i < n; i++)
		mx = max(mx, A[i]), mn = min(mn, A[i]);
	int l = 0, r = mx - mn, mid, ret;
	m = (long long) n * (n-1)/2 - m + 1;
	long long cnt;
	sort(A, A+n);

	while (l <= r) {
		mid = (l + r)/2;
		cnt = 0;
		for (int i = 0; i < n; i++) {
			int pos = (int)(upper_bound(A+i, A+n, A[i] + mid) - A);
			cnt += pos - i - 1;
		}
		if (cnt >= m)
			r = mid - 1, ret = mid;
		else
			l = mid + 1;
	} 
	return ret;
}
int main() {
	int n, m, A[131072];
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		printf("%d\n", kThDiff(A, n, m));
	}
	return 0;
}
/*
9 4
4 6 3 7 7 5 0 8 9 
5 1
7 4 2 5 2 
10 3
4 6 9 8 7 1 1 4 2 0 
9 20
3 8 6 2 1 9 6 7 2 
2 1
2 6 
4 4
0 9 0 0 
5 7
4 0 9 1 8 
11 30
1 2 1 6 1 0 7 7 5 2 5 
4 3
4 7 5 8 
2 1
1 6 
10 40
7 5 5 0 2 9 4 9 6 2 
3 2
6 8 7 
10 28
3 5 0 8 1 1 7 9 2 1 
9 3
6 7 1 2 0 8 5 1 0 
8 22
0 3 1 9 1 8 4 7 
11 20
2 3 0 4 7 1 7 6 2 2 1 
3 1
7 3 9 
4 2
9 2 4 5 
10 39
6 5 2 3 6 1 1 8 1 9 
8 7
4 9 7 2 1 6 3 2 
*/
