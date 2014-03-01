#include<stdio.h>
long long Mod(long long x, long long y, long long m) {
	long long ans = 1, tmp = x;
	while(y) {
		if(y&1) {
			ans *= tmp;
			ans %= m;
		}
		y >>= 1;
		tmp *= tmp, tmp %= m;
	}
	return ans;
}
int main() {
	int B, P, M;
	while(scanf("%d %d %d", &B, &P, &M) == 3) {
		printf("%lld\n", Mod(B, P, M));
	}
    return 0;
}
