#include <stdio.h>
long long ZeroToN(long long n) {
	if(n <= 0)
		return 0;
	long long ans = 0, i;
	while(n != 0) {
		ans += 45*(n/10);
		for(i = n/10*10+1; i <= n; i++)
			ans += i%10;
		n /= 10;
	}
	return ans;
}
int main() {
	long long p, q;
	while(scanf("%lld %lld", &p, &q) == 2) {
		if(p < 0 && q < 0)
			break;
		printf("%lld\n", ZeroToN(q)-ZeroToN(p-1));
	}
    return 0;
}
