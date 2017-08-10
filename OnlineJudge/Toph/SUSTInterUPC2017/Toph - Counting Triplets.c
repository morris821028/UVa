#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXV (1<<16)
#define MAXN (131072)

inline int readchar() {
    static char buf[1048576];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, 1048576, stdin)) == buf) return EOF;
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
		
		static int A[MAXN];
		for (int i = 0; i < n; i++) {
//			scanf("%d", &A[i]);
			ReadInt(&A[i]);
		}
				
		int64_t ret = 0;
		static uint16_t C[MAXV] = {};
		memset(C, 0, sizeof(C));
		int mn = MAXV;
		for (int i = 0; i < n; i++) {
			int x = A[i];
			int a = mn;
			int b = x-a;
			uint16_t *Ca = C+a, *Cb = C+b;
			while (Ca < Cb) {
				int32_t t1 = *Ca;
				int32_t t2 = *Cb;
				ret += (int64_t) t1*t2;
				Ca++, Cb--;
			}
			if (x%2 == 0 && C[x/2]) {
				int64_t t = C[x/2];
				ret += t*(t-1)/2;
			}
			C[x]++;
			if (x < mn)	mn = x;
		}
		
		printf("%lld\n", ret);
	}
	return 0;
}
/*
1 
6 
2 3 3 4 7 11
*/

