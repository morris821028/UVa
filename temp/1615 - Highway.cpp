#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define eps 1e-6
bool cmp(pair<double, double> a, pair<double, double> b) {
    if (fabs(a.second - b.second) > eps)
        return a.second < b.second;
    return a.first < b.first;
}
int main() {
    int D, L, N, x, y;
    while (scanf("%d %d", &L, &D) == 2) {
        scanf("%d", &N);
        
        vector< pair<double, double> > A;
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            double d = sqrt(D*D-y*y);
            A.push_back(make_pair(max(x-d, 0.0), min(x+d, (double)L)));
        }
        sort(A.begin(), A.end(), cmp);
        
        int ret = 0;
        double v = -1;
        for (int i = 0; i < N; i++) {
            if (v < A[i].first) {
                v = A[i].second;
                ret++;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*

*/