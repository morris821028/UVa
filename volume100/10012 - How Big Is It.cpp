#include <stdio.h>
#include <string.h>
#include <math.h>

double r[10], x[10], map[10][10], ans;
int used[10], rx[10];
void dfs(int idx, int n) {
    if(idx == n) {
        double xs = 0;
        int i;
        for(i = 0; i < n; i++)
            if(r[rx[i]]+x[i] > xs)
                xs = r[rx[i]]+x[i];
        if(ans > xs) {
            ans = xs;
        }
        return;
    }
    int i, j, k, f;
    double xs;
    for(i = 0; i < n; i++) {
        if(!used[i]) {
            rx[idx] = i;
            f = 0;
            xs = r[i];
            for(j = idx-1; j >= 0; j--) {
                xs = x[j] + 2*map[i][rx[j]];
                for(k = j-1; k >= 0; k--) {
                    if(xs < 2*map[i][rx[k]] + x[k])
                        break;
                }
                if(k == -1) {
                    f = 1;
                    break;
                }
            }
            if(xs < r[i])   xs = r[i];
            x[idx] = xs;
            if(f == 0 && idx != 0 || xs + r[i] >= ans)
                continue;
            used[i] = 1;
            dfs(idx+1, n);
            used[i] = 0;
        }
    }
}
int main() {
    int n, m, i, j;
    scanf("%d", &n);
    while(n--) {
        scanf("%d", &m);
        memset(used, 0, sizeof(used));
        ans = 0;
        for(i = 0; i < m; i++) {
            scanf("%lf", &r[i]);
            ans += r[i];
        }
        for(i = 0; i < m; i++)
            for(j = 0; j < m; j++)
                map[i][j] = sqrt(r[i]*r[j]);
        ans *= 2;
        dfs(0, m);
        printf("%.3lf\n", ans);
    }
    return 0;
}
