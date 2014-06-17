#include <stdio.h>
#include <vector>
#include <queue>
#define SIZE 500
#define maxx 100000
using namespace std;
struct ND {
    int x, y, idx;
    ND(int a, int b, int c) :
    x(a), y(b), idx(c) {}
};
struct PT {
    int x, y;
    PT(int a, int b) :
    x(a), y(b) {}
};
vector<ND> g[maxx/SIZE+1][maxx/SIZE+1];
int main() {
    int t, n, x, y, tx, ty;
    int i, j, k;
    int gsize = maxx/SIZE;
    int dirx[9] = {0,0,0,1,1,1,-1,-1,-1};
    int diry[9] = {0,1,-1,0,1,-1,0,1,-1};
    int out[50005];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i <= gsize; i++)
            for(j = 0; j <= gsize; j++)
                g[i][j].clear();
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            g[x/SIZE][y/SIZE].push_back(ND(x, y, i));
        }
        char used[201][201] = {}; // gsize
        for(i = 0; i <= gsize; i++) {
            for(j = 0; j <= gsize; j++) {
                for(vector<ND>::iterator it = g[i][j].begin();
                    it != g[i][j].end(); it++) {
                    //printf("%d %d\n", it->x, it->y);
                    queue<PT> Q, CLR;
                    PT tn(0,0);
                    Q.push(PT(i, j));
                    long long r = 1LL<<60, dist;
                    int label, flag;
                    while(!Q.empty()) {
                        tn = Q.front(), Q.pop();
                        CLR.push(tn);
                        x = tn.x, y = tn.y;
                        flag = 0;
                        for(vector<ND>::iterator jt = g[x][y].begin();
                            jt != g[x][y].end(); jt++) {
                            dist = (it->x-jt->x)*(it->x-jt->x)+(it->y-jt->y)*(it->y-jt->y);
                            if(jt->idx != it->idx && (dist < r || dist == r && jt->idx < label)) {
                                r = dist;
                                label = jt->idx;
                                flag = 1;
                            }
                        }
                        if(flag) {
                            for(k = 0; k < 9; k++) {
                                tx = x+dirx[k], ty = y+diry[k];
                                if(tx < 0 || ty < 0 || tx > gsize || ty > gsize)
                                    continue;
                                if(used[tx][ty])
                                    continue;
                                Q.push(PT(tx, ty));
                            }
                        }
                    }
                    while(!CLR.empty()) {
                        tn = CLR.front(), CLR.pop();
                        used[tn.x][tn.y] = 0;
                    }
                    out[it->idx] = label;
                }
            }
        }
        for(i = 0; i < n; i++)
            printf("%d\n", out[i]+1);
    }
    return 0;
}
/*
2
3
0 0
1 1
2 2
3
0 0
2 2
3 3
*/
