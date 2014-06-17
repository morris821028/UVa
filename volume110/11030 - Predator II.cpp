#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;
vector<int> g[30];
int bg[30][30];
int used[30];
struct Pt {
    double x, y;
};
struct Polygon {
    Pt p[20];
    int n;
};
Polygon ply[30];
int parent[30];
int inPolygon(Pt p[], Pt q, int n) {
    int i, j, k = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y)+p[i].x)
           k++;
    }
    return k&1;
}
void build(int nd, int n) {
    int i, j;
    for(i = 0; i <= n; i++) {
        if(used[i] == 0 && inPolygon(ply[nd].p, ply[i].p[0], ply[nd].n)) {
            for(j = 0; j <= n; j++)
                if(i != j && used[j] == 0 && inPolygon(ply[j].p, ply[i].p[0], ply[j].n))
                    break;
            if(j == n+1) {
                used[i] = 1;
                parent[i] = nd;
                g[nd].push_back(i);
                bg[i][nd] = bg[nd][i] = 1;
                build(i, n);
            }
        }
    }
}
int treefind(int nd, Pt p) {
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(inPolygon(ply[*it].p, p, ply[*it].n)) {
            return treefind(*it, p);
        }
    }
    return nd;
}
int main() {
    int t, n, cases = 0;
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d", &ply[i].n);
            for(j = 0; j < ply[i].n; j++)
                scanf("%lf %lf", &ply[i].p[j].x, &ply[i].p[j].y);
        }
        ply[i].n = 4;
        ply[i].p[0].x = -1, ply[i].p[0].y = -1;
        ply[i].p[1].x = -1, ply[i].p[1].y = 10005;
        ply[i].p[2].x = 10005, ply[i].p[2].y = 10005;
        ply[i].p[3].x = 10005, ply[i].p[3].y = -1;
        for(i = 0; i <= n; i++)
            g[i].clear(), used[i] = 0;
        for(i = 0; i <= n; i++) {
            for(j = 0; j <= n; j++)
                bg[i][j] = 0xffff; // oo
            bg[i][i] = 0;
        }
        used[n] = 1;
        build(n, n);
        for(k = 0; k <= n; k++)
            for(i = 0; i <= n; i++)
                for(j = 0; j <= n; j++)
                    if(bg[i][j] > bg[i][k]+bg[k][j])
                        bg[i][j] = bg[i][k]+bg[k][j];
        int Q;
        printf("Case %d:\n", ++cases);
        scanf("%d", &Q);
        while(Q--) {
            Pt st, ed;
            scanf("%lf %lf", &st.x, &st.y);
            scanf("%lf %lf", &ed.x, &ed.y);
            int stp = treefind(n, st);
            int edp = treefind(n, ed);
            printf("%d\n", bg[stp][edp]);
        }
    }
    return 0;
}

