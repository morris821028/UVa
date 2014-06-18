#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define eps 1e-6
struct Pt {
    float x, y;
    bool operator<(const Pt &a) const {
        if(a.x != x)
            return x < a.x;
        return y < a.y;
    }
};
struct Seg {
    Pt s, t;
};
float cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
void convexHull(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int m = 0, i, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
}
int onLine(Seg a, Pt p) {
    if((a.s.x-a.t.x)*(p.y-a.s.y) != (a.s.y-a.t.y)*(p.x-a.s.x))
        return 0;
    if(p.x < a.s.x && p.x < a.t.x)
        return 0;
    if(p.x > a.s.x && p.x > a.t.x)
        return 0;
    if(p.y < a.s.y && p.y < a.t.y)
        return 0;
    if(p.y > a.s.y && p.y > a.t.y)
        return 0;
    return 1;
}
int intersection(Seg a, Seg b) {
    if(onLine(a, b.s) || onLine(a, b.t) ||
        onLine(b, a.s) || onLine(b, a.t))
        return 1;
    if(cross(a.s, a.t, b.s)*cross(a.s, a.t, b.t) < 0 &&
       cross(a.t, a.s, b.s)*cross(a.t, a.s, b.t) < 0 &&
       cross(b.s, b.t, a.s)*cross(b.s, b.t, a.t) < 0 &&
       cross(b.t, b.s, a.s)*cross(b.t, b.s, a.t) < 0)
       return 1;
    return 0;
}
int g[2005][4005], gt[2005];
void addEdge(int x, int y) {
    //printf("%d -> %d\n", x, y);
    //g[x].push_back(y);
    g[x][gt[x]++] = y;
}
int vfind[2005], findIdx;
int stk[2005], stkIdx;
int in_stk[2005], visited[2005];
int vgroup[2005];
int scc_cnt;
int scc(int nd) {
    //printf("%d\n", nd);
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    /*for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(!visited[*it])
            mn = min(mn, scc(*it));
        if(in_stk[*it])
            mn = min(mn, vfind[*it]);
    }*/
    for(int i = 0; i < gt[nd]; i++) {
        if(!visited[g[nd][i]]) {
            mn = min(mn, scc(g[nd][i]));
            //printf("%d --> %d\n", nd, g[nd][i]);
        }
        if(in_stk[g[nd][i]]){
            mn = min(mn, vfind[g[nd][i]]);
           // printf("%d %d %d\n", nd, g[nd][i], vfind[g[nd][i]]);
        }
    }
    //printf("%d : %d %d\n", nd, mn, vfind[nd]);
    if(mn == vfind[nd]) {
        do {
            in_stk[stk[stkIdx]] = 0;
            vgroup[stk[stkIdx]] = scc_cnt;
            //printf("%d ", stk[stkIdx]);
        } while(stk[stkIdx--] != nd);
        scc_cnt++;
    }
    return mn;
}
int main() {
    int n;
    int i, j;
    Pt p[4], rect[1000][10];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < 4; j++)
                scanf("%f %f", &p[j].x, &p[j].y);
            convexHull(4, p, rect[i]);
        }
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        memset(gt, 0, sizeof(gt));
        //for(i = 2*n; i >= 0; i--)
        //    g[i].clear();
        for(i = 0; i < n; i++) {
            //printf("%lf %lf %lf %lf\n", rect[i][0].x, rect[i][0].y, rect[i][2].x, rect[i][2].y);
            //printf("%lf %lf %lf %lf\n\n", rect[i][1].x, rect[i][1].y, rect[i][3].x, rect[i][3].y);
            //diagonal val(i<<1), another diagonal !val(i<<1|1)
            for(j = 0; j < i; j++) {
                Seg a, b;
                a.s = rect[i][0], a.t = rect[i][2];
                b.s = rect[j][0], b.t = rect[j][2];
                int f1, f2, f3, f4;
                f1 = intersection(a, b);
                a.s = rect[i][0], a.t = rect[i][2];
                b.s = rect[j][1], b.t = rect[j][3];
                f2 = intersection(a, b);
                a.s = rect[i][1], a.t = rect[i][3];
                b.s = rect[j][0], b.t = rect[j][2];
                f3 = intersection(a, b);
                a.s = rect[i][1], a.t = rect[i][3];
                b.s = rect[j][1], b.t = rect[j][3];
                f4 = intersection(a, b);
                if(f1) {
                    addEdge(i<<1, j<<1|1);
                    addEdge(j<<1, i<<1|1);
                }
                if(f2) {
                    addEdge(i<<1, j<<1);
                    addEdge(j<<1|1, i<<1|1);
                }
                if(f3) {
                    addEdge(i<<1|1, j<<1|1);
                    addEdge(j<<1, i<<1);
                }
                if(f4) {
                    addEdge(i<<1|1, j<<1);
                    addEdge(j<<1|1, i<<1);
                }
            }
        }
        scc_cnt = 1;
        for(i = 0; i < 2*n; i++) {
            if(!visited[i]) {
                stkIdx = -1;
                findIdx = 0;
                scc(i);
            }
        }
        int hasSolution = 1;
        for(i = 0; i < n; i++)
            if(vgroup[i<<1] == vgroup[i<<1|1])
                hasSolution = 0;
        puts(hasSolution ? "YES" : "NO");
    }
    return 0;
}
/*
2-SAT
ex. (A | B)&(!A | B) has a solution?
*/
