#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 105
#define MAXBN ((MAXN+63)>>6)
static uint64_t S[MAXN];
static uint64_t G[MAXN][MAXBN];  // G[i] -> j
static uint64_t U[MAXBN], T[MAXBN];

int dfs(int K) {
    if (K == 0)
        return 1;
    if (U[0]) {
	 	if (__builtin_popcountll(U[0]) + __builtin_popcountll(U[1]) < K)
        	return 0;
        uint64_t pos = U[0]&(-U[0]);
        uint64_t m[2] = {U[0], U[1]};
        int t = __builtin_ctzll(pos);
        T[0] ^= pos;
        U[0] &= G[t][0], U[1] &= G[t][1];
        if (dfs(K-1))   return 1;
        U[0] = m[0]^pos, U[1] = m[1];
        T[0] ^= pos;
        if (dfs(K))     return 1;
        U[0] ^= pos;
    } else {
		if (__builtin_popcountll(U[1]) < K)
        	return 0;
        uint64_t pos = U[1]&(-U[1]);
        uint64_t m = U[1];
        int t = __builtin_ctzll(pos)+64;
        T[1] ^= pos;
        U[1] &= G[t][1];
        if (dfs(K-1))   return 1;
        U[1] = m^pos;
        T[1] ^= pos;
        if (dfs(K))     return 1;
        U[1] ^= pos;
    }
    return 0;
}
int main() {
    int N, K;
    while (scanf("%d %d", &N, &K) == 2) {
        for (int i = 0; i < N; i++) {
            int m, x;
            int64_t mask = 0;
            scanf("%d", &m);
            for (int j = 0; j < m; j++)
                scanf("%d", &x), mask |= 1LLU<<x;
            S[i] = mask;
        }
        
        for (int i = 0; i < N; i++) {
            memset(G[i], 0, sizeof(G[i]));
            for (int j = i+1; j < N; j++) {
                if (S[i]&S[j])
                    continue;
                G[i][j>>6] |= 1LLU<<(j&63);
            }
        }
        
        memset(U, 0, sizeof(U));
        memset(T, 0, sizeof(T));
        for (int i = 0; i < N; i++)
            U[i>>6] |= 1LLU<<(i&63);
        
        int ret = dfs(K);
        if (!ret) {
            puts("no solution");
        } else {
            for (int i = 0; i < N; i++) {
                if ((T[i>>6]>>(i&63))&1)
                    printf("%d\n", i);
            }
        }
    }
    return 0;
}

