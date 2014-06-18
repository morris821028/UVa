#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
	int testcase;
	int n, A[80];
	int i, j, k;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		sort(A, A+n, greater<int>());
		int ret = 0xfffffff;
		for(i = 0; i < A[0]; i++) {
			int l = i, r = A[0] - i - 1;
			int cost = A[0];
			for(j = 1; j < n; j++) {
				int cl, cr; // cover
				cl = min(l, A[j] - 1);
				cr = min(r, A[j] - 1);
				if(cl > cr)
					l = A[j] - cl - 1, cost += l + 1;
				else
					r = A[j] - cr - 1, cost += r + 1;
			}
			ret = min(ret, cost);
		}
		printf("%d\n", ret);
	}
	return 0;
}
