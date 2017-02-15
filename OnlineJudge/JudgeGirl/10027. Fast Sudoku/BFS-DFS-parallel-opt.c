#include <bits/stdc++.h>
using namespace std;
#define MAXN 65536
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0) 

int C[81][3];
int  N, Pidx;
short R[9][3] = {};
short P[2][MAXN*9][9][3], (*StoreP)[9][3];
int ida_dep;
short state[9][3];
int (*Cend)[3];
#pragma omp threadprivate(state)
#pragma omp threadprivate(Cend)
void IDA(int idx) {
    if (idx == ida_dep) {
        memcpy(StoreP[Pidx], state, sizeof(state)), Pidx++;
        return ;
    }
	short *x = state[C[idx][0]], *y = state[C[idx][1]];
    short *c = state[C[idx][2]];
	short p = ((1<<9)-1) ^ (x[0] | y[1] | c[2]);
	while (p) {
		short mask = p&(-p);
		p ^= mask;
		x[0] |= mask, y[1] |= mask, c[2] |= mask;
		IDA(idx+1);
		x[0] ^= mask, y[1] ^= mask, c[2] ^= mask;
	}
}
int dfs(int (*A)[3]) {
	if (unlikely(A == Cend))
		return 1;
	short *x = state[A[0][0]], *y = state[A[0][1]];
	short *c = state[A[0][2]];
	int sum = 0;
	short p = ((1<<9)-1) ^ (x[0] | y[1] | c[2]);
	while (p) {
		short mask = p&(-p);
		p ^= mask;
		x[0] |= mask, y[1] |= mask, c[2] |= mask;
		sum += dfs(A+1);
		x[0] ^= mask, y[1] ^= mask, c[2] ^= mask;
	}
	return sum;
}
int incomplete_bfs() {
	memcpy(P[0][0], R, sizeof(state)), Pidx = 1;
	int prev_ida_dep = 0;
	int storeFlag = 0;
	for (ida_dep = min(8, N); ida_dep <= N; ida_dep++) {
		int tmpPidx = Pidx;
		short (*PrevP)[9][3] = P[storeFlag];
		Pidx = 0, storeFlag ^= 1;
		StoreP = P[storeFlag];
		for (int i = 0; i < tmpPidx; i++) {
			memcpy(state, PrevP[i], sizeof(state));
			IDA(prev_ida_dep);
		}
		prev_ida_dep = ida_dep;
		if (Pidx >= MAXN)
			break;
	}
	if (ida_dep == N+1)
		return Pidx;
	int ret = 0;
	#pragma omp parallel for schedule(guided) reduction(+: ret) firstprivate(C) 
	for (int i = 0; i < Pidx; i++) {
		memcpy(state, P[storeFlag][i], sizeof(state));
		Cend = C + N;
		ret += dfs(C + ida_dep);
	}
	return ret;
}
int main() {
	int g[9][9], n = 9;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &g[i][j]);
	N = 0;
	memset(R, 0, sizeof(R));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i][j]) {
				g[i][j]--;
				R[i][0] |= 1<<g[i][j];
				R[j][1] |= 1<<g[i][j];
				R[i/3*3+j/3][2] |= 1<<g[i][j];
			} else {
				C[N][0] = i, C[N][1] = j, C[N][2] = i/3*3 + j/3;
				N++;
			}
		}
	}
	int ret = incomplete_bfs();
	printf("%d\n", ret);
	return 0;
}




