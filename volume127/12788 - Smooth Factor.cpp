#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n, A[100005], B[100005];
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		int cnt = 1, m = 0;
		A[n] = -0x3f3f3f3f;
		for (int i = 1; i <= n; i++) {
			if (A[i] >= A[i-1])
				cnt++;
			else {
				B[m++] = cnt;
				cnt = 1;
			}
		}
		int ret = B[0];
		for (int i = 1; i < m; i++)
			ret = max(ret, B[i] + B[i-1]);
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
1 2 3
1
0
8
1 2 1 2 1 2 3 1
4
1 -10 -100 -100
*/
