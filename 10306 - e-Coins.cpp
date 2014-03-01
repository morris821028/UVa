#include <stdio.h>
int queue[100000][2];
int front, rear;
int main() {
    int t, n, r, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &r);
        int dp[305][305] = {}, x[50], y[50];
        int used[305][305] = {};
        rear = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x[i], &y[i]);
            dp[x[i]][y[i]] = 1;
            used[x[i]][y[i]] = 1;
            queue[rear][0] = x[i];
            queue[rear][1] = y[i];
            rear++;
        }
        int vx, vy, flag = 1;
        front = 0;
        while(front < rear) {
            vx = queue[front][0], vy = queue[front][1];
            if(vx*vx + vy*vy == r*r) {
                printf("%d\n", dp[vx][vy]);
                flag = 0;
                break;
            }
            front++;
            int tx, ty;
            for(i = 0; i < n; i++) {
                tx = vx+x[i], ty = vy+y[i];
                if(tx*tx + ty*ty > r*r) continue;
                if(dp[tx][ty] > dp[vx][vy]+1 || dp[tx][ty] == 0) {
                    dp[tx][ty] = dp[vx][vy]+1;
                    if(!used[tx][ty]) {
                        used[tx][ty] = 1;
                        queue[rear][0] = tx;
                        queue[rear++][1] = ty;
                    }
                }
            }
        }
        if(flag)
            puts("not possible");
    }
    return 0;
}
