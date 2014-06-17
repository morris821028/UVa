#include <stdio.h>
#include <string.h>
int mapped[262144], LIS[100005];
int main() {
    int n, i, x;
    while(scanf("%d", &n) == 1) {
        memset(mapped, 0, sizeof(mapped));
        for(i = 0; i < n; i++)
            scanf("%d", &x), mapped[x+100000] = i;
        int L = -1, l, r, m;
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            x = mapped[x+100000];
            l = 0, r = L;
            while(l <= r) {
                m = (l+r)/2;
                if(LIS[m] < x)
                    l = m+1;
                else
                    r = m-1;
            }
            LIS[l] = x;
            if(l > L)   L = l;
        }
        printf("%d\n", L+1);
    }
    return 0;
}
