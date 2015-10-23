#include <stdio.h>
int hasEOF = 0;
int readchar() {
	static int N = 1<<20;
	static char buf[1<<20];
	static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) {
        	hasEOF = 1;
        	return EOF;	
		}
        p = buf;
    }
    return *p++;
}
int ReadInt(int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
char obuf[1<<20];
char *op = obuf, *oend = obuf + (1<<20) - 1;
void printInt(int x, char padding) {
    static char stk[16];
    int idx = 0;
    stk[idx++] = padding;
    if (!x)	
        stk[idx++] = '0';
    while (x)
        stk[idx++] = x%10 + '0', x /= 10;
    while (idx) {
        if (op == oend) {
            *op = '\0';
            printf("%s", obuf), op = obuf;
        }
        *op = stk[--idx], op++;
    }
}
int main() {
	int n;
	while (ReadInt(&n)) {
		int f = 0, ret = 0;
		while (n) {
			if (n&1)	f++, ret = f > ret ? f : ret;
			else		f = 0;
			n >>= 1;
		}
		ret = f > ret ? f : ret;
		printInt(ret, '\n');
		if (hasEOF)	break;
	}
	*op = '\0';
	printf("%s", obuf);
	return 0;
}
