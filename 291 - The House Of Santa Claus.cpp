#include <stdio.h>
int map[5][5] = {
    {0,1,1,0,1},
    {1,0,1,0,1},
    {1,1,0,1,1},
    {0,0,1,0,1},
    {1,1,1,1,0}
    };
int ans[8] = {0};
void DFS(int idx, int now) {
    ans[idx] = now;
    if(idx == 8) {
        for(int i = 0; i < 9; i++)
            printf("%d", ans[i]+1);
        puts("");
        return ;
    }
    int i;
    for(i = 0; i < 5; i++) {
        if(map[now][i] == 1) {
            map[now][i] = map[i][now] = 0;
            DFS(idx+1, i);
            map[now][i] = map[i][now] = 1;
        }
    }
}
int main() {
    DFS(0, 0);
    return 0;

}
