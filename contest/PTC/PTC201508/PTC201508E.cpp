#include <stdio.h> 
#include <set>
#include <limits.h>
#include <algorithm>
using namespace std;
const int MAXC = 5;
const int MAXK = 10;
const int MAXN = 100005;
int C, K[MAXK];
long long E[MAXC][MAXK], T[MAXC][MAXK], I[MAXN];
int N, Re, Rt;	
void schedule() {
	for (int i = 0; i < C; i++)
		for (int j = 0; j < K[i]; j++)
			E[i][j] *= Re, T[i][j] *= Rt;
	sort(I, I + N);
	long long CPUcount[MAXC] = {};
	long long MIN_COST = 0;
	for (int i = N-1; i >= 0; i--) {	// reverse arrange
		long long mnv = -1;
		int chCPU = -1;
		for (int j = 0; j < C; j++) {
			for (int k = 0; k < K[j]; k++) {
				if (chCPU == -1 || T[j][k]*(CPUcount[j]+1) + E[j][k] < mnv) {
					mnv = T[j][k]*(CPUcount[j]+1) + E[j][k];
					chCPU = j;
				}
			}				
		}
		MIN_COST += mnv * I[i];
		CPUcount[chCPU]++;
	}
	printf("%lld\n", MIN_COST);
}
int main() {
	while (scanf("%d", &C) == 1) {
		for (int i = 0; i < C; i++) {
			scanf("%d", &K[i]);
			for (int j = 0; j < K[i]; j++)
				scanf("%lld", &E[i][j]);
			for (int j = 0; j < K[i]; j++)
				scanf("%lld", &T[i][j]);
		}
		scanf("%d %d %d", &N, &Re, &Rt);
		for (int i = 0; i < N; i++)
			scanf("%lld", &I[i]);
		schedule();
	}
	return 0;
}
/*
1
3
1 10 80
10 5 3

3 1 1
5
4
2

2
3
1 10 80
10 5 3
3
1 10 80
10 5 3

3 1 1
5
4
2
*/
