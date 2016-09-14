#include <stdio.h>
#include <algorithm>
using namespace std;
struct LINE {
    double st, ed, y;
};
int main() {
    int n, m;
    while(scanf("%d", &n) == 1) {
        double a, b, sum;
        double P[500];
        LINE F[105], G[105];
        int cnt = 0, i;
        for(i = 0, sum = 0; i < n; i++) {
            scanf("%lf %lf", &a, &b);
            F[i].st = sum, F[i].ed = sum+b;
            F[i].y = a;
            P[cnt++] = sum, P[cnt++] = sum+b;
            sum += b;
        }
        scanf("%d", &m);
        for(i = 0, sum = 0; i < m; i++) {
            scanf("%lf %lf", &a, &b);
            G[i].st = sum, G[i].ed = sum+b;
            G[i].y = a;
            P[cnt++] = sum, P[cnt++] = sum+b;
            sum += b;
        }
        double res = 1e+10;
        sort(P, P+cnt);
        int pf = 0, pg = 0;
        for(i = 0; i < cnt; i++) {
            while(F[pf].ed < P[i])  pf++;
            while(G[pg].ed < P[i])  pg++;
            res = min(max(F[pf].y, G[pg].y), res);
        }
        printf("%.3lf\n", res);
    }
    return 0;
}

