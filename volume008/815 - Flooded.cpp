#include <bits/stdc++.h>
using namespace std;

int main() {
    double V;
    int cases = 0;
    int n, m, A[1005];
    while (scanf("%d %d", &n ,&m) == 2 && n) {
        int x;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &A[i*m+j]);
        scanf("%lf", &V);
        n = n*m;
        sort(A, A+n);
        double sum = 0, h = 0;
        A[n] = 1e+10;
        printf("Region %d\n", ++cases);
        for (int i = 0; i < n; i++) {
            sum += A[i];
            h = (V+sum*100)/(i+1)/100.0;
#define eps 1e-6
            if (h < A[i+1]+eps) {
                printf("Water level is %.2lf meters.\n", h);
                printf("%.2lf percent of the region is under water.\n\n", (i+1)*100.0/n);
                break;
            }
        }
    }
    return 0;
}
/*
1 1
37
24
0 0
*/
