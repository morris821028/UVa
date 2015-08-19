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
	long long CPUcount[MAXC];
	long long MIN_COST = 0;
	multiset< pair<long long, int> > scheduler;
	for (int i = 0; i < C; i++)
		for (int j = 0; j < K[i]; j++)
			E[i][j] *= Re, T[i][j] *= Rt;
	for (int i = 0; i < C; i++) {
		long long mnv = LONG_LONG_MAX;
		for (int j = 0; j < K[i]; j++)
			mnv = min(mnv, T[i][j] + E[i][j]);
		scheduler.insert(make_pair(mnv, i));
		CPUcount[i] = 0;
	}
	sort(I, I + N);
	for (int i = N-1; i >= 0; i--) {	// reverse arrange
		int chCPU = -1;
		long long mnv = -1;
		pair<long long, int> t = *scheduler.begin();
		scheduler.erase(scheduler.begin());
		// accumulate cost
		chCPU = t.second, mnv = t.first;
		MIN_COST += mnv * I[i];
		// update CPU
		CPUcount[chCPU]++;
		mnv = LONG_LONG_MAX;
		for (int j = 0; j < K[chCPU]; j++)
			mnv = min(mnv, T[chCPU][j] * (CPUcount[chCPU]+1) + E[chCPU][j]);
		scheduler.insert(make_pair(mnv, chCPU));
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
