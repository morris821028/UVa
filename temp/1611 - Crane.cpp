#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 131072

int A[MAXN], R[MAXN], N;
vector< pair<int, int> > ret;
void swapInterval(int l, int r) {
    assert(0 <= l && l < N && 0 <= r && r < N);
    assert((r-l+1)%2 == 0);
    ret.push_back(make_pair(l, r));
    int mid = (l + r)/2;
    for (int i = l, j = mid+1; i <= mid; i++, j++) {
        swap(R[A[i]], R[A[j]]);
        swap(A[i], A[j]);
    }
//    printf("[%d %d]\n", l, r);
//    for (int i = 0; i < N; i++)
//        printf("%d ", A[i]);
//    puts("");
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
            A[i]--;
            R[A[i]] = i;
        }
        
        ret.clear();
        for (int i = 0; i < N; i++) {
            if (R[i] == i)
                continue;
            int div = (N + i)/2;
            if (R[i] > div) { // need swap into [i, (N+i)/2]
                swapInterval(div - (R[i]-div-1), R[i]);
            }
            swapInterval(i, R[i] + (R[i]-i-1));
        }
        printf("%d\n", (int) ret.size());
        for (int i = 0; i < ret.size(); i++) {
            printf("%d %d\n", ret[i].first+1, ret[i].second+1);
        }
    }
    return 0;
}
/*

*/