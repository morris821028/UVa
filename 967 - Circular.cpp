#include <stdio.h>
#include <string.h>
#include <math.h>

int DP[1000001] = {};
int Prime[5500], Pt;
void sieve() {
	Pt = 0;
	char mark[50000] = {};
	int i, j;
	for(i = 2; i < 50000; i++) {
		if(mark[i] == 0) {
			Prime[Pt++] = i;
			for(j = 2; i*j < 50000; j++)
				mark[i*j] = 1;
		}
	}
}
int judgePrime(int n) {
	static int i, sqr;
	sqr = (int)sqrt(n);
	for(i = 0; Prime[i] <= sqr && i < Pt; i++)
		if(n%Prime[i] == 0)
			return 0;
	return 1;
}
void build() {
	char str[20];
	int i, j, k, n, len, tmp;
	for(i = 100; i <= 1000000; i++) {
		DP[i] += DP[i-1];
		sprintf(str, "%d", i);
		len = strlen(str);
		for(j = 0; j < len; j++) {
			sscanf(str, "%d", &n);
			if(judgePrime(n) == 0)
				break;
			tmp = str[0];
			for(k = 1; k < len; k++)
				str[k-1] = str[k];
			str[len-1] = tmp;
		}
		if(j == len) {
			DP[i]++;
		}
	}
}
int main() {
	sieve();
	build();
	int a, b, sum;
	while(scanf("%d", &a) == 1 && a > 0) {
		scanf("%d", &b);
		sum = DP[b] - DP[a-1];
		if(sum == 0)
			puts("No Circular Primes.");
		else if(sum == 1) {
			puts("1 Circular Prime.");
		} else
			printf("%d Circular Primes.\n", sum);
	}
    return 0;
}
