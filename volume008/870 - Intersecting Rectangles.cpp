#include <stdio.h>
#include <algorithm>
using namespace std;

int hasIntersect(int lx, int ly, int rx, int ry,
                int la, int lb, int ra, int rb) {
    lx = max(lx, la);
    ly = max(ly, lb);
    rx = min(rx, ra);
    ry = min(ry, rb);
    return lx < rx && ly < ry;
}
int main() {
    int t, n, i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int lx[105], ly[105], rx[105], ry[105];
        int X[305], Y[305], m = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d %d", &lx[i], &ly[i], &rx[i], &ry[i]);
            X[m] = lx[i], Y[m] = ly[i];
            m++;
            X[m] = rx[i], Y[m] = ry[i];
            m++;
        }
        sort(X, X+m);
        sort(Y, Y+m);
        int Q[105], Qt = 0, used[105] = {};
        Q[Qt] = 0, used[0] = 1;
        for(i = 0; i <= Qt; i++) {
            k = Q[i];
            for(j = 0; j < n; j++) {
                if(used[j]) continue;
                if(hasIntersect(lx[k], ly[k], rx[k], ry[k], lx[j], ly[j], rx[j], ry[j])) {
                    Q[++Qt] = j;
                    used[j] = 1;
                }
            }
        }
        n = Qt;
        int ans = 0;
        for(i = 1; i < m; i++) {
            for(j = 1; j < m; j++) {
                for(k = 0; k <= n; k++) {
                    if(X[i-1] >= lx[Q[k]] && X[i] <= rx[Q[k]] &&
                       Y[j-1] >= ly[Q[k]] && Y[j] <= ry[Q[k]]) {
                        break;
                    }
                }
                if(k != n+1) {
                    ans += (X[i]-X[i-1])*(Y[j]-Y[j-1]);
                }
            }
        }
        printf("%d\n", ans);
        if(t)
            puts("");
    }
    return 0;
}
