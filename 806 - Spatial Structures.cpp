#include <stdio.h>
#include <algorithm>
using namespace std;
char g[65][65];
struct Node {
    int wb; // 1 white 2 black 3 no
} ND[32767];
int dfs(int k, int lx, int rx, int ly, int ry) {
    int mx = (lx+rx)/2, my = (ly+ry)/2;
    if(lx == rx && ly == ry) {
        ND[k].wb = (g[lx][ly] == '0') ? 1 : 2;
        return ND[k].wb;
    }
    ND[k].wb = 0;
    ND[k].wb |= dfs(k*4-2, lx, mx, ly, my);
    ND[k].wb |= dfs(k*4-1, lx, mx, my+1, ry);
    ND[k].wb |= dfs(k*4, mx+1, rx, ly, my);
    ND[k].wb |= dfs(k*4+1, mx+1, rx, my+1, ry);
    return ND[k].wb;
}
void color(int k, int lx, int rx, int ly, int ry, long long num) {
    int mx = (lx+rx)/2, my = (ly+ry)/2;
    if(num == 0) {
        ND[k].wb = 2;
        int i, j;
        for(i = lx; i <= rx; i++)
            for(j = ly; j <= ry; j++)
                g[i][j] = '*';
        return;
    }
    long long v = num%5;
    if(v == 1)
        color(k*4-2, lx, mx, ly, my, num/5);
    else if(v == 2)
        color(k*4-1, lx, mx, my+1, ry, num/5);
    else if(v == 3)
        color(k*4, mx+1, rx, ly, my, num/5);
    else
        color(k*4+1, mx+1, rx, my+1, ry, num/5);
}
long long buf[32767], bidx;
void pdfs(int k, long long num, long long base) {
    if(ND[k].wb == 1 || ND[k].wb == 2) {
        if(ND[k].wb == 2)
            buf[bidx++] = num;
        return;
    }
    pdfs(k*4-2, num + base, base*5);
    pdfs(k*4-1, num + base*2, base*5);
    pdfs(k*4, num + base*3, base*5);
    pdfs(k*4+1, num + base*4, base*5);
}
int main() {
    int n, i, j;
    int cases = 0, lastop = 0;
    while(scanf("%d", &n) == 1 && n) {
        if(lastop == 1 && n > 0)
            puts("\n");
        if(lastop == 1 && n < 0)
            puts("");
        if(lastop == -1 && n > 0)
            puts("");
        if(n > 0) {
            lastop = 1;
            for(i = 0; i < n; i++)
                scanf("%s", &g[i]);
            dfs(1, 0, n-1, 0, n-1);
            bidx = 0;
            pdfs(1, 0, 1);
            sort(buf, buf+bidx);
            printf("Image %d\n", ++cases);
            if(bidx) {
                for(i = 0; i < bidx; i++) {
                    if(i%12)    putchar(' ');
                    printf("%lld", buf[i]);
                    if((i+1)%12 == 0)
                        puts("");
                }
                if(bidx%12)
                    puts("");
            }
            printf("Total number of black nodes = %d\n", bidx);
        } else {
            lastop = -1;
            n = -n;
            bidx = 0;
            while(scanf("%lld", &buf[bidx]) == 1 && buf[bidx] >= 0)
                bidx++;
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    g[i][j] = '.';
            for(i = 0; i < bidx; i++)
                color(1, 0, n-1, 0, n-1, buf[i]);
            printf("Image %d\n", ++cases);
            for(i = 0; i < n; i++) {
                g[i][n] = 0;
                puts(g[i]);
            }
        }
    }
    return 0;
}
