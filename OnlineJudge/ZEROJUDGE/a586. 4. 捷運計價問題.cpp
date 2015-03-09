#include <stdio.h>
#include <vector>
#define ch(i) (i-'A')
using namespace std;
vector<int> g[2600];
int main() {
    int n, x, y, dis[2600][2], used[2600], i, j;
    char xx[10], yy[10];
    scanf("%d", &n);
    while(n--) {
        scanf("%s %s", xx, yy);
        sscanf(xx+1, "%d", &x);
        sscanf(yy+1, "%d", &y);
        x = ch(xx[0])*100 + x-1;
        y = ch(yy[0])*100 + y-1;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    scanf("%s %s", xx, yy);
    sscanf(xx+1, "%d", &x);
    sscanf(yy+1, "%d", &y);
    x = ch(xx[0])*100 + x-1;
    y = ch(yy[0])*100 + y-1;
    for(i = 0; i < 2600; i++)
        dis[i][0] = dis[i][1] = 0xfffff, used[i] = 0;
    dis[x][0] = dis[x][1] = 0;
    for(i = 0; i < 2600; i++) {
        int mn = 0xffff, tn = -1;
        for(j = 0; j < 2600; j++) {
            if(used[j] == 0 && dis[j][0]/3*5+dis[j][1] < mn)
                mn = dis[j][0]/3*5+dis[j][1], tn = j;
        }
        if(tn < 0)  break;
        used[tn] = 1;
        for(j = 0; j < g[tn].size(); j++) {
            if((g[tn][j]/100 != tn/100)*5+(dis[tn][0]+1)/3*5+dis[tn][1] < dis[g[tn][j]][0]/3*5+dis[g[tn][j]][1]) {
                dis[g[tn][j]][0] = dis[tn][0]+1;
                dis[g[tn][j]][1] = dis[tn][1]+(g[tn][j]/100 != tn/100)*5;
            }
        }
    }
    printf("%d\n", dis[y][0]/3*5+dis[y][1]+10);
    return 0;
}
