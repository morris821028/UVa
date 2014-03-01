#include <stdio.h>
#include <algorithm>
using namespace std;
int g[305][305], gt[305];
int invg[305][305], invgt[305], to[305];
int check(int n) {
    int i, j, k;
    for(i = n-1; i >= 0; i--) {
        for(j = 0; j < n; j++)  to[j] = 0;
        for(j = invgt[i]-1; j >= 0; j--) {
            for(k = gt[invg[i][j]]-1; k >= 0; k--) {
                to[g[invg[i][j]][k]]++;
            }
        }
        for(j = 0; j < n; j++) {
            if(to[j] == 0 || to[j] == invgt[i])
                {}
            else
                return 0;
        }
    }
    return 1;
}
int main() {
    int t, cases = 0;
    int n, m, i, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            gt[i] = 0, invgt[i] = 0;
        while(m--) {
            scanf("%d %d", &x, &y);
            g[x][gt[x]++] = y;
            invg[y][invgt[y]++] = x;
        }
        int flag = check(n);
        printf("Case #%d: %s\n", ++cases, flag ? "Yes" : "No");
    }
    return 0;
}
