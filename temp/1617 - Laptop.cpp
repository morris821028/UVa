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
    if (a.second != b.second)
        return a.second < b.second;
    return a.first < b.first;
}
int main() {
    int testcase, N, x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        
        vector< pair<int, int> > A;
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            A.push_back(make_pair(x, y));
        }
        sort(A.begin(), A.end(), cmp);
        
        int ret = 1, right = A[0].second;
        for (int i = 1; i < N; i++) {
            if (right != A[i].second) {
                if (right < A[i].first) {
                    ret++, right = A[i].second;
                } else {
                    right++; // greedy place 
                }
            }
        }
        printf("%d\n", ret - 1);
    }
    return 0;
}
/*
 
 */