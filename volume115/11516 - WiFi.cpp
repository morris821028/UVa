#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
int A[100005];
int n, m, i, l, r, mm;
int greedy(int mm) {
    static int cnt;
    static int r;
    cnt = 1;
    r = A[0] + mm;
    for(i = 0; i < m; i++) {
        if(abs(r-A[i]) <= mm) {}
        else {
            cnt++;
            if(cnt > n) return 0;
            r = A[i] + mm;
        }
    }
    return 1;
}
inline int ReadInt(int *x) {
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
    scanf("%*d");
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < m; i++)
            ReadInt(&A[i]), A[i] *= 2;
        sort(A, A+m);
        l = 0, r = (A[m-1]-A[0])/2;
        while(l <= r) {
            mm = (l+r)/2;
            if(greedy(mm)) {
                r = mm-1;
            } else
                l = mm+1;
        }
        printf("%.1lf\n", (r+1)/2.0);
    }
    return 0;
}
