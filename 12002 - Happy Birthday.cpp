#include <stdio.h>

int main() {
    int n, i, j, k;
    int dish[105], A[105], B[105];
    int la, lb, dpa[105], dpb[105];
    int ta, tb, ans;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &dish[i]);
        ans = 0;
        for(i = 0; i < n; i++) {
            la = 0, lb = 0;
            for(j = i+1; j < n; j++)
                if(dish[j] > dish[i])
                    A[la++] = dish[j];
                else
                    B[lb++] = dish[j];
            for(j = 0; j < la; j++) {
                dpa[j] = 1;
                for(k = 0; k < j; k++)
                    if(A[j] >= A[k] && dpa[j] < dpa[k]+1)
                        dpa[j] = dpa[k]+1;
            }
            for(j = 0; j < lb; j++) {
                dpb[j] = 1;
                for(k = 0; k < j; k++)
                    if(B[j] <= B[k] && dpb[j] < dpb[k]+1)
                        dpb[j] = dpb[k]+1;
            }
            ta = 0, tb = 0;
            for(j = 0; j < la; j++)
                if(dpa[j] > ta) ta = dpa[j];
            for(j = 0; j < lb; j++)
                if(dpb[j] > tb) tb = dpb[j];
            if(ta+tb+1 > ans)
                ans = ta+tb+1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
