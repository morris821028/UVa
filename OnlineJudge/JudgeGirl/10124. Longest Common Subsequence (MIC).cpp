#include <stdio.h>
#include <string.h>
#include <omp.h>
#define MAXN 60005
#define CHARSET 4
typedef unsigned short uint16;
__declspec(align(256)) static char A[MAXN], B[MAXN];
__attribute__ ((target(mic)))
int lcs_len(const char *A, int na, const char *B, int nb, int dpf[]) {
	__declspec(align(256)) static int c2i[128] = {['A'] = 0, ['C'] = 1, ['G'] = 2, ['T'] = 3};
	__declspec(align(256)) static char i2c[CHARSET] = {'A', 'C', 'G', 'T'};
	__declspec(align(256)) static uint16 P[CHARSET][MAXN] = {};
	__declspec(align(256)) static uint16 dp[2][MAXN];
	A--, B--;
#pragma omp parallel for
#pragma ivdep
	for (int i = 0; i < CHARSET; i++) {
		P[i][0] = nb+1;
		for (int j = 1; j <= nb; j++)
			P[i][j] = (B[j] == i2c[i]) ? j-1 : P[i][j-1];
	}
	for (int i = 0; i < 2; i++) {
		memset(dp[i], 0, sizeof(uint16)*(nb+1));
		dp[i][nb+1] = -1;
	}
#pragma omp parallel 
	for (int i = 1; i <= na; i++) {
		uint16 *Pv = P[c2i[A[i]]];
		uint16 *dpIn = dp[i&1^1];
		uint16 *dpOut = dp[i&1];
#pragma omp for
#pragma ivdep
		for (int j = 1; j <= nb; j++) {
			uint16 t1 = dpIn[Pv[j]]+1;
			uint16 t2 = dpIn[j];
			dpOut[j] = t1 > t2 ? t1 : t2;
		}
	}
	for (int i = 0; i <= nb; i++) 
		dpf[i] = dp[na&1][i];
	return dpf[nb];
}
int main() {
	int dp[MAXN];
	while (scanf("%s %s", A, B) == 2) {
		int len;
#pragma offload target(mic) in(A[:]) in(B[:]) inout(len) 
		{
			int na = strlen(A);
			int nb = strlen(B);
			if (na > nb)
				len = lcs_len(A, na, B, nb, dp);
			else
				len = lcs_len(B, nb, A, na, dp);
		}
		printf("%d\n", len);
	}
	return 0;
}




