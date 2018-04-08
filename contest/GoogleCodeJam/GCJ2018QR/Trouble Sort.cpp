#include <bits/stdc++.h>
using namespace std;
const int MAXN = 131072;
int A[MAXN], D[MAXN];
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		vector<int> B, C;
		B.reserve(n/2+1);
		C.reserve(n/2+1);
		for (int i = 0; i < n; i++) {
			if (i%2)
				C.push_back(A[i]);
			else
				B.push_back(A[i]);
		}

		sort(B.begin(), B.end());
		sort(C.begin(), C.end());

		for (int i = 0, b = 0, c = 0; i < n; i++) {
			if (i%2)
				D[i] = C[c++];
			else
				D[i] = B[b++];
		}

		int diff = -1;
		sort(A, A+n);
		for (int i = 0; i < n; i++) {
			if (A[i] != D[i]) {
				diff = i;
				break;
			}
		}
		
		printf("Case #%d: ", ++cases);
		if (diff < 0)
			puts("OK");
		else
			printf("%d\n", diff);
	}
	return 0;
}
