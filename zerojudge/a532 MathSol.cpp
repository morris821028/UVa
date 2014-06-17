#include <stdio.h>
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
    int dp[20] = {0,3}, x5[20] = {1}, stk[20];
    int i, j;
    char buf[5] = {'0','1','6','8','9'};
    char buf2[5] = {'0','1','9','8','6'};
    char str[30];
    for(i = 1; i < 20; i++) x5[i] = x5[i-1]*5;
    for(i = 2; i < 20; i++) {
        j = i/2;
        if(i&1)
            dp[i] = (x5[j]-x5[j-1])*3;
        else
            dp[i] = (x5[j]-x5[j-1]);
    }
    int n, l;
    while(ReadInt(&n) && n) {
        for(i = 1; i < 20; i++) {
            if(n <= dp[i]) {
                l = i;
                break;
            }
            n -= dp[i];
        }
        int idx = 0;
        j = l/2;
        if(l&1) {
            int n3 = n/3+x5[j-1]-(n%3 == 0);
            n = n - n/3*3;
            while(n3) {
                stk[idx++] = n3%5;
                n3 /= 5;
            }
        } else {
            n += x5[j-1] - 1;
            while(n) {
                stk[idx++] = n%5;
                n /= 5;
            }
        }
        int at = 0;
        for(i = j-1; i >= 0; i--)
            str[at++] = buf[stk[i]];
        if(l&1) {
            if(!n)  str[at++] = '8';
            else if(n == 1) str[at++] = '0';
            else    str[at++] = '1';
        }
        for(i = 0; i < j; i++)
            str[at++] = buf2[stk[i]];
        str[at] = '\0';
        puts(str);
    }
    return 0;
}
