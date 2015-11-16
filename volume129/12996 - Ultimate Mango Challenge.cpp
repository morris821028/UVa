#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, L;
		int A[20], B[20], S = 0, ret = 1;
		scanf("%d %d", &N, &L);
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]), S += A[i];
		for (int i = 0; i < N; i++)
			scanf("%d", &B[i]), ret &= A[i] <= B[i];
		ret &= S <= L;
		printf("Case %d: %s\n", ++cases, ret ? "Yes" : "No");
	}
	return 0;
}
/*
3
3 5
1 2 3
1 3 3
3 6
1 2 3
1 3 2
3 6
1 2 3
3 3 3
*/

