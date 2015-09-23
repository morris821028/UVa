#include <bits/stdc++.h>
using namespace std;

int main() {
	long long N, B;
	while (scanf("%lld %lld", &N, &B) == 2) {
		long long l = 1, r = N/2 + N%2, mid;
		if (N%2 && B == N*N) {
			printf("%lld %lld\n", N/2+1, N/2+1);
			continue;
		}
		while (l <= r) {
			mid = (l+r)/2;
			long long st = 4*N - 4;
			long long ed = 4*(N-(mid-1)*2) - 4;
			long long ss = (st + ed) * mid / 2;
			if (ss-ed+1 <= B && B <= ss) {
				long long x = mid, y = mid;
				long long b = B - (ss-ed+1), e = N-(mid-1)*2;
//				printf("st %lld %lld %lld %lld\n", x, y, e, b);
				if (b < e) {
					printf("%lld %lld\n", x, y + b);
					break;
				}
				y += e-1, b -= e, x++;
				if (b < e-1) {
					printf("%lld %lld\n", x + b, y);
					break;
				}
				x += e-2, b -= e-1, y--;
				if (b < e-1) {
					printf("%lld %lld\n", x, y - b);
					break;
				}
				y -= e-2, b -= e-1, x--;
				printf("%lld %lld\n", x - b, y);
				break;
			}
			if (ss < B)	l = mid+1;
			else		r = mid-1;
		}
	}
	return 0;
}
/*
8 53
1073741824 1152921504603393520
*/
