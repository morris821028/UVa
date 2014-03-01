#include <stdio.h>
#include <map>
#include <math.h>
#include <algorithm>
#include <set>
#include <iostream>
#define dist(a, b) (sqrt(a*a+b*b))
#define eps 1e-12
using namespace std;
struct Pt {
    double x, y, rx, ry;
    int w, in;
};
bool cmp(Pt a, Pt b) {
    if(fabs(a.x-b.x) > eps)
        return a.x < b.x;
    return a.y < b.y;
}
char buffer[32767], bufidx;
void int2str(int n) {
    if(n == 0)  return;
    int2str(n/10);
    buffer[bufidx++] = n%10+'0';
}
Pt p[1024], q[1024], buf[1024], ans[1024];
void solve(int n, int m, int &times) {
    int i, j, ti, tj, tk;
    int mx = 0;
    Pt res[1024];
    set<string> exist;
    for(ti = 0; ti < n; ti++) {
        for(tj = 0; tj < n; tj++) {
            if(ti == tj)    continue;
            for(tk = 0; tk < n; tk++) {
                buf[tk].x = p[tk].x-p[ti].x;
                buf[tk].y = p[tk].y-p[ti].y;
                buf[tk].rx = p[tk].x;
                buf[tk].ry = p[tk].y;
                buf[tk].w = p[tk].w;
                buf[tk].in = p[tk].in;
            }
            double dx = buf[tj].x-buf[ti].x;
            double dy = buf[tj].y-buf[ti].y;
            double r = dist(dx, dy);
            double cos = dx/r, sin = dy/r;
            for(tk = 0; tk < n; tk++) {
                double tx, ty;
                tx = buf[tk].x, ty = buf[tk].y;
                buf[tk].x = (tx*cos + ty*sin)/r;
                buf[tk].y = (-tx*sin + ty*cos)/r;
            }
            sort(buf, buf+n, cmp);
            int idx1 = 0, idx2 = 0, sum = 0;
            while(idx1 < m && idx2 < n) {
                if(fabs(buf[idx2].x-q[idx1].x) < eps &&
                   fabs(buf[idx2].y-q[idx1].y) < eps)
                    res[idx1] = buf[idx2], sum += buf[idx2].w, idx1++, idx2++;
                else
                    idx2++;
            }
            /*for(tk = 0; tk < n; tk++)
                printf("%lf %lf rrr %lf %lf\n", buf[tk].x, buf[tk].y, buf[tk].rx, buf[tk].ry);
            puts("----");*/
            if(idx1 == m) {
                for(tk = 0; tk < m; tk++) {
                    swap(res[tk].x, res[tk].rx);
                    swap(res[tk].y, res[tk].ry);
                }
                sort(res, res+m, cmp);
                bufidx = 0;
                for(tk = 0; tk < m; tk++) {
                    int2str(res[tk].in);
                    buffer[bufidx++] = ' ';
                }
                buffer[bufidx] = '\0';
                if(exist.find(buffer) != exist.end())
                    continue;
                exist.insert(buffer);
                times++;
                if(mx < sum)    mx = sum;
                if(mx == sum) {

                    int flag = 0;
                    for(tk = 0; tk < m; tk++) {
                        if(res[tk].x <= ans[tk].x && res[tk].y < ans[tk].y)
                            flag = 1, tk = m;
                        else if(res[tk].x > ans[tk].x)
                            flag = 2, tk = m;
                        else if(res[tk].x <= ans[tk].x && res[tk].y > ans[tk].y)
                            flag = 2, tk = m;
                    }
                    if(times == 1 || flag == 1)
                        for(tk = 0; tk < m; tk++)
                            ans[tk] = res[tk];
                }
                /*idx1 = idx2 = 0;
                while(idx1 < m && idx2 < n) {
                    if(fabs(buf[idx2].x-q[idx1].x) < eps &&
                       fabs(buf[idx2].y-q[idx1].y) < eps)
                        idx1++, idx2++, printf("%d ", idx1);
                    else
                        idx2++;
                }*/
                //puts("yes yes yes");
            }
        }
    }
}
int main() {
    int n, m, i, j, ti, tj, tk;
    int A[100];
    int cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            scanf("%lf %lf %d", &p[i].x, &p[i].y, &p[i].w);
            p[i].in = i+1;
        }
        printf("Map #%d\n\n", ++cases);
        int query;
        char name[1024];
        scanf("%d", &query);
        while(query--) {
            scanf("%d %s", &m, name);
            for(i = 0; i < m; i++)
                scanf("%lf %lf", &q[i].x, &q[i].y);
            sort(q, q+m, cmp);
            for(i = 1; i < m; i++)
                q[i].rx = q[i].x-q[0].x, q[i].ry = q[i].y-q[0].y;
            q[0].rx = q[0].ry = 0;
            double dx = q[1].rx, dy = q[1].ry;
            double r = dist(dx, dy);
            double cos = dx/r, sin = dy/r;
            for(i = 0; i < m; i++) {
                double tx, ty;
                tx = q[i].rx, ty = q[i].ry;
                q[i].rx = (tx*cos + ty*sin)/r;
                q[i].ry = (-tx*sin + ty*cos)/r;
            }
            for(i = 0; i < m; i++) {
                swap(q[i].x, q[i].rx);
                swap(q[i].y, q[i].ry);
            }
            sort(q, q+m, cmp);

            int times = 0;
            solve(n, m, times);
            puts("");
            printf("%s occurs %d time(s) in the map.\n", name, times);
            if(times) {
                printf("Brightest occurrence:");
                for(i = 0; i < m; i++)
                    printf(" (%d,%d)", (int)ans[i].x, (int)ans[i].y);
                puts("");
            }
        }
        puts("-----");
    }
    return 0;
}
/*
4
1 2 1
2 1 4
4 1 5
4 3 2
1
3 Triangulum
1 1
3 1
2 4
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
Map #1

Triangulum occurs 1 time(s) in the map.
Brightest occurrence: (1,2) (4,1) (4,3)
-----
*/
