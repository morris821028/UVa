#include <bits/stdc++.h>
#include <stdint.h>
#include "labeling.h"

// #define DEBUG

namespace {
	uint32_t seed = 0;
	void p_srand(uint32_t x) { seed = x;}
	uint32_t p_rand() {return seed = (seed*9301 + 49297);}
}

int main() {
	static const int MAXN = 16777216<<1;
	static const int MAXTOKEN = 500;
	static char s[MAXN];
	static int ret[MAXN];
	static char *cuStr;
	static int32_t *cuPos;
	int cases = 0;
	int n, m1, m2, seed;
	while (scanf("%d %d %d %d", &n, &m1, &m2, &seed) == 4) {
		assert(n <= MAXN);
		assert(m1 <= MAXTOKEN);
		p_srand(seed);
		cudaMalloc(&cuStr, sizeof(char)*n);
		cudaMalloc(&cuPos, sizeof(int32_t)*n);
		// random string
		{
			int pos = 0;
			for (; pos < n;) {
				int sp = pos == 0 ? p_rand()%m2 : p_rand()%m2+1;
				int cp = p_rand()%m1+1;
				for (; sp && pos < n; sp--, pos++)
					s[pos] = ' ';
				for (; cp && pos < n; cp--, pos++)
					s[pos] = 'a' + p_rand()%26;
			}
#ifdef DEBUG
			for (int i = 0; i < n; i++)
				putchar(s[i]);
			puts("");
#endif
			cudaMemcpy(cuStr, s, sizeof(char)*n, cudaMemcpyHostToDevice);
		}
		// test performance
		{
			clock_t st, ed;
			st = clock();
			const int ROUND = 2525;
			//const int ROUND = 1;
			for (int i = 0; i < ROUND; i++)	{
				labeling(cuStr, cuPos, n);
			}
			cudaMemcpy(ret, cuPos, sizeof(int32_t)*n, cudaMemcpyDeviceToHost);
			ed = clock() - st;
			fprintf(stderr, "It took average %lf seconds.\n", ((float) ed)/CLOCKS_PER_SEC/ROUND);
		}
		// check
		{
			clock_t st, ed;
			st = clock();
			uint32_t HEX = 0;
			for (int i = 0, sum = 0; i < n; i++) {
#ifdef DEBUG
				// printf("%d%c", ret[i], " \n"[i==n-1]);
				printf("%d ", ret[i]);
				if (i == n-1)
					puts("");
#endif
				if (s[i] > ' ')
					sum++;
				else
					sum = 0;
/*
				if (sum != ret[i]) {
					fprintf(stderr, "%c%c%c%c\n", s[i-2], s[i-1], s[i], s[i+1]);
					fprintf(stderr, "%d %d, %d %d, acc %d\n", ret[i], ret[i-1], i, i-1, sum);
				}
*/
				assert(sum == ret[i]);


				HEX ^= i*ret[i];
			}
			ed = clock() - st;
			fprintf(stderr, "Check task took %lf seconds.\n", ((float) ed)/CLOCKS_PER_SEC);
			printf("Case #%d: PASS %X\n", ++cases, HEX);
		}
		cudaFree(cuPos);
		cudaFree(cuStr);
	}

	return 0;
}


