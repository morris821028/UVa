#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
typedef struct {
    int x, v;
} arc;
vector<arc> g[505];
string LEV[505][2], line;
int lev[505];
int gg[4][4] = {
    {1,5,3,10},{5,1,5,10},{3,5,1,10},{10,10,10,1}
};
int poss[505] = {1,3,5};
int poss2[505] = {1,3,5};
int spfa(int st, int ed, int n) {
    int i, j;
    int dist[505], used[505] = {};
    for(i = 0; i <= n; i++)
        dist[i] = 0xfffff;
    dist[st] = poss2[poss[st]];
    queue<int> Q;
    Q.push(st);
    while(!Q.empty()) {
        int tn = Q.front();
        Q.pop();
        used[tn] = 0;
        for(vector<arc>::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            if(dist[it->x] > dist[tn]+it->v+poss2[poss[it->x]]+gg[lev[tn]][lev[it->x]]) {
                dist[it->x] = dist[tn]+it->v+poss2[poss[it->x]]+gg[lev[tn]][lev[it->x]];
                Q.push(it->x);
                printf("%d -> %d %d %d\n", tn, it->x, dist[it->x], dist[tn]);
            }
        }
    }
    return dist[ed];
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        int n, Q, x, y, v;
        scanf("%d %d", &n, &Q);
        cin.ignore(100, '\n');
        for(i = 1; i <= n; i++)
            g[i].clear();
        for(i = 0; i < n; i++) {
            getline(cin, line);
            stringstream sin;
            sin << line;
            sin >> x;
            sin >> LEV[x][0] >> LEV[x][1];
            if(LEV[x][0] == "I")    lev[x] = 0;
            else if(LEV[x][0] == "R")    lev[x] = 1;
            else if(LEV[x][0] == "P")    lev[x] = 2;
            else if(LEV[x][0] == "E")    lev[x] = 3;
            if(LEV[x][1] == "S")    poss[x] = 0;
            else if(LEV[x][1] == "I")    poss[x] = 1;
            else if(LEV[x][1] == "P")    poss[x] = 2;
            while(sin >> y >> v) {
                arc tmp;
                tmp.x = y, tmp.v = v;
                g[x].push_back(tmp);
            }
        }
        string mis;
        int st, ed;
        while(Q--) {
            cin >> mis >> st >> ed;
            int time = spfa(st, ed, n);
            printf("%d\n", time);
        }
        if(t)
            puts("==========");
    }
    return 0;
}/*
2
4 1
1 I S 2 1
2 R I 3 6
3 I I 4 2 1 7
4 P I 1 4
A 1 3
10 6
1 R S 2 8
2 I S 3 15 1 15
3 R I 4 14 2 12
4 E S 5 1 3 15
5 P S 6 2 4 4
6 I I 7 12 5 7
7 R S 8 9 6 9
8 P S 9 12 7 11
9 E I 10 10 8 2
10 R I 9 11
B 5 2
S 4 5
A 2 9
B 10 3
A 8 9
S 1 7
*/
