#include<stdio.h>
int gcd(int x, int y) {
	int tmp;
	while(x%y) {
		tmp = x, x = y, y = tmp%y;
	}
	return y;
}
int main() {
	long long K, a, b, c, d, m, i;
	scanf("%lld", &K);
	while(K--) {
		scanf("%lld %lld %lld", &m, &a, &b);
		if(gcd(m, a) != 1) {
			printf("No inverse, gcd(a,m)=%d\n", gcd(m, a));
			continue;
		}
		for(i = 1; i < m; i++) {
			if((a*i)%m == 1) {
				c = i;
				break;
			}
		}
		for(i = 1; i < m; i++) {
			if((a*i+b)%m == 0) {
				d = i;
				break;
			}
		}
		printf("%lld %lld\n", c, d);
	}
	return 0;
}
