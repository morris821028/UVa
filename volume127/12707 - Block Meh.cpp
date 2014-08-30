#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second != b.second)
        return a.second < b.second;
    return a.first < b.first;
}
#define INF 0x3f3f3f3f
int main() {
    int testcase, cases = 0;
    int n, s, e;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        vector< pair<int, int> > D;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &s, &e);
            D.push_back(make_pair(s, e));
        }
        sort(D.begin(), D.end(), cmp);
        vector<int> leftside;
        for (int i = 0; i < D.size(); i++) {
            int pos = (int)(lower_bound(leftside.begin(), leftside.end(), D[i].first + 1)
                            - leftside.begin());
            if (pos == leftside.size()) {
                leftside.push_back(D[i].first);
            } else {
                leftside[pos] = D[i].first;
            }
        }
        printf("Case %d: %d\n", ++cases, (int)leftside.size());
    }
    return 0;
}

/*
 2
 4
 1 5
 2 5
 3 5
 3 4
 4
 1 5
 2 4
 3 5
 3 3
 */