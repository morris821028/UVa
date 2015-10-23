#include <stdio.h>

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
static const int N = 1048576;
char buf[N], *p, *end;
void printInt(int x, char padding) {
    static char stk[16];
    int idx = 0;
    stk[idx++] = padding;
    if (!x)	
        stk[idx++] = '0';
    while (x)
        stk[idx++] = x%10 + '0', x /= 10;
    while (idx) {
        if (p == end) {
            *p = '\0';
            printf("%s", buf), p = buf;
        }
        *p = stk[--idx], p++;
    }
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int f = 0, ret = 0;
		while (n) {
			if (n&1)	f++, ret = f > ret ? f : ret;
			else		f = 0;
			n >>= 1;
		}
		ret = f > ret ? f : ret;
		printf("%d\n", ret);
	}
	return 0;
}
