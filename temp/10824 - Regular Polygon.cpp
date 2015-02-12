#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
#define eps 1e-6
const double pi = acos(-1);
struct cmp {
    bool operator() (const double a, const double b) const {
        return a + eps < b;
    }
};
int main() {
    int n, cases = 0;
    double x, y;
    double A[2048];
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &x, &y);
            A[i] = atan2(y, x);
        }
        
        sort(A, A+n);
        printf("Case %d:\n", ++cases);
        
        for (int i = 3; i <= n; i++) {
            int cnt = 0, used[2048] = {};
            double theta = 2 * pi / i;
            for (int j = 0; j < n; j++) {
                if (used[j])    continue;
                int ok = 1;
                double base = A[j];
                for (int k = 0; k < i; k++) {
                    int pos = (int) (lower_bound(A, A+n, base, cmp()) - A);
                    if (pos != n && fabs(A[pos] - base) < eps) {
                        used[pos] = 1;
                    } else {
                        ok = 0;
                        break;
                    }
                    base += theta;
                }
                if (ok)
                    cnt++;
            }
            if (cnt)
                printf("%d %d\n", i, cnt);
        }
    }
    return 0;
}