#include<stdio.h>
#include<stdlib.h>
main() {
	int i, j;
	while(scanf("%d %d", &i, &j) == 2) {
		long long t, Ans = 0;
		while(1) {
			t = 2;
			while(t < i || t < j) {
				t *= 2;
			}
			if(i == 1 && j == 1) {Ans++;break;}
			if(t / 2 >= i && t / 2 < j)
				Ans += t*t / 2, j -= t / 2;
			else if(t / 2 < i && t / 2 < j)
				Ans += t*t / 4, i -= t / 2, j -= t / 2;
			else
				Ans += t*t / 4 * 3, i -= t / 2;
		}
		printf("%lld\n", Ans);
	}
	return 0;
}
