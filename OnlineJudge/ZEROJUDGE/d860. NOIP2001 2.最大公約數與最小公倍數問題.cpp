#include<stdio.h>
#include<math.h>
int gcd(int x, int y) {
	int t;
	while(x%y) {
		t = x, x = y, y = t%y;
	}
	return y;
}
main() {
	int x, y;
	while(scanf("%d %d", &x, &y) == 2) {
		long long n = x * y;
		int a, p, q, Ans = 0;
		for(a = x; a <= y; a++) {
			if(n%a == 0) {
				p = a, q = n /a;
				if(gcd(p,q) == x)	Ans++;
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
