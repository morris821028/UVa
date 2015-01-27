#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <set>
#include <assert.h>
#include <iostream>
using namespace std;

#define MAXSTATE 1048576
#define HASH_MOD 1007
#define MAXN ((100)>>5)+1
struct state {
    int wall[MAXN], sx, sy;
    int dist, dir;
    state *prev;
    state() {
        memset(wall, 0, sizeof(wall));
        sx = sy = 0;
    }
    void removeWall(int x) {
        wall[x>>5] ^= 1<<(x&31);
    }
    void setWall(int x) {
        wall[x>>5] |= 1<<(x&31);
    }
    int getWall(int x) {
        return wall[x>>5]>>(x&31)&1;
    }
    int canPass(int dir) {
        return !getWall(dir + sy * 4 + sx * 6 * 4);
    }
    unsigned int hash() {
        unsigned int a = 63689, b = 378551;
        unsigned int value = 0;
        for (int i = 0; i < MAXN; i++) {
            value = value * a + wall[i];
            a *= b;
        }
        value = value * a + sx;
        a *= b;
        value = value * a + sy;
        a *= b;
        return value % HASH_MOD;
    }
    bool operator<(const state &a) const {
        for (int i = 0; i < MAXN; i++) {
            if (wall[i] != a.wall[i])
                return wall[i] < a.wall[i];
        }
        if (sx != a.sx) return sx < a.sx;
        if (sy != a.sy) return sy < a.sy;
        return false;
    }
} states[MAXSTATE];
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
const char sdir[] = "WNES";
const int invDir[] = {2, 3, 0, 1};
int stateSize;
set<state> used[HASH_MOD];
int isOuter(int x, int y) {
    return x < 0 || y < 0 || x >= 4|| y >= 6;
}
int isValidPos(int x, int y) {
    return 0 <= x && x < 4 && 0 <= y && y < 6;
}
void printState(state u) {
    printf("(%d, %d)\n", u.sx, u.sy);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            printf(" ");
            if (u.getWall(1 + j * 4 + i * 6 * 4)) {
                printf("_");
            } else {
                printf(" ");
            }
        }
        puts("");
        for (int j = 0; j < 6; j++) {
            if (u.getWall(0 + j * 4 + i * 6 * 4)) {
                printf("|");
            } else {
                printf(" ");
            }
            printf(" ");
        }
        if (u.getWall(2 + 5 * 4 + i * 6 * 4)) {
            printf("|");
        } else {
            printf(" ");
        }
        puts("");
    }
    for (int j = 0, i = 3; j < 6; j++) {
        printf(" ");
        if (u.getWall(3 + j * 4 + i * 6 * 4)) {
            printf("_");
        } else {
            printf(" ");
        }
    }
    puts("\n---");
}
state pushWall(state u, int dir) {
    int tx, ty, ttx, tty;
    state t = u;
    tx = u.sx + dx[dir], ty = u.sy + dy[dir];
    ttx = tx + dx[dir], tty = ty + dy[dir];
    t.sx = tx, t.sy = ty;
    t.setWall(dir + ty * 4 + tx * 6 * 4);
    if (isValidPos(ttx, tty))
        t.setWall(invDir[dir] + tty * 4 + ttx * 6 * 4);
    t.removeWall(dir + u.sy * 4 + u.sx * 6 * 4);
    t.removeWall(invDir[dir] + ty * 4 + tx * 6 * 4);
    return t;
}
void bfs(state init) {
    for (int i = 0; i < HASH_MOD; i++)
        used[i].clear();
    queue<state*> Q;
    state *st, *u, *v, t;
    int tx, ty;
    stateSize = 0;
    st = &states[stateSize++];
    *st = init;
    st->dist = 0, st->prev = NULL;
    Q.push(st), used[st->hash()].insert(*st);
    while (!Q.empty()) {
        assert(stateSize < MAXSTATE);
        u = Q.front(), Q.pop();
        for (int i = 0; i < 4; i++) {
            if (u->canPass(i)) { // no wall
                tx = u->sx + dx[i], ty = u->sy + dy[i];
                if (isOuter(tx, ty)) {
                    string ret(1, sdir[i]);
                    while (u->prev) {
                        ret = sdir[u->dir] + ret;
                        u = u->prev;
                    }
                    printf("%s\n", ret.c_str());
                    return;
                }
                t = *u;
                t.sx = tx, t.sy = ty;
                if (used[t.hash()].count(t))   continue;
                used[t.hash()].insert(t);
                v = &states[stateSize++];
                *v = t;
                v->dist = u->dist + 1, v->prev = u, v->dir = i;
                Q.push(v);
            } else { // try push wall
                tx = u->sx + dx[i], ty = u->sy + dy[i];
                if (isValidPos(tx, ty)) {
                    if (u->getWall(i + ty * 4 + tx * 6 * 4) == 0) {
                        t = pushWall(*u, i);
//                        printf("try push %d , %d %d\n", i, t.sx, t.sy);
//                        printState(t);
                        if (used[t.hash()].count(t))   continue;
                        used[t.hash()].insert(t);
                        v = &states[stateSize++];
                        *v = t;
                        v->dist = u->dist + 1, v->prev = u, v->dir = i;
                        Q.push(v);
                    }
                }
            }
        }
    }
    puts("-1");
}
int main() {
    int sx, sy, x;
    while (scanf("%d %d", &sy, &sx) == 2 && sx) {
        sx--, sy--;
        state init;
        init.sx = sx, init.sy = sy;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                scanf("%d", &x);
                for (int k = 0; k < 4; k++) {
                    if ((x>>k)&1)
                        init.setWall(k + j * 4 + i * 6 * 4);
                }
            }
        }
        bfs(init);
    }
    return 0;
}
/*
 2 3
 10 2 10 10 2 6
 3 12 11 14 9 4
 13 15 3 6 15 13
 14 11 12 9 14 11
 0 0
*/