#include <stdio.h>
#include <vector>
#include <queue>
#define SIZE 601
#define maxx 60000
using namespace std;
struct ND {
    int x, y, com;
    ND(int a, int b, int c):
    x(a), y(b), com(c) {}
};
vector<ND> g[maxx/SIZE+1][maxx/SIZE+1];
int main() {
    int t, n, r, x, y, tx, ty;
    int i, j, k;
    int gsize = maxx/SIZE;
    int dirx[9] = {0,0,0,1,1,1,-1,-1,-1};
    int diry[9] = {0,1,-1,0,1,-1,0,1,-1};
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &r);
        for(i = 0; i <= gsize; i++)
            for(j = 0; j <= gsize; j++)
                g[i][j].clear();
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            g[x/SIZE][y/SIZE].push_back(ND(x, y, 0));
        }
        int res = 0;
        for(i = 0; i <= gsize; i++) {
            for(j = 0; j <= gsize; j++) {
                for(vector<ND>::iterator it = g[i][j].begin();
                    it != g[i][j].end(); it++) {
                    if(it->com == 0) {
                        res++;
                        it->com = res;
                        queue<ND> Q;
                        ND tn(0,0,0);
                        Q.push(*it);
                        while(!Q.empty()) {
                            tn = Q.front(), Q.pop();
                            x = tn.x/SIZE, y = tn.y/SIZE;
                            for(k = 0; k < 9; k++) {
                                tx = x+dirx[k], ty = y+diry[k];
                                if(tx < 0 || ty < 0 || tx > gsize || ty > gsize)
                                    continue;
                                for(vector<ND>::iterator jt = g[tx][ty].begin();
                                    jt != g[tx][ty].end(); jt++) {
                                    if(jt->com == 0 && (jt->x-tn.x)*(jt->x-tn.x)+(jt->y-tn.y)*(jt->y-tn.y) <= 4*r*r) {
                                        jt->com = res;
                                        Q.push(ND(jt->x, jt->y, res));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
/*
2

3 100
0 0
100 0
1000 1000

6 300
0 0
0 600
600 0
600 600
10000 0
0 10000
*/
