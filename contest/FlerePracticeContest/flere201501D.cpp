#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define MAXN 1024
int A[MAXN], B[MAXN];
int LIS(int A[], int n) {
    vector<int> r;
    r.push_back(A[0]);
    for (int i = 1; i < n; i++) {
        int pos = (int)(upper_bound(r.begin(), r.end(), A[i]) - r.begin());
        if (pos == r.size())
            r.push_back(A[i]);
        else
            r[pos] = A[i];
    }
    return (int) r.size();
}
int main() {
    int testcase, N, K;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &N, &K);
        for (int i = 0; i < N; i++)
            scanf("%d", &A[i]);
        for (int i = 0; i < N; i++)
            scanf("%d", &B[i]);
        
        vector< pair<int, int> > D;
        for (int i = 0; i < N; i++)
            D.push_back(make_pair(A[i], B[i]));
        
        sort(D.begin(), D.end());
        for (int i = 0; i < N; i++)
            B[i] = D[i].second;
        
        int L = LIS(B, N);
        puts(L >= N - K ? "yes" : "no");
    }
    return 0;
}
/*
 2
 4 2 
 9 3 7 1 
 1 4 8 2
 2 0
 1 3
 3 1
*/