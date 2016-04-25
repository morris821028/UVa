#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#define MAXN 65536
 
int C[81][2], N;
int R[9][3] = {};
int threadcount = 0;
#pragma omp threadprivate(threadcount)
void dfs_serial(int idx, int state[][3]) {
    if (idx == N) {
    	threadcount++;
        return ;
    }
    int x = C[idx][0], y = C[idx][1];
    int c = x/3*3 + y/3;
    for (int i = 0; i < 9; i++) 
	{
        int mask = 1<<i;
        if ((state[x][0]&mask) || (state[y][1]&mask) ||
                (state[c][2]&mask)) 
            continue;
        state[x][0] |= mask;
        state[y][1] |= mask;
        state[c][2] |= mask;
		dfs_serial(idx+1, state);
        state[c][2] ^= mask;
        state[y][1] ^= mask;
        state[x][0] ^= mask;
    }
}
void dfs(int idx, int state[][3]) {
    if (idx == N) {
    	threadcount++;
        return ;
    }
    int x = C[idx][0], y = C[idx][1];
    int c = x/3*3 + y/3;
    for (int i = 0; i < 9; i++) 
    #pragma omp task untied
	{
        int mask = 1<<i;
        if ((state[x][0]&mask) || (state[y][1]&mask) ||
                (state[c][2]&mask)) {
                	
		} else {
	        int S[9][3] = {};
			memcpy(S, state, sizeof(S));
//			int (*S)[3] = malloc(sizeof(int)*9*3);
//			memcpy(S, state, sizeof(int)*9*3);
			S[x][0] |= mask;
	        S[y][1] |= mask;
	        S[c][2] |= mask;
			if (idx >= 6) {
	    		dfs_serial(idx+1, S);
	    	} else {
		        dfs(idx+1, S);
			}
    	}
    }
    #pragma omp taskwait
}
int incomplete_bfs() {
	int ret = 0;
	#pragma omp parallel
	{
		#pragma omp single
		{
			dfs(0, R);
		}
		#pragma omp critical
			ret += threadcount;
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
                 C[N][0] = i, C[N][1] = j;
                 N++;
             }
         }
     }
    int ret = incomplete_bfs();
    printf("%d\n", ret);
    return 0;
}
