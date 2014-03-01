#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int x[10], y[10];
int n, i, p[10];
void solve() {
    int a[10];
    double mn = 0xfffffff, tmp;
    do {
        double sum = 0;
        for(i = 1; i < n; i++) {
            tmp = sqrt((x[p[i]]-x[p[i-1]])*(x[p[i]]-x[p[i-1]])+
                       (y[p[i]]-y[p[i-1]])*(y[p[i]]-y[p[i-1]])) +16;
            sum += tmp;
        }
        if(sum < mn) {
            mn = sum;
            for(i = 0; i < n; i++)
                a[i] = p[i];
        }
    } while(next_permutation(p, p+n));
    for(i = 1; i < n; i++) {
        tmp = sqrt((x[a[i]]-x[a[i-1]])*(x[a[i]]-x[a[i-1]])+
                (y[a[i]]-y[a[i-1]])*(y[a[i]]-y[a[i-1]])) +16;
        printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n",
               x[a[i-1]], y[a[i-1]], x[a[i]], y[a[i]], tmp);
    }
    printf("Number of feet of cable required is %.2lf.\n", mn);
}
int main() {
    int cases = 0;
    while(scanf("%d", &n), n) {
        for(i = 0; i < n; i++)
            scanf("%d %d", &x[i], &y[i]), p[i] = i;
        puts("**********************************************************");
        printf("Network #%d\n", ++cases);
        solve();
    }
    return 0;
}
