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
int main() {
    int t, n, q, i, x, a;
    ReadInt(&t);
    //scanf("%d", &t);
    while(t--) {
        ReadInt(&n), ReadInt(&q);
      //  scanf("%d %d", &n, &q);
        int m[256] = {};
        while(n--) {
            ReadInt(&x);
            //scanf("%d", &x);
            m[x&0xff] = 1;
        }
        while(q--) {
            ReadInt(&a);
            //scanf("%d", &a);
            x = 0;
            for(i = 255; i > x; i--)
                if(m[i] && (a&i) > x)
                    x = a&i;
            printf("%d\n", x);
        }
    }
    return 0;
}
