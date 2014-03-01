#include<stdio.h>
main() {
	int T, n, a;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		int max = 0, pre, now, Ans;
		for(a = 0; a < n; a++) {
			scanf("%d", &now);
			if(a && now - pre > max)
				max = now - pre, Ans = a;
			pre = now;
		}
		printf("%d\n", Ans);
	}
	return 0;
}
