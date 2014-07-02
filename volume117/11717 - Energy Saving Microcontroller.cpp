#include <stdio.h>

int main() {
	int N, I, K, testcase, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &N, &I, &K);
		int x, ignore = 0, active = 0, t = 0;
		while(N--) {
			scanf("%d", &x);
			if(x < t)
				ignore++;
			else if(x >= t + I)
				active++, t = x + K;
			if(x > t)
				t = x;
		}
		printf("Case %d: %d %d\n", ++cases, active, ignore);
	}
	return 0;
} 
