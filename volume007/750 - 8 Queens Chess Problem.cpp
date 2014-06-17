#include <stdio.h>
#include <stdlib.h>
int x[8], y[8], used[8] = {};
int ax, ay, time;
int check(int a, int b, int idx) {
    int i;
    for(i = 0; i < idx; i++)
        if(abs(x[i]-a) == abs(y[i]-b))
            return 0;
    return 1;
}
void dfs(int idx) {
    if(idx == 8) {
        if(y[ay-1] == ax-1) {
            printf("%2d     ", ++time);
            int i;
            for(i = 0; i < 8; i++)
                printf(" %d", y[i]+1);
            puts("");
        }
        return;
    }
    int i;
    for(i = 0; i < 8; i++) {
        if(used[i] == 0 && check(idx, i, idx) != 0) {
            used[i] = 1;
            x[idx] = idx, y[idx] = i;
            dfs(idx+1);
            used[i] = 0;
        }
    }
}
int main() {
    int t, i, j, first = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &ax, &ay);
        if(first)
            puts("");
        first = 1;
        puts("SOLN       COLUMN");
        puts(" #      1 2 3 4 5 6 7 8\n");
        time = 0;
        dfs(0);
    }
    return 0;
}
