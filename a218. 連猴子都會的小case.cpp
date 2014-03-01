#include<stdio.h>
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
    while((c = readchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
main() {
	int n, x;
	while(ReadInt(&n) != EOF) {
		int a, b, used[10] = {};
		for(a = 0; a < n; a++)
			ReadInt(&x), used[x]++;
		for(a = n; a;a--)
			for(b = 0; b < 10; b++)
				if(used[b] == a)
					printf("%c ", b+'0');
		puts("");
	}
	return 0;
}
