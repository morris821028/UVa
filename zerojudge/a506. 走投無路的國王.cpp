#include <iostream>
#include <map>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define SET(T, x) (T.v[(x)>>5] |= 1<<((x)&31))
#define GET(T, x) (T.v[(x)>>5]>>(x&31)&1)
#define NOT(T, x) (T.v[x] = ~T.v[x])
#define RESET(T, x) (NOT(T, x>>5), SET(T, x), NOT(T, x>>5))
using namespace std;

int n, m, i, j;
int V;
struct state {
    unsigned int *v;
    state(int V) {
        v = new unsigned int[V];
        int i;
        for(i = 0; i < V; i++)
            v[i] = 0;
    }
    ~state() {
        delete[] v;
    }
};
struct statecmp {
    bool operator() (const state &a, const state &b) {
        static int i;
        for(i = 0; i < V; i++)
            if(a.v[i] != b.v[i])
                return a.v[i] < b.v[i];
        return true;
    }
};
map<state, char, statecmp> dp;
int dfs(int ix, int iy, int dep, state &buf) {
    map<state, char, statecmp>::iterator it;
    it = dp.find(buf);
    if(it != dp.end())  return it->second;
    int res = 0, tx, ty, i, j, idx1, idx2;
    for(i = -1; i <= 1; i++) {
        for(j = -1; j <= 1; j++) {
            if(ix+i < 0 || ix+i >= n ||
               iy+j < 0 || iy+j >= m)
                continue;
            if(i == 0 && j == 0)    continue;
            tx = ix+i, ty = iy+j;
            idx1 = tx*m+ty, idx2 = ix*m+iy;
            if(!GET(buf, (idx1)*2+1)) { // '.'
                SET(buf, idx1*2);
                SET(buf, idx1*2+1);
                //buf[tx*m+ty] = 'K'; //11
                RESET(buf, idx2*2);
                SET(buf, idx2*2+1);
                //buf[ix*m+iy] = '#'; //01
                res |= !dfs(tx, ty, dep+1, buf);
                RESET(buf, idx1*2);
                RESET(buf, idx1*2+1);
                //buf[tx*m+ty] = '.'; //00
                SET(buf, idx2*2);
                SET(buf, idx2*2+1);
                //buf[ix*m+iy] = 'K'; //11
                if(res) i = 3, j = 3;
            }
        }
    }
    dp[buf] = res;
    return res;
}
int main() {
    int t;
    scanf("%d", &t);
    char g[105][105];
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%s", &g[i]);
        V = ((n*m*2)>>5)+1;
        state buf(V);
        dp.clear();
        int idx = 0, ix, iy;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(g[i][j] == '.') {//00
                    RESET(buf, idx*2);
                    RESET(buf, idx*2+1);
                } else if(g[i][j] == '#') { //01
                    RESET(buf, idx*2);
                    SET(buf, idx*2+1);
                } else { // K 11
                    SET(buf, idx*2);
                    SET(buf, idx*2+1);
                }
                idx++;
                //buf = g[i][j];
                if(g[i][j] == 'K')
                    ix = i, iy = j;
            }
        }
        int ans = dfs(ix, iy, 0, buf);
        if(ans) puts("Ting");
        else    puts("Wen");
    }
    return 0;
}
/*
2
2 3
K..
.##
3 4
.#.#
#.#.
K#.#
*/
