#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

int main() {
    int N;
    double bx, by, cx, cy, cr;
    while (scanf("%d", &N) == 1 && N) {
        scanf("%lf %lf", &bx, &by);
        vector< pair<double, double> > interval;
        for (int i = 0; i < N; i++) {
            scanf("%lf %lf %lf", &cx, &cy, &cr);
            double a, b, c;
            a = (cx - bx) * (cx - bx) - cr * cr;
            b = 2 * (cx - bx) * (by - cy);
            c = (by - cy) * (by - cy) - cr * cr;
            if (b * b - 4 * a * c > 0) {
#define eps 1e-6
                if (fabs(a) > eps) {
                    double m1 = (-b + sqrt(b * b - 4 * a * c))/(2 * a);
                    double m2 = (-b - sqrt(b * b - 4 * a * c))/(2 * a);
                    double l, r;
                    c = by - m1 * bx;
                    l = -c / m1;
                    c = by - m2 * bx;
                    r = -c / m2;
                    if (l >= r)
                        swap(l, r);
                    interval.push_back(make_pair(l, r));
                } else {
                    double m1 = -c / b;
                    double l, r;
                    c = by - m1 * bx;
                    l = -c / m1;
                    r = bx;
                    if (l >= r)
                        swap(l, r);
                    interval.push_back(make_pair(l, r));
                }
            }
        }
        sort(interval.begin(), interval.end());
        double coverL, coverR;
        coverL = interval[0].first;
        coverR = interval[0].second;
        for (int i = 0; i < interval.size(); i++) {
            if (interval[i].first <= coverR) {
                coverR = max(coverR, interval[i].second);
            } else {
                printf("%.2lf %.2lf\n", coverL, coverR);
                coverL = interval[i].first;
                coverR = interval[i].second;
            }
        }
        printf("%.2lf %.2lf\n", coverL, coverR);
        puts("");
    }
    return 0;
}
/*
 ## Input ##
 6
 300 450
 70 50 30
 120 20 20
 270 40 10
 250 85 20
 220 30 30
 380 100 100
 1
 300 300
 300 150 90
 1
 300 300
 390 150 90
 0
 
 ## Output ##
 0.72 78.86
 88.50 133.94
 181.04 549.93
 
 75.00 525.00
 
 300.00 862.50
 */