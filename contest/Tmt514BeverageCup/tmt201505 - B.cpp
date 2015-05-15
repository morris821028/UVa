#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 131072;
int A[MAXN], Qt[MAXN], out[MAXN];
int main() {
    int testcase;
    int N, K, Q;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &N, &K);
        for (int i = 0; i < N; i++)
            scanf("%d", &A[i]);
        scanf("%d", &Q);
        for (int i = 0; i < Q; i++)
            scanf("%d", &Qt[i]);
        
        vector< pair<int, int> > QV;
        for (int i = 0; i < Q; i++)
            QV.push_back(make_pair(Qt[i], i));
        
        sort(QV.begin(), QV.end());
        sort(A, A+N);
        
        int idx = -1, sum = 0, t, mx = -0x3f3f3f3f;
        for (int i = 0; i < Q; i++) {
            t = QV[i].first;
            while (idx+1 < N && mx + K <= t && A[idx+1] <= t) {
                idx++, sum++;
                mx = max(mx+K, A[idx]);
            }
            out[QV[i].second] = sum;
        }
        
        for (int i = 0; i < Q; i++)
            printf("%d\n", out[i]);
    }
    return 0;
}

/*
 1
 5 2
 7 3 6 8 5
 2
 9
 1
*/