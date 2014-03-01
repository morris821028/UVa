#include <stdio.h>
int gcd(int x, int y) {
    int t;
    while(x%y) {
        t = x, x = y, y = t%y;
    }
    return y;
}
double mysqrt(double &n) {
    static int i;
    static double ans;
    for(i = 0, ans = n; i < 7; i++)
        ans = (ans + n/ans)/2;
    return ans;
}
int main() {
    int n, A[50], i, j;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        int s = n*(n-1)/2, cnt = 0;
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++)
                if(gcd(A[i], A[j]) == 1)
                    cnt++;
        }
        if(!cnt)
            puts("No estimate for this data set.");
        else {
            double pi = (double)6*s/cnt;
            printf("%.6lf\n", mysqrt(pi));
        }
    }
    return 0;
}
