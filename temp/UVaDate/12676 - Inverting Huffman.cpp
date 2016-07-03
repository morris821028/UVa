#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n, x;
	while (scanf("%d", &n) == 1) {
		vector<long long> A[64]; // A[bit_length]
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			A[x].push_back(-1);
		}
		
		long long ret = 0, mx = 1;
		for (int i = n; i >= 1; i--) {
			for (int j = 0; j < A[i].size(); j++) {
				if (A[i][j] == -1)
					A[i][j] = mx, ret += A[i][j];
			}
			for (int j = 0; j < A[i].size(); j += 2) {
				A[i-1].push_back(A[i][j] + A[i][j+1]);
				mx = max(mx, A[i][j]);
				mx = max(mx, A[i][j+1]);
			}
		}
		printf("%lld\n", ret);
	} 
	return 0;
}

/*
2
1 1
4
2 2 2 2
10
8 2 4 7 5 1 6 9 3 9
8
2 2 3 3 4 4 4 4
5
1 3 3 3 3
*/
