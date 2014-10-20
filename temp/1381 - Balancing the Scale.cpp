#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int cases = 0;
	int A[16], B[4];
	while (scanf("%d", &A[0]) == 1 && A[0]) {
		for (int i = 1; i < 16; i++)
			scanf("%d", &A[i]);
		sort(A, A + 16);
		int C[1<<16] = {};
		vector<int> D[32767];
		for (int i = (1<<16) - 1; i >= 0; i--) {
			if (__builtin_popcount(i) == 4) {
				int n = 0;
				for (int j = 0; j < 16; j++)
					if ((i>>j)&1)	B[n++] = A[j];
				do {
					int sum = B[0] + B[1] * 2 + B[2] * 3 + B[3] * 4;
					for (int j = 0; j < D[sum].size(); j++) {
						if (D[sum][j]&i)	continue;
						C[D[sum][j]|i]++;
					}
					D[sum].push_back(i);
				} while (next_permutation(B, B + 4));
			}
		}
		int ret = 0;
		for (int i = (1<<16) - 1; i >= 0; i--)
			ret += C[i] * C[((1<<16)-1) ^ i];
		printf("Case %d: %d\n", ++cases, ret/2);
	}
	return 0;
}
