#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int q[250000][2];
int main() {
    int i, j, idx = 2;
    int px[10025], py[10025];
    px[1] = py[1] = 0;
    for(i = 1; idx < 10005; i++) {
        px[idx] = px[idx-1], py[idx] = py[idx-1]+1;
        idx++;
        for(j = 1; j < i && idx < 10005; j++, idx++)
            px[idx] = px[idx-1]-1, py[idx] = py[idx-1]+1;

        px[idx] = px[idx-1]-1, py[idx] = py[idx-1];
        idx++;
        for(j = 1; j < i && idx < 10005; j++, idx++)
            px[idx] = px[idx-1]-1, py[idx] = py[idx-1];

        px[idx] = px[idx-1], py[idx] = py[idx-1]-1;
        idx++;
        for(j = 1; j < i && idx < 10005; j++, idx++)
            px[idx] = px[idx-1], py[idx] = py[idx-1]-1;

        px[idx] = px[idx-1]+1, py[idx] = py[idx-1]-1;
        idx++;
        for(j = 1; j < i && idx < 10005; j++, idx++)
            px[idx] = px[idx-1]+1, py[idx] = py[idx-1]-1;

        px[idx] = px[idx-1]+1, py[idx] = py[idx-1];
        idx++;
        for(j = 1; j < i && idx < 10005; j++, idx++)
            px[idx] = px[idx-1]+1, py[idx] = py[idx-1];

        px[idx] = px[idx-1], py[idx] = py[idx-1]+1;
        idx++;
        for(j = 1; j < i && idx < 10005; j++, idx++)
            px[idx] = px[idx-1], py[idx] = py[idx-1]+1;
    }
    int st, ed;
    while(scanf("%d %d", &st, &ed) == 2) {
        if(st+ed == 0)  break;
        //int used[500][500] = {};
        int sx = px[st], sy = py[st];
        int ex = px[ed], ey = py[ed];

        /*int qidx = 0, i, tx, ty;
        int dir[6][2] = {{0,-1},{-1,0},{1,-1},{1,0},{0,1},{-1,1}};
        used[sx][sy] = 1;
        q[0][0] = sx, q[0][1] = sy;
        for(i = 0; i <= qidx; i++) {
            tx = q[i][0], ty = q[i][1];
            if(tx == ex && ty == ey)
                break;
            for(j = 0; j < 6; j++) {
                if(!used[tx+dir[j][0]][ty+dir[j][1]]) {
                    used[tx+dir[j][0]][ty+dir[j][1]] = used[tx][ty]+1;
                    qidx++;
                    q[qidx][0] = tx+dir[j][0];
                    q[qidx][1] = ty+dir[j][1];
                }
            }
        }*/
        printf("The distance between cells %d and %d is %d.\n", st, ed, (abs(sx-ex)+abs(sy-ey)+abs(sx-ex+sy-ey))/2);
    }
    return 0;
}
