#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int g[1025][1025];
int main() {
    int testcase, n, d;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &d, &n);
        memset(g, 0, sizeof(g));
        int x, y, size;
        int i, j, xl, xr, yl, yr;
        while(n--) {
            scanf("%d %d %d", &x, &y, &size);
            xl = max(0, x-d), xr = min(x+d, 1024);
            yl = max(0, y-d), yr = min(y+d, 1024);
            for(i = xl; i <= xr; i++)
                for(j = yl; j <= yr; j++)
                    g[i][j] += size;
        }
        int mx = -1, rx, ry;
        for(i = 0; i < 1025; i++)
            for(j = 0; j < 1025; j++)
                if(g[i][j] > mx)
                    mx = g[i][j], rx = i, ry = j;
        printf("%d %d %d\n", rx, ry, mx);
    }
    return 0;
}
