#include <stdio.h>

int main() {
    int t, test = 0;
    int n, i, x;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int tmp = 1, st = 0xffff, ed, sum = 0, ans = 0;
        for(i = 2; i <= n; i++) {
            scanf("%d", &x);
            sum += x;
            if(sum < 0) sum = 0, tmp = i;
            if(sum >= ans) {
                if(sum > ans) {
                    st = tmp;
                    ed = i;
                } else if(tmp <= st) {
                    ed = i;
                }
                ans = sum;
            }
        }
        if(ans > 0) {
            printf("The nicest part of route %d is between stops %d and %d\n", ++test, st, ed);
        } else {
            printf("Route %d has no nice parts\n", ++test);
        }
    }
    return 0;
}
