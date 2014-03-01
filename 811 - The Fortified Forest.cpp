#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Pt {
    double x, y;
    bool operator<(const Pt &a) const {
        if(x != a.x)
            return x < a.x;
        return y < a.y;
    }
};
#define eps 1e-8
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double dist(Pt a, Pt b) {
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}
double calcConvexBounds(Pt p[], int n) {
    if(n == 1)  return 0;
    sort(p, p+n);
    Pt ch[20];
    int i, m = 0, t;
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
    m--;
    if(m == 2)
        return 2*dist(ch[0], ch[1]);
    double bounds = 0;
    for(i = 0, t = m-1; i < m; t = i++)
        bounds += dist(ch[i], ch[t]);
    return bounds;
}
int main() {
    int n, m;
    int i, j, k;
    int cases = 0;
    double x[20], y[20], v[20], l[20];
    Pt tree[20];
    while(scanf("%d", &n) == 1 && n) {
        if(cases)   puts("");
        for(i = 0; i < n; i++)
            scanf("%lf %lf %lf %lf", &x[i], &y[i], &v[i], &l[i]);
        double mncost = 0xffffff, extrawood;
        int mnstate, mncut;
        for(i = (1<<n)-1; i > 0; i--) { // cut state
            double bounds = 0, cost = 0;
            int cut = 0;
            m = 0;
            for(j = 0; j < n; j++) {
                if((i>>j)&1) {
                    bounds += l[j];
                    cost += v[j];
                    cut++;
                } else {
                    tree[m].x = x[j];
                    tree[m].y = y[j];
                    m++;
                }
            }
            if(cost > mncost)   continue;
            double needBound = calcConvexBounds(tree, m);
            //printf("%d %lf %lf %lf %lf\n", i, cost, bounds-needBound, bounds, needBound);
            if(needBound <= bounds+eps) {
                if(mncost > cost || (fabs(mncost-cost) < eps && mncut > cut)) {
                    mncost = cost;
                    mncut = cut;
                    mnstate = i;
                    extrawood = bounds - needBound;
                }
            }
        }
        printf("Forest %d\n", ++cases);
        printf("Cut these trees:");
        for(i = 0; i < n; i++)
            if((mnstate>>i)&1)  printf(" %d", i+1);
        puts("");
        printf("Extra wood: %.2lf\n", extrawood);
    }
    return 0;
}
