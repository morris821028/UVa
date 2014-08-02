#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int n, q, k;
	while(scanf("%d %d", &n, &q) == 2 && n) {
		int mask[128] = {}, x;
		for(int i = 0; i < n; i++) {
			scanf("%d", &k);
			while(k--) {
				scanf("%d", &x), x--;
				mask[i] |= 1<<x;
			}
		}
		int dp[1<<16] = {};
		for(int i = (1<<16)-1; i >= 0; i--)
			dp[i] = 0x3f3f3f3f;
		dp[0] = 0;
		for(int i = 0; i < (1<<16); i++) {
			if(dp[i] == 0x3f3f3f3f)
				continue;
			for(int j = 0; j < n; j++) {
				int v = i|mask[j];
				dp[v] = min(dp[v], dp[i] + 1);
			}
		}
		for(int i = 0; i < q; i++) {
			scanf("%d", &k);
			int mm = 0;
			while(k--) {
				scanf("%d", &x), x--;
				mm |= 1<<x;
			}
			printf("%d%c", dp[mm] == 0x3f3f3f3f ? 0 : dp[mm], i == q-1 ? '\n' : ' ');
		}
	} 
	return 0;
}
