#include <stdio.h>
#include <math.h>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
struct Pt {
    int x, y, w;
    bool operator<(const Pt &a) const {
        if(x != a.x)
            return x < a.x;
        return y < a.y;
    }
};
struct St {
    int V[(1000>>5)+1];
    St() {
        memset(V, 0, sizeof(V));
    }
    bool operator<(const St &a) const {
        return memcmp(V, a.V, sizeof(V)) > 0;
    }
};
int main() {
    int n, m, q, i, j, k;
    Pt star[1005];//stars in sky
    int cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        map<int, map<int, int> > R;
        for(i = 0; i < n; i++)
            scanf("%d %d %d", &star[i].x, &star[i].y, &star[i].w);
        sort(star, star+n);
        for(i = 0; i < n; i++) {
            R[star[i].x][star[i].y] = i;
        }
        scanf("%d", &q);
        char name[205];
        int buffer[105], res[105];
        Pt con[105];//constellation
        printf("Map #%d\n", ++cases);
        while(q--) {
            scanf("%d %s", &m, &name);
            for(i = 0; i < m; i++)
                scanf("%d %d", &con[i].x, &con[i].y);
            int times = 0, light = 0, slight;
            map<St, int> hash;
            for(i = 0; i < n; i++) {
                for(j = 0; j < n; j++) {
                    if(i == j && m != 1)  continue;
                    double theta1 = atan2(star[j].y-star[i].y, star[j].x-star[i].x);
                    double theta2 = atan2(con[1].y-con[0].y, con[1].x-con[0].x);
                    double rtheta = theta1 - theta2;
                    double disp = pow(star[j].x-star[i].x,2)+pow(star[j].y-star[i].y,2);
                    double disq = pow(con[1].x-con[0].x,2)+pow(con[1].y-con[0].y,2);
                    double scaling = sqrt(disp/disq);
                    slight = 0;
                    //printf("%d %d %d %d\n", star[i].x, star[i].y, star[j].x, star[j].y);
                    //printf("%lf %lf\n", rtheta, scaling);
                    for(k = 0; k < m; k++) {
                        double tx = con[k].x-con[0].x;
                        double ty = con[k].y-con[0].y;
                        double rx, ry;
                        rx = tx*cos(rtheta) - ty*sin(rtheta);
                        ry = tx*sin(rtheta) + ty*cos(rtheta);
                        rx *= scaling;
                        ry *= scaling;
                        rx += star[i].x;
                        ry += star[i].y;
                        int ix, iy;
#define eps 1e-6
                        ix = (int)floor(rx+eps);
                        iy = (int)floor(ry+eps);
                        //printf("%d %d\n", ix, iy);
                        if(fabs(rx-ix) > eps || fabs(ry-iy) > eps)
                            break;
                        map<int, map<int, int> >::iterator xt = R.find(ix);
                        if(xt == R.end())
                            break;
                        map<int, int>::iterator yt = (xt->second).find(iy);
                        if(yt == (xt->second).end())
                            break;
                        slight += star[yt->second].w;
                        buffer[k] = yt->second;

                    }
                    if(k == m) {
                        if(slight > light)
                            light = slight;
                        St val;
                        for(k = 0; k < m; k++)
                            val.V[buffer[k]>>5] |= 1<<(buffer[k]&31);
                        hash[val] = slight;
                    }
                    //puts("---");
                }
            }
            puts("");
            times = hash.size();
            printf("%s occurs %d time(s) in the map.\n", name, times);
            if(times) {
                int first = 0;
                for(map<St, int>::iterator it = hash.begin();
                    it != hash.end(); it++) {
                    if(it->second == light) {
                        for(i = 0, j = 0; i < n; i++) {
                            if((it->first).V[i>>5]>>(i&31)&1)
                                res[j++] = i;
                        }
                        break;
                    }
                }
                printf("Brightest occurrence:");
                for(i = 0; i < m; i++)
                    printf(" (%d,%d)", star[res[i]].x, star[res[i]].y);
                puts("");
            }
        }
        puts("-----");
    }
    return 0;
}
/*
Map #10

Point occurs 1 time(s) in the map.
Brightest occurrence: (1,1)

Line occurs 0 time(s) in the map.

Triangulum occurs 0 time(s) in the map.

Cancer occurs 0 time(s) in the map.
-----
*/
