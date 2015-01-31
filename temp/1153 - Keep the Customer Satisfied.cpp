#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define eps 1e-6
#define MAXN 1048576
// similar  UVa 10154 - Weights and Measures
pair<int, int> D[MAXN];

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second != b.second)
        return a.second < b.second;
    return a.first < b.first;
}
int main() {
    int testcase, N, x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            D[i] = make_pair(x, y);
        }
        sort(D, D+N, cmp);
        
        priority_queue<int> pQ; // max-heap
        int t = 0;
        for (int i = 0; i < N; i++) {
            pQ.push(D[i].first);
            t += D[i].first;
            if (t > D[i].second)
                t -= pQ.top(), pQ.pop();
        }
        printf("%d\n", (int) pQ.size());
        if (testcase)
            puts("");
    }
    return 0;
}
/*
 
 */