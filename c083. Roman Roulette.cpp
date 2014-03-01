#include<stdio.h>
main() {
	int n, k;
	while(scanf("%d %d", &n, &k) == 2) {
		if(n == 0 && k == 0) break;
		if(n == 1) {
			puts("1");continue;
		}
		int p[101], a, now = 1, nowp = n, t, kill;
		for(a = 1; a <= n; a++)	p[a] = a;
		while(nowp > 1) {
			nowp--, t = 0;
			while(t < k) {
				if(now > n) now = 1;
				if(p[now]) t++;
				now++;
			}			
			kill = now-1;
			p[kill] = 0;/*kill*/
			t = 0;
			while(t < k) {
				if(now > n) now = 1;
				if(p[now]) t++;
				now++;
			}
			p[kill] = p[now-1];
			p[now-1] = 0;
			now = kill+1;

		}
		if(p[kill] == 1)
			puts("1");
		else
			printf("%d\n", n+2-p[kill]);
	}
	return 0;
}
