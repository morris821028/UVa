#include <stdio.h>
#include <math.h>
#define min(x, y) ((x)<(y)?(x):(y))
struct Pt {
    float x, y;
};
Pt D[3000005];
double merge(int l, int m, int r, double d) {
    static double midX, tmp;
    static int i, j;
    midX = D[m].x;
    for(i = m; i >= l; i--) {
        if((D[i].x-midX)*(D[i].x-midX) >= d)
            break;
        for(j = m+1; j <= r; j++) {
            if((D[i].x-D[j].x)*(D[i].x-D[j].x) >= d)
                break;
            tmp = (D[i].x-D[j].x)*(D[i].x-D[j].x)+(D[i].y-D[j].y)*(D[i].y-D[j].y);
            d = min(d, tmp);
        }
    }
    return d;
}
void closestPair(int n) {
    int i, j;
    double ans = 0xffffff, tmp;
    for(i = 2; i < n; i <<= 1) {
        for(j = 0; j < n; j += i) {
            if(j+i-1 < n)
                tmp = merge(j, j+i/2-1, j+i-1, ans);
            else if(j+i/2-1 < n)
                tmp = merge(j, j+i/2-1, n-1, ans);
            ans = min(ans, tmp);
        }
    }
    tmp = merge(0, i/2-1, n-1, ans);
    ans = min(ans, tmp);
    printf("%.4lf\n", sqrt(ans));
}
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
    int n, i, x, y;
    //scanf("%d", &n);
    ReadInt(&n);
    for(i = 0; i < n; i++) {
        ReadInt(&x);
        ReadInt(&y);
        D[i].x = x, D[i].y = y;
     //   scanf("%f %f", &D[i].x, &D[i].y);
    }
    closestPair(n);
    return 0;
}
