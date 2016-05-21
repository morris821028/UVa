#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#define MAXN 128
#define LOOP_UNROLL 8
#define INF (1LL<<60)
int N, SZ[MAXN], SEED[MAXN];
long long dp[MAXN][MAXN] = {};
int argdp[MAXN][MAXN];
uint32_t* rand_gen(uint32_t c, int R, int C) {
	uint32_t *m = (uint32_t *) malloc(sizeof(uint32_t) * R*C);
	assert(m != NULL);
    uint32_t x = 2, n = R*C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            x = (x * x + c + i + j)%n;
            m[i*C + j] = x;
        }
    }
    return m;
}
uint32_t* multiplyAndDel(uint32_t *A, uint32_t *B, int r, int rc, int c) {
	uint32_t *C = (uint32_t *) malloc(sizeof(uint32_t) * r * c);
	uint32_t *tB = (uint32_t *) malloc(sizeof(uint32_t) * rc * c);
	assert(C != NULL);
	assert(tB != NULL);
	for (int i = 0; i < rc; i++) {
    	for (int j = 0; j < c; j++)
    		tB[j*rc + i] = B[i*c + j];
	}
	free(B);
    #pragma omp parallel for
    for (int i = r-1; i >= 0; i--) {
        for (int j = c-1; j >= 0; j--) {
            register uint32_t sum = 0;
            uint32_t *a = &A[i*rc], *b = &tB[j*rc];
            int k = rc;
            switch (k % LOOP_UNROLL) {
                case 0: do { sum += *a * *b, a++, b++;
                case 7: sum += *a * *b, a++, b++;
                case 6: sum += *a * *b, a++, b++;
                case 5: sum += *a * *b, a++, b++;
                case 4: sum += *a * *b, a++, b++;
                case 3: sum += *a * *b, a++, b++;
                case 2: sum += *a * *b, a++, b++;
                case 1: sum += *a * *b, a++, b++;
                } while ((k -= LOOP_UNROLL) > 0);
            }
            C[i*c + j] = sum;
        }
    }
    free(A), free(tB);
    return C;
}
uint32_t hash(uint32_t x) {
    return (x * 2654435761LU);
}
uint32_t signatureAndDel(uint32_t *A, int r, int c) {
    uint32_t h = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            h = hash(h + A[i*c + j]);
    }
    free(A);
    return h;
}
uint32_t* dfs(int l, int r, int *mR, int *mC) {
	if (l == r) {
		*mR = SZ[l], *mC = SZ[l+1];
		return rand_gen(SEED[l], *mR, *mC);
	}
	int split = argdp[l][r];
	int r1, r2, c1, c2;
	uint32_t *A, *B;
	A = dfs(l, split, &r1, &c1);
	B = dfs(split+1, r, &r2, &c2);
	assert(c1 == r2);
	*mR = r1, *mC = c2;
	return multiplyAndDel(A, B, r1, c1, c2);
}
int main() {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i <= N; i++)
			scanf("%d", &SZ[i]);
		for (int i = 0; i < N; i++)
			scanf("%d", &SEED[i]);
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j+i < N; j++) {
				int l = j, r = j+i;
				dp[l][r] = INF;
				for (int k = l; k < r; k++) {
					long long t = dp[l][k] + dp[k+1][r] + (long long) SZ[l] * SZ[k+1] * SZ[r+1];
					if (t < dp[l][r])
						dp[l][r] = t, argdp[l][r] = k;
				}
			}
		}
		int retR, retC;
		uint32_t *retM;
		uint32_t hval;
		retM = dfs(0, N-1, &retR, &retC);
		hval = signatureAndDel(retM, retR, retC);
		printf("%u\n", hval);
		
		long long test = 0;
		for (int i = 1; i < N; i++) {
			test += SZ[0] * SZ[i] * SZ[i+1];
		}
		fprintf(stderr, "best %lld, origin %lld, %lf\n", dp[0][N-1], test, dp[0][N-1]*1.f / test);
	}
	return 0;
}


