#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define eps 1e-10
#define MAXN 131072

pair<int, int> D[MAXN];
int main() {
    int N, x, y;
    while (scanf("%d", &N) == 1) {
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            D[i] = make_pair(x, y);
        }
        
        sort(D, D+N);
        
        double l = 0, r = 1000000, mid, ret = 0;
        for (int it = 0; it < 100; it++) {
            mid = (l + r)/2;
            double left = 0;
            int ok = 1;
            for (int i = 0; i < N && ok; i++) {
                if (D[i].first > left)  left = D[i].first;
                if (left + mid > D[i].second)
                    ok = 0;
                left += mid;
            }
            if (ok)
                l = mid, ret = mid;
            else
                r = mid;
        }
        
        int rp = 0, rq = 1;
        for (int p, q = 1; q <= N; q++) {
            p = round(ret * q);
            if (fabs((double) p/q - ret) < fabs((double) rp/rq - ret)) {
                rp = p, rq = q;
            }
        }
//        printf("%lf\n", ret);
        printf("%d/%d\n", rp, rq);
    }
    return 0;
}
/*

*/