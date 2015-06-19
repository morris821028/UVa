#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <limits.h>
using namespace std;
const long long LIMIT = 1e+16 + 10;
long long mpow(long long n, int m) {
	long long ret = 1;
	for(int i = 1; i <= m; i++)
		ret *= n;
	return min(ret, LIMIT);
}
long long mul(long long a, long long b) {
	if (a == 0 || b == 0)	
		return 0;
	if (LIMIT / a / b == 0)
		return LIMIT;
	return a * b;
}
void calc(long long n, long long cnt[]) {
	if (n <= 0)
		return;
	char buf[105];
	sprintf(buf, "%lld", n);
	int len = strlen(buf);
	long long prev = 0, suffix;
	calc(mpow(10, len-1)-1, cnt);
	
	long long prev10 = 1;
	for(int i = 0; i < len; i++) {
		int d = buf[i] - '0';
		sscanf(buf+i+1, "%lld", &suffix);
		
		if(i != len-1)
			cnt[d] += suffix + 1;
		else
			cnt[d]++;
		if(i != 0)
			cnt[d] += mul((prev - prev10/10), mpow(10, len-i-1));
		
		cnt[d] = min(cnt[d], LIMIT);
		for(int j = i == 0; j < 10; j++) {
			if(j == d)	continue;
			if(j < d) {
				if(prev > 0) {
					cnt[j] += mul((prev - prev10/10 + 1) , mpow(10, len-i-1));
				} else {
					cnt[j] += mpow(10, len-i-1);
				}
			} else {
				if(prev > 0 && prev - prev10/10 > 0) {
					cnt[j] += mul((prev - prev10/10) , mpow(10, len-i-1));
				}
			}
			cnt[j] = min(cnt[j], LIMIT);
		}
		prev10 *= 10;
		prev = prev * 10 + d;
	}
}
void print(long long r) {
	long long B[10] = {};
	calc(r, B);
	for (int i = 0; i < 10; i++)
		printf("%lld ", B[i]);
	puts("");
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		long long C[10];
		for (int i = 0; i < 10; i++)
			scanf("%lld", &C[i]);
		long long l = 1, r = 1e+16, mid, ret = 0;
		while (l <= r) {
			mid = (l + r)/2;
			long long B[10] = {};
			calc(mid, B);
			int ok = 1;
			for (int i = 0; i < 10; i++)
				ok &= B[i] <= C[i];
			if (ok)
				l = mid + 1, ret = mid;
			else
				r = mid - 1;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
