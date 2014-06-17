#include <stdio.h>
#define MaxN 20010
int N;
int p[MaxN], r[MaxN];
int find(int x) {
    return x == p[x] ? x : p[x]=find(p[x]);
}
int joint(int x, int y) {
    x = find(x), y = find(y);
    if(x != y) {
        if(r[x] < r[y])
            p[x] = y, r[y] += r[x];
        else
            p[y] = x, r[x] += r[y];
        return 1;
    }
    return 0;
}
void init() {
    for(int i = 0; i < MaxN; i++)
        p[i] = i, r[i] = 1;
}
int enemyID(int x) {
    return x+N;
}
int main() {
    while(scanf("%d", &N) == 1) {
        init();
        int c, x, y;
        while(scanf("%d %d %d", &c, &x, &y) == 3) {
            if(c == 0 && x == 0 && y == 0)  break;
            if(c == 1) { // setFriend
                if(find(x) == find(enemyID(y)) || find(y) == find(enemyID(x)))
                    puts("-1");
                else {
                    joint(x, y);
                    joint(enemyID(x), enemyID(y));
                }
            } else if(c == 2) { // setEnemy
                if(find(x) == find(y) || find(enemyID(x)) == find(enemyID(y)))
                    puts("-1");
                else {
                    joint(x, enemyID(y));
                    joint(y, enemyID(x));
                }
            } else if(c == 3) { // areFriend
                if(find(x) == find(y) || find(enemyID(x)) == find(enemyID(y)))
                    puts("1");
                else
                    puts("0");
            } else { // areEnemy
                if(find(x) == find(enemyID(y)) || find(y) == find(enemyID(x)))
                    puts("1");
                else
                    puts("0");
            }
        }
    }
    return 0;
}
