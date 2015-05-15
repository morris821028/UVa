#include <stdio.h> 
#include <algorithm>
using namespace std;

const int MAXN = 131072;
int A[MAXN];
int main() {
	int testcase, N, T, Q, K;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &T);
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		sort(A, A+N);
		
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d", &K);
			int ret = 0, t = T;
			for (int j = N-1; j >= 0; j--) {
				if (A[j] <= t)
					ret++, t = t - K;
			}
			printf("%d\n", ret);
		}
	}
	return 0;
}
