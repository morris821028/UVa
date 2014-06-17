#include <stdio.h>
#include <math.h>
int main() {
    int n, i, j, flag = 0;
    while(scanf("%d", &n) == 1) {
        if(flag)
            puts("");
        flag = 1;
        int t1 = 0, t2 = 0;
        double r = n-0.5, r1, r2;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                r1 = sqrt(i*i+j*j);
                r2 = sqrt(i*i+j*j+2*i+2*j+2);
                if(r1 <= r && r2 <= r)
                    t1++;
                if(r1 <= r && r2 > r)
                    t2++;
            }
        }
        printf("In the case n = %d, %d cells contain segments of the circle.\n", n, t2*4);
        printf("There are %d cells completely contained in the circle.\n", t1*4);
    }
    return 0;
}
