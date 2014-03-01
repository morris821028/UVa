#include <stdio.h>
#include <vector>
using namespace std;
int main() {
    int n, g[100][100];
    int i, j, k;
    vector<int> gv[100];
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++) {
            gv[i].clear();
            for(j = 0; j < n; j++) {
                scanf("%d", &g[i][j]);
                if(g[i][j])
                    gv[i].push_back(j);
            }
        }
        int time = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < gv[i].size(); j++) {
                for(k = 0; k < gv[gv[i][j]].size(); k++) {
                    if(gv[gv[i][j]][k] != i && g[gv[gv[i][j]][k]][i] == 1) {
                        if((i+1 < gv[i][j]+1 && gv[i][j]+1 < gv[gv[i][j]][k]+1) ||
                            (i+1 > gv[i][j]+1 && gv[i][j]+1 > gv[gv[i][j]][k]+1) )
                            printf("%d %d %d\n", i+1, gv[i][j]+1, gv[gv[i][j]][k]+1), time++;
                    }
                }
            }
        }
        printf("total:%d\n", time);
        puts("");
    }
    return 0;
}
