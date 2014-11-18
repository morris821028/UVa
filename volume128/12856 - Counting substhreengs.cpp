#include <stdio.h>
char s[1048576];
int main() {
	int mod3[32];
	for (int i = 0; i < 32; i++)
		mod3[i] = i%3;
	while (gets(s)) {
		long long ret = 0;
		for (int i = 0; s[i]; i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				int c[3] = {1, 0, 0}, sum = 0;
				while (s[i] >= '0' && s[i] <= '9') {
					sum += s[i] - '0';
					if (sum >= 3)	sum = mod3[sum];
					ret += c[sum], c[sum]++;
					i++;
				}
				i--;
			}
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
130a303
0000000000
icpc2014regional
*/
