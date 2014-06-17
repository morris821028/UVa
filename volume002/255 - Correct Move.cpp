#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int K, Q, M;
    while(scanf("%d %d %d", &K, &Q, &M) == 3) {
        if(K == Q) {
            puts("Illegal state");
            continue;
        }
        int map[8][8] = {}, i, j;
        int x, y, r = 0, l = 0, u = 0, d = 0;
        x = K/8, y = K%8;
        map[x][y] = 1; /*King*/
        x = Q/8, y = Q%8;
        for(i = 1; i <= 7; i++) {
            if(r == 0 && !(x+i < 0 || x+i > 7)) {
                if(map[x+i][y] == 1)
                    r = 1;
                else
                    map[x+i][y] = 1;
            }
            if(l == 0 && !(x-i < 0 || x-i > 7)) {
                if(map[x-i][y] == 1)
                    l = 1;
                else
                    map[x-i][y] = 1;
            }
            if(u == 0 && !(y+i < 0 || y+i > 7)) {
                if(map[x][y+i] == 1)
                    u = 1;
                else
                    map[x][y+i] = 1;
            }
            if(d == 0 && !(y-i < 0 || y-i > 7)) {
                if(map[x][y-i] == 1)
                    d = 1;
                else
                    map[x][y-i] = 1;
            }
        }
        if(map[M/8][M%8] == 0 || M == K) {
            puts("Illegal move");
            continue;
        }
        if(abs(K/8-M/8)+abs(K%8-M%8) == 1) {
            puts("Move not allowed");
            continue;
        }
        int stop = 0;
        x = K/8, y = K%8;
        if(x+1 > 7 || x+1 == M/8)   stop++;
        if(x-1 < 0 || x-1 == M/8)   stop++;
        if(y+1 > 7 || y+1 == M%8)   stop++;
        if(y-1 < 0 || y-1 == M%8)   stop++;
        if(stop == 4)
            puts("Stop");
        else
            puts("Continue");
    }
    return 0;
}
