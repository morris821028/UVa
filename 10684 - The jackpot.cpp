#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int ans = 0, x, tmp = 0;
        while(n--) {
            scanf("%d", &x);
            tmp += x;
            if(tmp < 0)
                tmp = 0;
            if(tmp > ans)
                ans = tmp;
        }
        if(ans)
            printf("The maximum winning streak is %d.\n", ans);
        else
            printf("Losing streak.\n");
    }
    return 0;
}
