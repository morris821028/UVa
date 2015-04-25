#include <stdio.h> 
#include <algorithm>
#include <string.h>
using namespace std;

#define MAXL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];

/*
	k bottles
	[min, max], ..., [k*min, k*max], [(k+1)*min, (k+1)*max]
	
	always have solution for [k*min, k*max], [(k+1)*min, (k+1)*max] 
	sat. (k+1)*min >= k*max 
			k >= min / (max - min)
	all interval cover each other after k-bottles.
*/

const int MAXN = 128;
int mx[MAXN], mn[MAXN];
int main() {
	int testcase, L, N;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &L, &N);
		L *= 1000;
		
		int lower_full = 0x3f3f3f3f; 
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &mn[i], &mx[i]);
			lower_full = min(lower_full, mn[i] * mn[i] / (mx[i] - mn[i]));
		}
		
		if (L >= lower_full) {
			puts("0");
			if (testcase)
				puts("");
			continue;
		}
		
		// limit L <= 4500 * 4500 / (4500 * 0.01)
		int A[4505] = {}, ret = 0;
		
		for (int i = 0; i < N; i++)
			for (int j = mn[i]; j <= mx[i]; j++)
				A[j] = 1;
			
		memset(mark, 0, sizeof(mark)); 
		SET(0);
		for (int i = 1; i <= 4500; i++) {
			if (A[i] == 0)
				continue;
			for (int j = i, k = 0; j <= L; j++, k++) {
				if (GET(k))
					SET(j), ret = max(ret, j);
			}
		}
		
		printf("%d\n", L - ret);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
2

10 2
4450 4500
725 750

10000 2
4450 4500
725 750
*/
