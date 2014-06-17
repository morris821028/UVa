#include <stdio.h>
#include <vector>
using namespace std;

vector<int> g[256];
int flag, co[256], A, B;
void dfs(int nd, int f) {
    if(flag)    return;
    co[nd] = f;
    if(f == 0)  A++;
    else        B++;
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(co[*it] == -1) {
            dfs(*it, 1-f);
        }
    }
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(co[*it] == f)
            flag = 1;
    }
}
int main() {
    int n, x, y, i;
    scanf("%*d");
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            g[i].clear(), co[i] = -1;
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            while(x--) {
                scanf("%d", &y);
                y--;
                if(y >= n)   continue;
                g[i].push_back(y);
                g[y].push_back(i);
            }
        }
        int ans = 0;
        for(i = 0; i < n; i++) {
            if(co[i] == -1) {
                A = 0, B = 0;
                flag = 0;
                dfs(i, 0);
                if(flag)    continue;
                ans += A > B ? A : B;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
3

5
1 3
1 1
0
1 5
0

8
2 4 5
2 1 3
0
0
0
1 3
0
1 5

3
2 2 3
1 3
1 1
*/
