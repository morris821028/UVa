#include <stdio.h> 
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, cases = 0;
	int N, M, A[16][2048];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &M);
		int ret = 0;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				scanf("%d", &A[j][i]);
		for(int i = 0; i < M; i++) {
			sort(A[i], A[i]+N);
			for(int j = 0; j < N; j++)
				ret += abs(j - A[i][j]);
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
