#include <stdio.h>
#include <algorithm>
using namespace std;
void calcAdj(int w, int h, int g[][105], int ans[]) {
    int i, j, k, cnt;
    static int L[105][105], R[105][105], U[105][105], D[105][105];
    for(i = 0; i < w; i++)
        for(j = 0, cnt = 0; j < h; j++)
            cnt = g[i][j] ? cnt+g[i][j]:0, L[i][j] = cnt;

    for(i = 0; i < w; i++)
        for(j = h-1, cnt = 0; j >= 0; j--)
            cnt = g[i][j] ? cnt+g[i][j]:0, R[i][j] = cnt;

    for(j = 0; j < h; j++)
        for(i = 0, cnt = 0; i < w; i++)
            cnt = g[i][j] ? cnt+g[i][j]:0, U[i][j] = cnt;

    for(j = 0; j < h; j++)
        for(i = w-1, cnt = 0; i >= 0; i--)
            cnt = g[i][j] ? cnt+g[i][j]:0, D[i][j] = cnt;
    k = 0;
    for(i = 0; i < w; i++) {
        for(j = 0; j < h; j++) {
            if(g[i][j])
                ans[k++] = L[i][j]+R[i][j]+U[i][j]+D[i][j];
        }
    }
    sort(ans, ans+k);
}
int main() {
    int testcase;
    int W, H, n, i, x, y;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &W, &H, &n);
        int g1[105][105] = {}, g2[105][105] = {};
        int adj1[3005], adj2[3005];
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            g1[x][y] = 1;
        }
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            g2[x][y] = 1;
        }
        calcAdj(W, H, g1, adj1);
        calcAdj(W, H, g2, adj2);
        for(i = 0; i < n; i++) {
            if(adj1[i] != adj2[i])
                break;
        }
        if(i == n)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
