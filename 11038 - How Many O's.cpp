#include <stdio.h>

long long calcZeros(long long n) {
	if(n < 0)	return 0;
	long long sum = 1;
	long long n10 = 1, ntail = 0;
	while(n) {
		if(n%10 != 0) {
			sum += n/10*n10;
		} else {
			sum += (n/10-1)*n10 + (ntail+1);
		}
		ntail += n%10*n10;
		n /= 10, n10 *= 10;
	}
	return sum;
}
int main() {
	long long m, n;
	while(scanf("%lld %lld", &m, &n) == 2) {
		if(m < 0 && n < 0)
			break;
		printf("%lld\n", calcZeros(n)-calcZeros(m-1));
	}
    return 0;
}
