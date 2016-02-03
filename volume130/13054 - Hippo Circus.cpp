#include <bits/stdc++.h>
using namespace std;

int A[131072], used[131072];
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, H, Ta, Tb;
		scanf("%d %d %d %d", &N, &H, &Ta, &Tb);
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		sort(A, A+N);
		
		long long ret = 0;
		memset(used, 0, sizeof(used));
		int r = N-1;
		for (int i = 0; i < N; i++) {
			if (used[i] == 1)	continue;
			while (r > i && (A[i] + A[r] >= H || used[r] == 1))
				r--;
			if (r > i && A[i] + A[r] < H && used[r] == 0 && Ta+Ta > Tb) {
				ret += Tb;
				used[r] = used[i] = 1;
			} else {
				ret += Ta;
				used[i] = 1;
			}
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}

