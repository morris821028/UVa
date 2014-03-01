#include <stdio.h>
#include <stdlib.h>
int ans[92][9], at = -1;
int y[9], used[9] = {};
int check(int idx, int k) {
    int i;
    for(i = 1; i < idx; i++) {
        if(abs(i-idx) == abs(y[i]-k))
            return 0;
    }
    return 1;
}
void dfs(int idx) {
    int i;
    if(idx == 9) {
        ++at;
        for(i = 1; i <= 8; i++) {
            ans[at][i] = y[i];
        }
        return ;
    }
    for(i = 1; i <= 8; i++) {
        if(!used[i] && check(idx, i)) {
            used[i] = 1;
            y[idx] = i;
            dfs(idx+1);
            used[i] = 0;
        }
    }
}
int main() {
    dfs(1);
    int i, j, cases = 0, a[9];
    while(scanf("%d", &a[1]) == 1) {
        for(i = 2; i <= 8; i++)
            scanf("%d", &a[i]);

        int move = 0xfffff;
        for(i = 0; i <= at; i++) {
            int tmp = 0;
            for(j = 1; j <= 8; j++)
                if(ans[i][j] != a[j])
                    tmp++;
            if(tmp < move)  move = tmp;
        }
        printf("Case %d: %d\n", ++cases, move);
    }
    return 0;
}
