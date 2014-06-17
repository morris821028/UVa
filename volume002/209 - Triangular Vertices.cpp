#include <stdio.h>
#include <math.h>
#include <sstream>
#include <algorithm>
#define eps 1e-6
using namespace std;
double trix[32768], triy[32768];
const double pi = acos(-1);
struct Pt {
    double x, y;
};
bool cmp(Pt a, Pt b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double dist(Pt a, Pt b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
Pt P[1000], CH[1000];
int convex(int n) {
    sort(P, P+n, cmp);
    int m = 0, i, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(CH[m-2], CH[m-1], P[i]) <= 0)
            m--;
        CH[m++] = P[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(CH[m-2], CH[m-1], P[i]) <= 0)
            m--;
        CH[m++] = P[i];
    }
    return m;
}
int main() {
    trix[1] = triy[1] = 0;
    double disy = sqrt(3)/2;
    int i, j, idx = 2, x;
    char buf[1024];
    for(i = 2; idx < 32768;i++) {
        trix[idx] = trix[idx-i+1]-0.5;
        triy[idx] = triy[idx-i+1]-disy;
        for(j = 1, idx++; j < i && idx < 32768; j++, idx++) {
            trix[idx] = trix[idx-1]+1;
            triy[idx] = triy[idx-1];
        }
    }
    while(gets(buf)) {
        stringstream sin(buf);
        int n = 0, m;
        while(sin >> x) {
            P[n].x = trix[x];
            P[n].y = triy[x];
            n++;
        }
        sort(P, P+n, cmp);
        m = convex(n);
        printf("%s ", buf);
        if(m-1 != n || n == 1 || m-1 == 5) {
            puts("are not the vertices of an acceptable figure");
            continue;
        }
        double tmp = dist(CH[0], CH[1]);
        for(i = 1; i < m; i++) { // check all sides must be of the same length.
            if(fabs(dist(CH[i], CH[i-1])-tmp) > eps)
                break;
        }
        if(i != m) {
            puts("are not the vertices of an acceptable figure");
            continue;
        }
        for(i = 1; i < m-1; i++) { // check each side must coincide with an edge in the grid.
            tmp = fabs(cross(CH[i], CH[i-1], CH[i+1]));
            if(fabs(asin(tmp/sqrt(dist(CH[i], CH[i-1]))/sqrt(dist(CH[i], CH[i+1])))*180/pi - 60) > eps)
                break;
        }
        if(i != m-1) {
            puts("are not the vertices of an acceptable figure");
            continue;
        }
        printf("are the vertices of ");
        if(n == 3)
            puts("a triangle");
        else if(n == 4)
            puts("a parallelogram");
        else
            puts("a hexagon");
    }
    return 0;
}
