#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
double area(double a, double b, double c) {
    double s = (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}
int main() {
    int n, t, i, j, k;
    double A[100001];
    scanf("%d",&t);
    while(t--) {
        scanf("%d",&n);
        double tot = 0;
        for(i = 0; i < n; i++) {
            scanf("%lf", &A[i]), tot += A[i];
            A[i] = tot;
        }
        tot /= 3;
        double mx = 0;
        int cut1 = 0, cut2 = n-1;
        for(i = 0; i < n; i++)
            if(A[i] >= tot)
                cut1 = i, i = n+1;
        for(i = n-1; i >= 0; i--)
            if(A[n-1]-A[i] >= tot)
                cut2 = i, i = -1;
        for(i = -2; i < 2; i++)
            for(j = -2; j < 2; j++) {
                if(cut1+i >= n || cut1+i < 0 || cut2+j >= n || cut2+j < 0)
                    continue;
                if(cut1+i >= cut2+j)
                    continue;
                mx = max(mx, area(A[cut1+i], A[cut2+j]-A[cut1+i], A[n-1]-A[cut2+j]));
            }
        printf("%.2lf\n",mx);
    }
 return 0;
}
