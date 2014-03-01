#include <stdio.h>
#include <stdlib.h>

struct Pt {
    float x, y;
};
struct Polygon {
    Pt p[20];
    int n;
};
int inPolygon(Pt p[], Pt q, int n) {
    int i, j, k = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y)+p[i].x)
           k++;
    }
    return k&1;
}
int main() {
    int t, n, cases = 0;
    int i, j, k;
    Polygon ply[30];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d", &ply[i].n);
            for(j = 0; j < ply[i].n; j++)
                scanf("%f %f", &ply[i].p[j].x, &ply[i].p[j].y);
        }
        int Q;
        Pt st, ed;
        printf("Case %d:\n", ++cases);
        scanf("%d", &Q);
        while(Q--) {
            scanf("%f %f", &st.x, &st.y);
            scanf("%f %f", &ed.x, &ed.y);
            int res = n;
            for(i = 0; i < n; i++)
                res -= inPolygon(ply[i].p, st, ply[i].n) ==
                        inPolygon(ply[i].p, ed, ply[i].n);
            printf("%d\n", res);
        }
    }
    return 0;
}

