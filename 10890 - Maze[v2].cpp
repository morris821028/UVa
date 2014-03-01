#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int N, S, T, X[35], Y[35];
int ret, U[35];
void dfs(int nd, int cost, int used) {
    if(cost+(N-X[nd]+N-Y[nd]-2)*1.1 >= ret)
        return;
    if(used == S) {
        ret = min(ret, cost+(N-X[nd]+N-Y[nd]-2));
        return;
    }
    int i;
    for(i = 1; i < T; i++) {
        if(!U[i]) {
            U[i] = 1;
            dfs(i, cost+abs(X[i]-X[nd])+abs(Y[i]-Y[nd]), used+1);
            U[i] = 0;
        }
    }
}
int main() {
    int i, j, cases = 0;
    while(scanf("%d %d %d", &N, &T, &S) == 3) {
        if(N+S+T == 0)
            break;
        int g[35][35] = {};
        for(i = 0; i < T; i++) {
            scanf("%d %d", &X[i], &Y[i]);
            g[X[i]][Y[i]]++;
        }
        X[0] = 0, Y[0] = 0;
        T = 1;
        for(i = 0; i < N; i++) {
            for(j = 0; j < N; j++)
                if(g[i][j])
                    X[T] = i, Y[T] = j, T++;
            U[i] = 0;
        }
        ret = 0xffffff;
        dfs(0, 0, 0);
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
/*
4 4 4
2 0
2 1
2 2
0 2
4 4 2
2 0
2 1
2 2
0 2
*/
