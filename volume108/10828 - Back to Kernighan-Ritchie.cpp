#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
double sol[105];
int nosol[105];
void gaussianElimination(double mtx[][105], int n) {
#define eps 1e-8
    int i, j;
    for(i = 1; i <= n; i++) {
        int k = i;
        for(j = i+1; j <= n; j++)
            if(fabs(mtx[k][i]) < fabs(mtx[j][i]))
                k = j;
        if(fabs(mtx[k][i]) < eps)
            continue;
        if(k != i) {
            for(j = 1; j <= n+1; j++)
                swap(mtx[k][j], mtx[i][j]);
        }
        for(j = 1; j <= n; j++) {
            if(i == j)  continue;
            for(k = n+1; k >= i; k--) {
                mtx[j][k] -= mtx[j][i]/mtx[i][i]*mtx[i][k];
            }
        }
    }
    memset(nosol, 0, sizeof(nosol));
    for(i = n; i >= 1; i--) {
        if(fabs(mtx[i][n+1]) > eps && fabs(mtx[i][i]) < eps)
            nosol[i] = 1;
        else {
            if(fabs(mtx[i][n+1]) < eps)
                sol[i] = 0;
            else
                sol[i] = mtx[i][n+1]/mtx[i][i];
        }
        for(j = i+1; j <= n; j++)
            if(fabs(mtx[i][j]) > eps && nosol[j])
                nosol[i] = 1;
    }
}
int main() {
    int cases = 0;
    int n, x, y, i, j;
    while(scanf("%d", &n) == 1 && n) {
        vector<int> invg[105];
        int deg[105] = {};
        while(scanf("%d %d", &x, &y) == 2) {
            if(x == 0 && y == 0)
                break;
            deg[x]++;
            invg[y].push_back(x);
        }
        double mtx[105][105];
        memset(mtx, 0, sizeof(mtx));
        mtx[1][n+1] = 1;
        for(i = 1; i <= n; i++) {
            mtx[i][i] = 1;
            for(j = 0; j < invg[i].size(); j++)
                mtx[i][invg[i][j]] -= 1.0/deg[invg[i][j]];
        }
        gaussianElimination(mtx, n);
        printf("Case #%d:\n", ++cases);
        scanf("%d", &x);
        while(x--) {
            scanf("%d", &y);
            if(nosol[y])
                puts("infinity");
            else
                printf("%.3lf\n", sol[y]);
        }
    }
    return 0;
}
/*
E[j] = sigma(E[i]*(1/deg[i])), if i->j exists.
*/
