#include <stdio.h>
#include <math.h>
inline int readchar() {
    static const int N = 524288;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline double ReadPoint() {
    static char c;
    int p = 0;
    double t = 1;
    while((c = readchar()) >= '0')
        t /= 10, p = (p << 3) + (p << 1) + (c-'0');
    return (double)p*t;
}
inline int ReadDouble(double *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return EOF;}
    if(c == '.')    {*x = ReadPoint();return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x)*10 + c-'0';
    if(c == '.')    *x += ReadPoint();
    *x *= neg;
    return 0;
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
    int n, i, cases = 0;
    double LOG[50001];
    for(i = 0; i <= 50000; i++)
        LOG[i] = log(i);
    ReadInt(&i);
    while(ReadInt(&n)) {
        double B = 0, S = 0, x;
        double N2 = (n-1)*log(2);
        for(i = 0; i < n; i++) {
            ReadDouble(&x);
            S += exp(B-N2)*x;
            B = B + LOG[n-1-i] - LOG[i+1];
        }
        printf("Case #%d: %.3lf\n", ++cases, S);
    }
    return 0;
}
