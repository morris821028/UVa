#include <stdio.h> 

int main() {
	int testcase;
	int c[4], d[4], q, v;
	scanf("%d", &testcase);
	while(testcase--) {
		for(int i = 0; i < 4; i++)
			scanf("%d", &c[i]);
		scanf("%d", &q);
		
		long long dp[100005] = {};
		dp[0] = 1;
		for(int i = 0; i < 4; i++)
			for(int j = c[i]; j < 100005; j++)
				dp[j] += dp[j-c[i]];
		while(q--) {
			for(int i = 0; i < 4; i++)
				scanf("%d", &d[i]);
			scanf("%d", &v);
			
			long long ret = 0;
			for(int i = (1<<4)-1; i >= 0; i--) {
				int cnt = 0, dv = v;
				for(int j = 0; j < 4; j++) {
					if((i>>j)&1)
						dv -= (d[j] + 1) * c[j], cnt++;
				}
				if(dv >= 0) {
					if(cnt&1)
						ret -= dp[dv];
					else
						ret += dp[dv];
				}
				
			}
			printf("%lld\n", ret);
		}
	}
	return 0;
}
/*
2
1 2 5 10 2
3 2 3 1 10
1000 2 2 2 900
10 20 30 40 1
100 100 100 100 101
*/
