#include <stdio.h>
#include <stdlib.h>
int mark[32768], Prime[32768], Pt = 0;
void sieve() {
	int i, j;
	for(i = 2; i < 32768; i++) {
		if(mark[i] == 0) {
			Prime[Pt++] = i;
			for(j = 2; i*j < 32768; j++)
				mark[i*j] = 1;
		}
	}
}
int main() {
	sieve();
	int n;
	while(scanf("%d", &n) == 1 && n) {
		int i, x, y, ans = 0;
		for(i = 0; Prime[i] < n; i++) {
			x = Prime[i], y = n-x;
			if(x > y)	break;
			if(mark[y] == 0)	ans++;
		}
		printf("%d\n", ans);
	}
    return 0;
}
