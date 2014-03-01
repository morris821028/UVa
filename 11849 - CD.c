#include <stdio.h>
int A[1000000];
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
    int n, m;
    while(ReadInt(&n)) {
        ReadInt(&m);
        if(n == 0 && m == 0)
            break;
        int idx = 0, i, x, cnt = 0;
        for(i = 0; i < n; i++) {
            ReadInt(A+i);
        }
        while(m--) {
            ReadInt(&x);
            while(idx < n) {
                if(A[idx] == x)
                    cnt++, idx++;
                else if(A[idx] < x)
                    idx++;
                else
                    break;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
