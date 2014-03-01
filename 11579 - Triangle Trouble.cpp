#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
inline double ReadPoint() {
    static char c;
    int p = 0;
    double t = 1;
    while((c = getchar()) >= '0')
        t /= 10, p = (p << 3) + (p << 1) + (c-'0');
    return (double)p*t;
}
inline int ReadDouble(double *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    if(c == '.')    {*x = ReadPoint();return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x)*10 + c-'0';
    if(c == '.')    *x += ReadPoint();
    *x *= neg;
    return 0;
}
int main() {
    int t, n, i;
    double A[10000];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            ReadDouble(A+i);
        }
        sort(A, A+n);
        double area = 0.0, tmp, s;
        for(i = 2; i  < n; i++) {
            if(A[i-2]+A[i-1] <= A[i])
                continue;
            s = (A[i-2]+A[i-1]+A[i])/2;
            tmp = s*(s-A[i-2])*(s-A[i-1])*(s-A[i]);
            if(area < tmp)
                area = tmp;
        }
        area = sqrt(area);
        printf("%.2lf\n", area);
    }
    return 0;
}
