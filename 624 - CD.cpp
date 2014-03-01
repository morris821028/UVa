#include <stdio.h>
#include <string.h>

int main() {
	int N, t, i, j;
	int cdTime[20], DP[20001], source[20001];
	while(scanf("%d %d", &N, &t) == 2) {
		for(i = 0; i < t; i++)
			scanf("%d", &cdTime[i]);
		memset(DP, 0, sizeof(DP));
		memset(source, 0, sizeof(source));
		DP[0] = 1, source[0] = 0;
		for(i = 0; i < t; i++) {
			for(j = N-cdTime[i]; j >= 0; j--) {
				if(DP[j+cdTime[i]] == 0 && DP[j] == 1) {
					DP[j+cdTime[i]] = 1;
					source[j+cdTime[i]] = cdTime[i];
				}
			}
		}
		int tmpN = N;
		while(tmpN >= 0 && DP[tmpN] == 0)	tmpN--;
		N = tmpN;
		int ans[20], aidx = 0;
		while(tmpN) {
			ans[aidx++] = source[tmpN];
			tmpN -= source[tmpN];
		}
		for(i = 0; i < aidx; i++)
			printf("%d ", ans[i]);
		printf("sum:%d\n", N);
	}
    return 0;
}
