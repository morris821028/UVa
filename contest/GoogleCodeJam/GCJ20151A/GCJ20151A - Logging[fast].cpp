#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-6
#define MAXN 131072
struct Pt {
    double x, y;
    int label;
    Pt(double a = 0, double b = 0, int c = 0):
    x(a), y(b), label(c) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
    }
};
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
int between(Pt a, Pt b, Pt c) {
    return dot(c - a, b - a) >= -eps && dot(c - b, a - b) >= -eps;
}
int onSeg(Pt a, Pt b, Pt c) {
    return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
Pt D[4096];

bool cmp(const Pt& p1, const Pt& p2)
{
    if (p1.y == 0 && p2.y == 0 && p1.x * p2.x <= 0) return p1.x > p2.x;
    if (p1.y == 0 && p1.x >= 0 && p2.y != 0) return true;
    if (p2.y == 0 && p2.x >= 0 && p1.y != 0) return false;
    if (p1.y * p2.y < 0) return p1.y > p2.y;
    double c = cross2(p1, p2);
    return c > 0 || c == 0 && fabs(p1.x) < fabs(p2.x);
}
int main() {
    int N, testcase, cases = 0;
    double x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%lf %lf", &x, &y);
            D[i] = Pt(x, y);
        }
        printf("Case #%d:\n", ++cases);
        
        if (N == 1) {
            puts("0");
            continue;
        }
        
        for (int i = 0; i < N; i++) {
            vector< Pt > A;
            for (int j = 0; j < N; j++) {
                if (i == j)
                    continue;
                Pt p = D[j] - D[i];
                A.push_back(p);
            }
            sort(A.begin(), A.end(), cmp);
            int M = (int)A.size();
            int l = 0, r = 0, cnt = 1;
            int ret = 0;
            for (l = 0; l < M; l++) {
                if (l == r)
                    r = (r+1)%M, cnt++;
                while (l != r && cross2(A[l], A[r]) >= 0) {
                    r = (r+1)%M, cnt++;
                }
                ret = max(ret, cnt);
                cnt--;
            }
            printf("%d\n", N - ret);
        }
    }
    return 0;
}

/*
1
30
0 0
-971645 838743
748096 -988877
-652232 -993753
737167 -838743
-48 27
706721 -885828
606199 854425
659001 -993753
898961 885828
-659001 885828
748096 -973880
21 -13
-748096 606199
-732894 991850
13 -12
659001 -737167
-32 -32
737167 -748096
650983 -971645
650983 -732894
854425 -606199
-606199 885828
916399 -988877
652232 -838743
-606199 988877
-620105 -652232
-748096 -737167
24 -23
916399 854425

1000
8
-885828 650983
-652232 -853618
-854425 838743
916399 971645
-606199 971645
-854425 652232
748096 -737167
971645 737167

1
3
885828 737167 
898961 748096
-885828 -737167

854425 732894 706721 606199
 10
 8
 6 6
 0 3
 1 7
 4 5
 4 0
 3 9
 7 7
 7 1
*/
