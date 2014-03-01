#include <stdio.h>
#include <map>
#include <math.h>
#include <algorithm>
#define dist(a, b) (sqrt(a*a+b*b))
#define eps 1e-6
using namespace std;
struct Pt {
    double x, y;
};
bool cmp(Pt a, Pt b) {
    if(fabs(a.x-b.x) > eps)
        return a.x < b.x;
    return a.y < b.y;
}
int main() {
    int n, m, i, j, ti, tj, tk;
    Pt p[100][100], q[100], buf[100];
    int A[100];
    int testcases = 0;
    scanf("%d", &testcases);
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            for(j = 0; j < A[i]; j++)
                scanf("%lf %lf", &p[i][j].x, &p[i][j].y);
            for(j = 1; j < A[i]; j++)
                p[i][j].x -= p[i][0].x, p[i][j].y -= p[i][0].y;
            p[i][0].x = p[i][0].y = 0;
            double dx = p[i][1].x, dy = p[i][1].y;
            double r = dist(dx, dy);
            double cos = dx/r, sin = dy/r;
            for(j = 0; j < A[i]; j++) {
                double tx, ty;
                tx = p[i][j].x, ty = p[i][j].y;
                p[i][j].x = (tx*cos + ty*sin)/r;
                p[i][j].y = (-tx*sin + ty*cos)/r;
            }
            sort(p[i], p[i]+A[i], cmp);
        }
        scanf("%d", &m);
        int exist[100] = {}, vi;
        for(i = 0; i < m; i++) {
            scanf("%d", &vi);
            for(j = 0; j < vi; j++)
                scanf("%lf %lf", &q[j].x, &q[j].y);
            for(j = 0; j < n; j++) {
                if(exist[j] == 1 || A[j] != vi)
                    continue;
                for(ti = 0; ti < vi; ti++) {
                    for(tj = 0; tj < vi; tj++) {
                        if(ti == tj)    continue;
                        for(tk = 0; tk < vi; tk++) {
                            buf[tk].x = q[tk].x-q[ti].x;
                            buf[tk].y = q[tk].y-q[ti].y;
                        }
                        double dx = buf[tj].x-buf[ti].x;
                        double dy = buf[tj].y-buf[ti].y;
                        double r = dist(dx, dy);
                        double cos = dx/r, sin = dy/r;
                        for(tk = 0; tk < vi; tk++) {
                            double tx, ty;
                            tx = buf[tk].x, ty = buf[tk].y;
                            buf[tk].x = (tx*cos + ty*sin)/r;
                            buf[tk].y = (-tx*sin + ty*cos)/r;
                        }
                        sort(buf, buf+vi, cmp);
                        for(tk = 0; tk < vi; tk++) {
                            if(fabs(buf[tk].x-p[j][tk].x) > eps ||
                               fabs(buf[tk].y-p[j][tk].y) > eps)
                               break;
                        }
                        if(tk == vi) {
                            exist[j] = 1;
                            ti = vi, tj = vi;
                        }
                    }
                }
            }
        }
        int cnt = 0;
        for(i = 0; i < n; i++) {
            if(exist[i]) {
                if(cnt) putchar(' ');
                cnt++;
                printf("%d", i+1);
            }
        }
        if(cnt == 0)    printf("so sad");
        puts("");
    }
    return 0;
}
/*
3
2
4 1 4 4 2 4 0 0 0
4 0 0 1 1 0 1 1 0
2
4 1 1 3 9 9 5 9 1
4 0 -3 3 0 0 3 -3 0
1
5 2 7 8 3 1 -1 2 -2 7 -7
2
3 -1 -1 2 -1 0 0
5 2 7 8 3 1 -1 2 -2 6 -7
4
4 0 -2 0 4 4 0 -2 0
4 0 0 1 1 2 2 3 3
5 6 -7 2 7 2 -2 8 3 1 -1
5 0 0 0 8 0 10 2 10 2 8
4
4 -1000 -1000 -500 -500 500 500 0 0
4 1 -2 1 4 4 1 -2 1
5 6 -7 2 7 2 -2 8 3 1 -1
5 0 0 0 8 0 10 -2 10 -2 8
*/
