#include <stdio.h>
int N2[32];
int grey(int n, int k) {
    if(n == 0)  return 0;
    if(k >= N2[n-1])
        return N2[n-1]|(grey(n-1, N2[n]-k-1));
    else
        return grey(n-1, k);
}
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, k, t;
    for(n = 0; n <= 31; n++)
        N2[n] = 1<<n;
    ReadInt(&t);
    while(t--) {
        ReadInt(&n);
        ReadInt(&k);
        printf("%d\n", grey(n, k));
    }
    return 0;
}
