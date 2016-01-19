#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

const int MAXN = 131072;
const int LMAX = 0x3f3f3f3f;

long long C[MAXN];
double f(double l, double r) {
//    printf("[%lf, %lf]\n", l, r);
    return (r - l) * (r + l) / 2;
}
int main() {
    int testcase;
    int cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        int N;
        double A, B;
        scanf("%d %lf %lf", &N, &A, &B);
        for (int i = 0; i < N; i++) {
            scanf("%lld", &C[i]);
        }
        
        double ret = 0;
        double sum = 0, pre = 0;
        for (int i = 0; i < N; i++)
            sum += C[i];
        for (int i = 0; i < N; i++) {
            double pp = ceil(A / sum);
            double qq = floor(B / sum);
            int st = pp, ed = qq;
            set<int> S;
            for (int j = max(0, st-3); j <= st+3; j++) {
                if (S.count(j))
                    continue;
                double l = j * sum + pre, r = j * sum + pre + C[i];
                if (max(l, A) <= min(r, B)) {
                    ret += f(max(l, A) - (j * sum + pre), min(r, B) - (j * sum + pre));
                }
                S.insert(j);
            }
            for (int j = max(0, ed-3); j <= ed+3; j++) {
                if (S.count(j))
                    continue;
                double l = j * sum + pre, r = j * sum + pre + C[i];
                if (max(l, A) <= min(r, B)) {
                    ret += f(max(l, A) - (j * sum + pre), min(r, B) - (j * sum + pre));
                }
                S.insert(j);
            }
            
            ret += f(0, C[i]) * max((ed-3) - (st+3)-1, 0);
            pre += C[i];
        }
        
        ret /= (B - A);
        printf("Case #%d: %.9lf\n", ++cases, ret);
    }
    return 0;
}
/*
 5
 2 100 200
 100 100
 2 100 200
 50 100
*/