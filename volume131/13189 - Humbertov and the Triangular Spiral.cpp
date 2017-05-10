#include <bits/stdc++.h>
using namespace std;

pair<long long, long long> triangle_spiral(long long n) {
	if (n == 1)
		return make_pair(0, 0);
	long long bx = 0, by = 0, lv = 1;
	n--;
	long long k = sqrt(n/4);
	lv = k+1, bx += 2*k, by -= k, n -= 4*k*k;
	for (; n > (lv-1)*8+4; lv++)
		n -= (lv-1)*8+4, bx += 2, by--;
	bx--, n--;
	if (n < (lv-1)*4) {
		bx -= n;
	} else {
		bx -= (lv-1)*4, n -= (lv-1)*4;
		if (n < lv*2-1) {
			bx += n, by += n;
		} else {
			bx += lv*2-1, by += lv*2-1, n -= lv*2-1;
			bx += n, by -= n;
		}
	}
	return make_pair(bx, by);
}
int main() {
	int testcase;
	long long n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld", &n);
		pair<long long, long long> pos = triangle_spiral(n);
		printf("%lld %lld\n", pos.first, pos.second);
	}
	return 0;
}

