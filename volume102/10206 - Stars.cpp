#include <stdio.h>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;
struct Star {
    int x, y, w;
};
struct cmp {
    bool operator() (const Star a, const Star b) {
        if(a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    }
};
bool scmp(Star a, Star b) {
    if(a.x != b.x)  return a.x < b.x;
    return a.y < b.y;
}
#define dist(a, b) ((long long)(a.x-b.x)*(a.x-b.x)+\
                    (long long)(a.y-b.y)*(a.y-b.y))
#define vlen(a, b) (a*a+b*b)
#define eps 1e-6
int main() {
    int n, m, q, i, j, k;
    Star p[1024], qp[1024], buf[1024], res[1024];
    char cmd[105];
    int cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        map<Star, int, cmp> Exist;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].w);
            Star tmp;
            tmp.x = p[i].x, tmp.y = p[i].y;
            Exist[tmp] = i;
        }
        scanf("%d", &q);
        while(q--) {
            scanf("%d %s", &m, cmd);
            for(i = 0; i < m; i++)
                scanf("%d %d", &qp[i].x, &qp[i].y);
            int occtime = 0, res_avg = 0;
            for(i = 0; i < n; i++) { // first pt
                for(j = 0; j < n; j++) { // second pt
                    if(i == j)  continue;
                    if(dist(p[i], p[j]) != dist(qp[0], qp[1]))
                        continue;
                    // rotate
                    int dx = qp[0].x-p[i].x, dy = qp[0].y-p[i].y;
                    double theta, area;
                    Star va, vb;
                    va.x = p[j].x-p[i].x, va.y = p[j].y-p[i].y;
                    vb.x = qp[1].x-qp[0].x, vb.y = qp[1].y-qp[0].y;
                    area = fabs(va.x*vb.y-va.y*vb.x);
                    theta = asin(area/sqrt(vlen(va.x, va.y))/sqrt(vlen(vb.x, vb.y)));
                    for(k = 0; k < m; k++) {
                        double tx, ty, ttx, tty;
                        tx = qp[k].x-qp[0].x;
                        ty = qp[k].y-qp[0].y;
                        ttx = tx*cos(theta)-ty*sin(theta);
                        tty = tx*sin(theta)+ty*cos(theta);
                        ttx += p[i].x, tty += p[i].y;
                        if(fabs(ttx-round(ttx)) < eps && fabs(tty-round(tty)) < eps) {
                            Star tmp;
                            tmp.x = (int)round(ttx), tmp.y = (int)round(tty);
                            if(Exist.find(tmp) == Exist.end())
                                break;
                            buf[k] = p[Exist[tmp]];
                        } else
                            break;
                    }
                    if(k == m) {
                        occtime++;
                        int sum = 0;
                        for(int l = 0; l < m; l++)
                            sum += buf[l].w;
                        if(sum > res_avg)
                            res_avg = sum;
                        if(sum == res_avg) {
                            sort(buf, buf+m, scmp);
                            for(int l = 0; l < m; l++)
                                res[l] = buf[l];
                        }
                    }
                }
            }
            printf("Map #%d\n", ++cases);
            printf("\n%s occurs %d time(s) in the map.\n", cmd, occtime);
            printf("Brightest occurrence:");
            for(i = 0; i < m; i++)
                printf(" (%d,%d)", res[i].x, res[i].y);
            puts("\n-----");
        }
    }
    return 0;
}
/*
4
0 0 1
1 0 1
1 1 1
0 1 1
1
4 Rect
0 0
1 0
1 1
0 1
*/
