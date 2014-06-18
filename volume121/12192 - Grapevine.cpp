#include <stdio.h>
#include <algorithm>
using namespace std;
int diag[1005][505]; // diagonal
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
    int n, m, q, L, U;
    int i, j;
    while(ReadInt(&n), ReadInt(&m), n) {
        int didx[1005] = {};
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                ReadInt(&diag[i-j+m][didx[i-j+m]++]);
                //scanf("%d", &diag[i-j+m][didx[i-j+m]++]);
            }
        }
        ReadInt(&q);
        //scanf("%d", &q);
        while(q--) {
            ReadInt(&L);
            ReadInt(&U);
            //scanf("%d %d", &L, &U);
            int ret = 0;
            for(i = n+m-1; i >= 0; i--) {
                int low = lower_bound(diag[i], diag[i]+didx[i], L) - diag[i];
                int upp = upper_bound(diag[i]+low, diag[i]+didx[i], U) - diag[i];
                ret = max(ret, upp-low);
            }
            printf("%d\n", ret);
        }
        puts("-");
    }
    return 0;
}
