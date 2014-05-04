#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
long long mpow(int n, int m) {
	long long ret = 1;
	for(int i = 1; i <= m; i++)
		ret *= n;
	return ret;
}
void ito2(long long n, char buf[]) {
	if(n == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}
	int i, j, f;
	for(i = 63, j = f = 0; i >= 0; i--) {
		if((n>>i)&1)	f = 1;
		if(f) {
			buf[j++] = ((n>>i)&1) + '0';
		}
	}
	buf[j] = '\0';
}
void a2toi(long long &r, char buf[]) {
	r = 0;
	for(int i = 0; buf[i]; i++)
		r = r<<1 | (buf[i] - '0');
}
void calc(long long n, long long cnt[]) {
	if(n <= 0)
		return;
	//printf("%d\n", n);
	char buf[105];
	ito2(n, buf);
	int len = strlen(buf);
	long long prev = 0;
	long long suffix;
	calc(mpow(2, len-1)-1, cnt);
	//for(int i = 0; i < 10; i++)
	//	cnt[i] = 0;
	long long prev10 = 1;
	for(int i = 0; i < len; i++) {
		int d = buf[i] - '0';
		a2toi(suffix, buf + i + 1);
		
		if(i != len-1)
			cnt[d] += suffix + 1;
		else
			cnt[d]++;
		if(i != 0)
			cnt[d] += (prev - prev10/2) * mpow(2, len-i-1);
		for(int j = i == 0; j < 2; j++) {
			if(j == d)	continue;
			if(j < d) {
				if(prev > 0) {
					cnt[j] += (prev - prev10/2 + 1) * mpow(2, len-i-1);
				} else {
					cnt[j] += mpow(2, len-i-1);
				}
			} else {
				if(prev > 0 && prev - prev10/2 > 0) {
					cnt[j] += (prev - prev10/2) * mpow(2, len-i-1);
				}
			}
		}
		prev10 *= 2;
		prev = prev * 2 + d;
	}
}
int main() {
	long long A, B;
	while(scanf("%lld %lld", &A, &B) == 2) {
		long long cntA[2] = {}, cntB[2] = {};
		calc(A - 1, cntA);
		calc(B, cntB);
		printf("%lld\n", cntB[1] - cntA[1]);
	}
	return 0;
}
