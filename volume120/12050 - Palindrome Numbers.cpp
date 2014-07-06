#include <stdio.h>

int main() {
	long long d[20], n;
	d[1] = d[2] = 9;
	for(int i = 3; i < 20; i += 2)
		d[i] = d[i+1] = d[i-1] * 10;
	while(scanf("%lld", &n) == 1 && n) {
		long long x10 = 1;
		char s[64];
		for(int i = 1; i < 20; i++) {
			if(n > d[i]) {
				n -= d[i];
			} else {
				n += x10 - 1;
				sprintf(s, "%lld", n);
				int j;
				for(j = 0; s[j]; j++)
					putchar(s[j]);
				if(i%2)	j--;
				for(j-- ; j >= 0; j--)
					putchar(s[j]);
				puts("");
				break;
			}
			if(i%2 == 0)
				x10 *= 10;
		}
	}
	return 0;
}
