#include <stdio.h> 
#include <stdlib.h>
#include <algorithm>
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
	int testcase, n, m, x;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d", &n, &m);
		ReadInt(&n);
		ReadInt(&m);
		int odd = 0, even = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
//				scanf("%d", &x);
				ReadInt(&x);
				if (x == -1)	continue;
				if ((i+j)&1)
					odd += x;
				else
					even += x;
			}
		} 
		printf("%d\n", abs(odd - even));
	}
	return 0;
}
/*
1
3 3
2 2 3
1 -1 3
1 1 0
*/
