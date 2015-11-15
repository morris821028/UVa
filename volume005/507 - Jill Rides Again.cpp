#include <stdio.h>

int main() {
	int testcase, cases = 0;
	int n, x;
	scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        int tmp = 1, st = 0xffff, ed, sum = 0, ans = 0;
        for (int i = 2; i <= n; i++) {
            scanf("%d", &x);
            sum += x;
            if (sum < 0) sum = 0, tmp = i;
            if (sum >= ans) {
            	
                if (sum > ans || (sum == ans && (i - tmp > ed - st))) {
                    st = tmp;
                    ed = i;
                }
                ans = sum;
            }
        }
        if (ans > 0)
            printf("The nicest part of route %d is between stops %d and %d\n", ++cases, st, ed);
        else
            printf("Route %d has no nice parts\n", ++cases);
    }
    return 0;
}
/*
1
10
-1
2
3
4
-20
1
3
4
1
9
*/
