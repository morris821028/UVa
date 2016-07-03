#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 2000005;
const int MAXLOGN = 26;
int dp[MAXLOGN][MAXN]; // using 2^i intervals(exclude itself) from j-interval
void solve(int n, vector< pair<int, int> > &A) {
    vector< pair<int, int> > sweep;
    
    sort(A.begin(), A.end());
    for (int i = 0; i < A.size(); i++) {    // make interval (a, b]
        A[i].first--;
        sweep.push_back(make_pair(A[i].first, -(i+1))); // enter point
        sweep.push_back(make_pair(A[i].second, (i+1))); // exit point
    }
    sort(sweep.begin(), sweep.end());       // enter < exit
    
    int cover_id = -1;
    for (int i = 0; i < sweep.size(); i++) {
        int id = sweep[i].second;
        if (id < 0) {
            id = -id - 1;
            if (cover_id == -1 || A[cover_id].second < A[id].second)
                cover_id = id;
        } else {
            id = id - 1;
            if (cover_id >= 0 && A[cover_id].second == A[id].second)
                cover_id = -1;
            dp[0][id] = cover_id;
        }
    }
    
    for (int i = 1; i < MAXLOGN; i++) {
        for (int j = 0; j < A.size(); j++) {
            if (dp[i-1][j] == -1)
                dp[i][j] = -1;
            else
                dp[i][j] = dp[i-1][dp[i-1][j]];
        }
    }
    
    int ret = 0x3f3f3f3f;
    for (int i = 0; i < A.size(); i++) {
        int cnt = 0, pos = i, r = A[i].first + n;
        for (int j = MAXLOGN-1; j >= 0; j--) {
            if (dp[j][pos] == -1 || A[pos].second >= r)
                continue;
            if (A[dp[j][pos]].first < r)
                pos = dp[j][pos], cnt |= 1<<j;
        }
        if (pos != -1 && A[pos].second >= r)
            ret = min(ret, cnt+1);
    }
    
    if (ret == 0x3f3f3f3f)
        puts("impossible");
    else
        printf("%d\n", ret);
}
int main() {
    int n, m, a, b;
    while (scanf("%d %d", &n, &m) == 2) {
        vector< pair<int, int> > A;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            if (b < a)  b += n;
            A.push_back(make_pair(a, b));
            A.push_back(make_pair(a+n, b+n));
        }
        
        solve(n, A);
    }
    return 0;
}
/*
 100 7
 1 50
 50 70
 70 90
 90 40
 20 60
 60 80
 80 20
 8 2
 8 3
 5 7
 8 2
 8 4
 5 7
*/