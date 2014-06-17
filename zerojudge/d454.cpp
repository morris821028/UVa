#include <stdio.h>
#include <math.h>
int main() {
    int t, j;
    double x, y, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%lf %lf", &x, &y);
        y = y*sqrt(3)/2;
        x = fabs(x+0.5), y = fabs(y);
        int fx, fy;
        for(i = 0, j = 0; i < 10010; i += 1.5, j++) {
            if(i+1 > x) {
                fx = j;
                if(j%2 == 0)
                    fy = (int)ceil(y-0.5);
                else
                    fy = (int)ceil(y);
                break;
            }
            if(i+1.5 > x) {
                if(j%2 == 0) {
                    for(k = 0; k < 10010; k++) {
                        // L1 _/3 x + y = (_/3)/2+k+1
                        // L2 _/3 x - y = -(_/3)/2+k
                    }
                } else {
                }
            }
        }
        printf("%d %d\n", fx, fy);
    }
    return 0;
}
