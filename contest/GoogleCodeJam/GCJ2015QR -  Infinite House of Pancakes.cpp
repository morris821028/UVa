#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
int P[MAXN], N, A[MAXN];

int main()  {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", &P[i]);
			
		sort(P, P + N);
		int ret = 0x3f3f3f3f;
		for (int i = 0; i <= 1000; i++) { // special
			for (int j = 1; i+j < ret && j <= 1000; j++) { // normal
					
				int cnt = 0;
				for (int k = 0; k < N && cnt <= i; k++) {
					if (P[k] > j) {
						int d = P[k] / j - (P[k] % j == 0);
						cnt += d;
					}
				}
				if (cnt <= i) {
					ret = min(ret, i + j);
//					printf("%d %d\n", i, j);
				}
			}
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
3
1
3
4
1 2 1 2
1
4
*/
