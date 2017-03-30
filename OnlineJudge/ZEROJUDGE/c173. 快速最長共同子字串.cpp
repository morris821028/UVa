#include <stdio.h>
#include <string.h>
#include <stdint.h>

static const int CHARSET = 4;
static const int MAXN = ((1<<16)>>6)+1;
static int c2i[128];
static const char i2c[CHARSET+1] = "ACGT";
void CIPR(char x[], char y[]) {
	const int n = strlen(y), m = strlen(x);
	const int o = (m>>6)+1;
	uint64_t R[CHARSET][MAXN] = {};
	uint64_t T[CHARSET][MAXN] = {};
	for (int i = 0; i < CHARSET; i++) {
		char c = i2c[i];
		uint64_t *r = R[i], *t = T[i];
		for (int j = 0; j < m; j++) {
			if (x[j] == c)
				r[j>>6] |= 1LL<<(j&63);
		}
		for (int j = 0; j < o; j++)
			t[j] = ~r[j];
	};
	uint64_t L[2][MAXN] = {};
	{
		for (int i = 0; i < (m>>6); i++)
			L[0][i] = 0xFFFFFFFFFFFFFFFFLL;
		for (int i = (m>>6)<<6; i < m; i++)
			L[0][i>>6] |= 1LL<<(i&63);
	}
		
	int ret = 0;
	for (int j = 0; j < n; j++) {
		uint64_t *p = L[j&1];
		uint64_t *q = L[(j&1)^1];
		const uint64_t *r = R[c2i[(int) y[j]]];
		const uint64_t *t = T[c2i[(int) y[j]]];
		uint64_t carry = 0;
		for (int k = 0; k < o; k++) {
			uint64_t a, b, sum;
	
			a = p[k], b = carry;
			sum = a + b;
			carry = sum < a;
		
			a = sum, b = p[k]&r[k];
			sum = a + b;
			carry |= sum < a;
			
			q[k] = sum | (p[k]&t[k]);
		}
		
		if (q[m>>6]>>(m&63)&1)
			q[m>>6] ^= 1LL<<(m&63), ret++;
	}
	printf("%d\n", ret);
}
int main() {
	for (int i = 0; i < CHARSET; i++)
        c2i[i2c[i]] = i;
	char sA[1<<16], sB[1<<16];
	while (scanf("%s%s", sA, sB) == 2) {
		CIPR(sA, sB);
	}
	return 0;
}

