// greedy 
#include <stdio.h> 
long long getLen(long long v) {
	if (v == 0)	return 1;
	int cnt = 0;
	while (v)	v /= 2, cnt++;
	return cnt;
} 
int main() {
	int testcase, cases = 0;
	long long A, B, P;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld %lld", &A, &B, &P);
		long long l = getLen(P);
		long long ret = -1;
		for (long long s = 0; s + l < 63; s++) {
			long long h = (A >> (s + l)) << (s + l);
			long long v = h | (P<<s);
			if (v < A) {
				if (v + (1LL<<s) - 1 >= A) {
					v = v + (A&((1LL<<s)-1));
//					puts("T");
				} else {
					h = ((A >> (s + l)) + 1) << (s + l);
			
					v = h | (P<<s);
//					puts("H");
				}
			}
//			printf("%lld %lld %lld\n", v, h, s);
			if (A <= v && v <= B) {
				if (ret == -1 || ret > v)
					ret = v;
			}
		}
		printf("Case %d: ", ++cases);
		if (ret != -1)
			printf("%lld\n", ret);
		else
			puts("NONE");
	} 
	return 0;
}
/*
4
10 20 5
10 100 9
1 1000 7
10 20 21

25
19017 22632 39
17314 19968 15
26675 29789 33
21571 23337 47
5928 21600 10
9514 15151 9
2473 10692 74
6111 9387 17
9335 17434 99
11023 11914 80
11327 23201 90
8538 15700 67
4974 28510 2
13561 20572 52
18868 24720 96
5273 16062 73
9662 17255 40
1056 22874 24
712 17275 69
3018 20131 71
1854 19552 5
621 5696 96
7837 14117 33
27830 32015 95
3498 26188 67

*/
