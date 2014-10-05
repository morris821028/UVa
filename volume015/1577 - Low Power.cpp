#include <stdio.h> 
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
int A[1048576];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		int N = 2 * n * m; 
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		sort(A, A+N);
		int l = A[1] - A[0], r = A[N-1] - A[0], mid;
		int ret = l;
		while (l <= r) {
			mid = (l + r)/2;
			int cnt = 0, used = 0;
			for (int i = 0; i < N - 1; i++) {
				if (A[i+1] - A[i] <= mid) {
					cnt++, i++, used += 2;
				} else {
					used++;
				}
				if (used > cnt * 2 * m || cnt == n)
					break;
			}
			if (cnt == n)
				ret = mid, r = mid - 1;
			else
				l = mid + 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2 3
1 2 3 4 5 6 7 8 9 10 11 12
2 2
3 1 3 3 3 3 3 3
*/
