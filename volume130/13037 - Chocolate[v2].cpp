#include <bits/stdc++.h>
using namespace std;

int A[3][131072];
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n[3], x;
		for (int i = 0; i < 3; i++)
			scanf("%d", &n[i]);
			
		int m = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < n[i]; j++)
				scanf("%d", &A[i][j]);
			sort(A[i], A[i] + n[i]);
			n[i] = unique(A[i], A[i]+n[i]) - A[i];
		}
		
		int idx[3] = {}, ret[3][2] = {};
		while (true) {
			int mn = INT_MAX;
			for (int i = 0; i < 3; i++) {
				if (idx[i] < n[i])
					mn = min(mn, A[i][idx[i]]);
			}
			if (mn == INT_MAX)
				break;
				
			int mask = 0;
			for (int i = 0; i < 3; i++) {
				if (idx[i] < n[i] && A[i][idx[i]] == mn)
					mask |= 1<<i;
			}
			for (int i = 0; i < 3; i++) {
				if (mask == (1<<i))
					ret[i][0]++;
				if (mask == (((1<<3)-1)^(1<<i)))
					ret[i][1]++;
			}
			
			for (int i = 0; i < 3; i++) {
				if (idx[i] < n[i] && A[i][idx[i]] == mn)
					idx[i]++;
			}
		}
		printf("Case #%d:\n", ++cases);
		for (int i = 0; i < 3; i++)
			printf("%d %d\n", ret[i][0], ret[i][1]);
	}
	return 0;
}

