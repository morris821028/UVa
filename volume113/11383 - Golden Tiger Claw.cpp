#include <stdio.h>
#include <string.h>
int W[505][505], N;
int mx[505], my[505]; // match arr
int lx[505], ly[505]; // label arr
int x[505], y[505]; // used arr
int hungary(int nd) {
    int i;
    x[nd] = 1;
    for(i = 1; i <= N; i++) {
        if(y[i] == 0 && W[nd][i] == lx[nd]+ly[i]) {
            y[i] = 1;
            if(my[i] == 0 || hungary(my[i])) {
                my[i] = nd;
                return 1;
            }
        }
    }
    return 0;
}
int KM() {
    int i, j, k, d;
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for(i = 1; i <= N; i++)
        for(j = 1; j <= N; j++)
            lx[i] = lx[i] > W[i][j] ? lx[i] : W[i][j];
    for(i = 1; i <= N; i++) {
        while(1) {
            memset(x, 0, sizeof(x));
            memset(y, 0, sizeof(y));
            if(hungary(i))  break;
            d = 0xfffffff;
            for(j = 1; j <= N; j++) {
                if(x[j]) {
                    for(k = 1; k <= N; k++)
                        if(!y[k])
                        d = d < lx[j]+ly[k]-W[j][k] ?
                            d : lx[j]+ly[k]-W[j][k];
                }
            }
            if(d == 0xfffffff)  break;
            for(j = 1; j <= N; j++) {
                if(x[j])    lx[j] -= d;
                if(y[j])    ly[j] += d;
            }
        }
    }
    int res = 0;
    for(i = 1; i <= N; i++) {
        if(my[i])
            res += W[my[i]][i];
    }
    return res < 0 ? 0 : res;
}
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        N = n;
        int i, j;
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                scanf("%d", &W[i][j]);
        KM();
        int ret = 0;
        for(i = 1; i <= n; i++)
        	printf("%d%c", lx[i], i == n ? '\n' : ' '), ret += lx[i];
        for(i = 1; i <= n; i++)
        	printf("%d%c", ly[i], i == n ? '\n' : ' '), ret += ly[i];
        printf("%d\n", ret);
        
    }
    return 0;
}
