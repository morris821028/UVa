#include <stdio.h>
int hasline;
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
    if(c == '\n')   hasline = 1;
    *x *= neg;
    return 1;
}

int main() {
    int t, p, deg[1000] = {}, x, i;
    ReadInt(&t);
    while(t--) {
        ReadInt(&p);
        int res = p, first = 0;
        for(i = 0; i < p; i++) {
            hasline = 0;
            deg[i] = 0;
            while(!hasline) {
                ReadInt(&x);
                deg[i]++;
            }
            if(deg[i] < res)
                res = deg[i];
        }
        for(i = 0; i < p; i++) {
            if(res == deg[i]) {
                if(first)   putchar(' ');
                else        first = 1;
                printf("%d", i+1);
            }
        }
        puts("");
    }
    return 0;
}
