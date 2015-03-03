#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <map>
#include <set>
#include <algorithm>
#include <ctype.h>
using namespace std;
#define eps 1e-6
struct MAP {
    string name;
    double x1, y1, x2, y2;
    int level;
    MAP(double xl = 0, double yl = 0,
        double xr = 0, double yr = 0, string s = ""):
    x1(xl), y1(yl), x2(xr), y2(yr), name(s) {
        if (x1 > x2)    swap(x1, x2);
        if (y1 > y2)    swap(y1, y2);
        level = -1;
    }
    double getArea() {
        return (x2 - x1) * (y2 - y1);
    }
    int contain(double x, double y) {
        return x1 - eps <= x && x <= x2 + eps
            && y1 - eps <= y && y <= y2 + eps;
    }
    pair<double, double> getCenter() {
        return make_pair((x1 + x2)/2.0, (y1 + y2)/2.0);
    }
    double getRatio() {
        return fabs((y2 - y1)/(x2 - x1) - 0.75);
    }
} D[2048];
map<string, pair<double, double> > R;
pair<double, double> QPOS;
double dist(pair<double, double> a, pair<double, double> b) {
    return hypot(a.first - b.first, a.second - b.second);
}
bool cmp(MAP a, MAP b) {
    if (a.level != b.level)     return a.level > b.level;
    double da = dist(QPOS, a.getCenter()), db = dist(QPOS, b.getCenter());
    if (fabs(da - db) > eps)    return da < db;
    da = a.getRatio(), db = b.getRatio();
    if (fabs(da - db) > eps)    return da < db;
    da = dist(QPOS, make_pair(a.x2, a.y1));
    db = dist(QPOS, make_pair(b.x2, b.y1));
    if (fabs(da - db) > eps)    return da > db;
    return a.x1 < b.x1;
}
int main() {
    char s[2048];
    double x1, x2, y1, y2;
    while (scanf("%*s") == 0) { // MAPS
        int N = 0;
        while (scanf("%s", s) == 1) {
            if (!strcmp(s, "LOCATIONS"))
                break;
            scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            D[N] = MAP(x1, y1, x2, y2, s), N++;
        }
        while (scanf("%s", s) == 1) {
            if (!strcmp(s, "REQUESTS"))
                break;
            scanf("%lf %lf", &x1, &y1);
            R[s] = make_pair(x1, y1);
        }
        
        while (scanf("%s", s) == 1) {
            if (!strcmp(s, "END"))
                break;
            int dlevel;
            scanf("%d", &dlevel);
            if (R.count(s) == 0) {
                printf("%s at detail level %d unknown location\n", s, dlevel);
            } else {
                printf("%s at detail level %d ", s, dlevel);
                
                vector<double> DAREA;
                vector<MAP> C;
                x1 = R[s].first, y1 = R[s].second;
                
                for (int i = 0; i < N; i++) {
                    if (D[i].contain(x1, y1)) {
                        C.push_back(D[i]);
                        DAREA.push_back(D[i].getArea());
                    }
                }
                sort(DAREA.begin(), DAREA.end());
                int K = 1;
                for (int i = 1; i < C.size(); i++) {
                    if (fabs(DAREA[i] - DAREA[K - 1]) > eps)
                        DAREA[K++] = DAREA[i];
                }
                for (int i = 0; i < C.size(); i++) {
                    for (int j = 0; j < K; j++) {
                        if (fabs(DAREA[j] - C[i].getArea()) < eps)
                            C[i].level = K - j;
                    }
                }
                
                QPOS = make_pair(x1, y1);
                sort(C.begin(), C.end(), cmp);
                int f = 0;
                for (int i = 0; i < C.size(); i++) {
                    if (C[i].level == dlevel) {
                        f = 1;
                        printf("using %s\n", C[i].name.c_str());
                        break;
                    }
                }
                if (f == 0) {
                    if (C.size() == 0) {
                        printf("no map contains that location\n");
                    } else {
                        printf("no map at that detail level; using %s\n", C[0].name.c_str());
                    }
                }
            }
        }
    }
    return 0;
}
/*
 MAPS
 BayArea -6.0 12.0 -11.0 5.0
 SantaClara 4.0 9.0 -3.5 2.5
 SanJoseRegion -3.0 10.0 11.0 3.0
 CenterCoast -5.0 11.0 1.0 -8.0
 SanMateo -5.5 4.0 -12.5 9.0
 NCalif -13.0 -7.0 13.0 15.0
 LOCATIONS
 Monterey -4.0 2.0
 SanJose -1.0 7.5
 Fresno 7.0 0.1
 SanFrancisco -10.0 8.6
 SantaCruz -4.0 2.0
 SanDiego 13.8 -19.3
 REQUESTS
 SanJose 3
 SanFrancisco 2
 Fresno 2
 Stockton 1
 SanDiego 2
 SanJose 4
 SantaCruz 3
 END
 */