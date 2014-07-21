#include <stdio.h>

int main() {
	int n, cases = 0;
	while(scanf("%d", &n) == 1 && n) {
		printf("Case %d:", ++cases);
		if(n%4 != 3 && n%4 != 0)
			puts(" -1");
		else {
			int d = (n+1)/4*2-1 + (n%4 == 0);
			int sum = 1 + d;
			printf(" 1 %d", sum);
			for(int i = 1, j = 0; i < n; i++) {
				if(i == d)
					continue;
				if(j%2 != d%2)
					sum += i;
				else
					sum -= i;
				printf(" %d", sum);
				j++;
			}
			puts("");
		}
	}
	return 0;
}
