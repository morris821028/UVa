#include<stdio.h>
#include<stdlib.h>
int Judge(int n, int k, int m) {
    static int i, j, kp, tk, tmp, lave;
    static int pre, now, next[29];
    for(i = 1; i < n; i++)
        next[i] = i+1;
    next[n] = 1, pre = n, now = 1, lave = n;
    for(i = 1; i <= m; i++) {
        tmp = 0;
        tk = k%lave;
        if(tk == 0) tk = lave;
        for(j = now; tmp != tk-1; pre = j, j = next[j])
            tmp++;
        kp = j;
        next[pre] = next[kp], now = next[kp], lave--;
        if(kp <= m)    return 0;
    }
    return 1;
}
main() {
    int m, k, i, Ans[14];
    for(i = 1; i <= 13; i++) {
        k = i, m = k+1;
        while(1) {
            if(Judge(2*k, m, k))
                break;
            m++;
        }
        Ans[i] = m;
    }

    while(scanf("%d", &k) == 1 && k)
        printf("%d\n", Ans[k]);
    return 0;
}
