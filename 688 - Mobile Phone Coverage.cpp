#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
    int n, cases = 0;
    int i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        double x[105], y[105], r[105];
        double dx[205], dy[205], area = 0;
        for(i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &x[i], &y[i], &r[i]);
            dx[i*2] = x[i]-r[i];
            dx[i*2+1] = x[i]+r[i];
            dy[i*2] = y[i]-r[i];
            dy[i*2+1] = y[i]+r[i];
        }
        sort(dx, dx+2*n);
        sort(dy, dy+2*n);
        for(i = 1; i < 2*n; i++) {
            for(j = 1; j < 2*n; j++) {
                for(k = 0; k < n; k++) {
                    if(dx[i] <= x[k]+r[k] && dx[i-1] >= x[k]-r[k]) {
                        if(dy[j] <= y[k]+r[k] && dy[j-1] >= y[k]-r[k]) {
                            area += (dx[i]-dx[i-1])*(dy[j]-dy[j-1]);
                            break;
                        }
                    }
                }
            }
        }
        printf("%d %.2lf\n", ++cases, area);
    }
    return 0;
}
