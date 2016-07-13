#include <bits/stdc++.h>
using namespace std;
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int testcase, n;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d", &n);
		ReadInt(&n);
		int Ql[16] = {}, Qu[16] = {};
		for (int i = 0; i < n; i++) {
			int d, s, r;
			ReadInt(&d), ReadInt(&s);
			while ((r = readchar()) < '-');
//			scanf("%d %d %s", &d, &s, r);
			if (s == 1 && r == 'c')
				Ql[d]++;
			else if (s == 0 && r == 'i')
				Qu[d]++;
		}
		
		long long ret = 0;
		for (int i = 0, sum = 0; i < 16; i++) {
			ret += 1LL * Ql[i] * sum;
			sum += Qu[i];
		}
		printf("%lld\n", ret);
	}
	return 0;
}

