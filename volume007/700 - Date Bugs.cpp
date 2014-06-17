#include <stdio.h>

int main() {
    int n, cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        int diff[20], y[20], a[20], b[20];
        int i, yflag = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d", &y[i], &a[i], &b[i]);
            diff[i] = b[i]-a[i];
            if(y[i] > yflag)
                yflag = y[i];
        }
        for(; yflag < 10000; yflag++) {
            for(i = 0; i < n; i++) {
                if((yflag-y[i])%diff[i] != 0)
                    break;
            }
            if(i == n)
                break;
        }
        printf("Case #%d:\n", ++cases);
        if(yflag == 10000)
            puts("Unknown bugs detected.\n");
        else
            printf("The actual year is %d.\n\n", yflag);
    }
    return 0;
}
