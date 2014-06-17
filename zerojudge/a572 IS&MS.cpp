#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
int lowbit[10005];
long long C[10005];
void modify(int idx, int L, long long v) {
    while(idx <= L) {
        C[idx] = max(C[idx], v);
        idx += lowbit[idx];
    }
}
long long query(int idx) {
    static long long ans;
    ans = 0;
    while(idx) {
        ans = max(ans, C[idx]);
        idx -= lowbit[idx];
    }
    return ans;
}
int main() {
    int n, i, A[10005];
    for(i = 0; i < 10005; i++)
        lowbit[i] = i&(-i);
    while(scanf("%d", &n) == 1) {
        map<int, int> r;
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            r[A[i]] = 1;
        }
        int idx = 1, tn, tag;
        for(map<int, int>::iterator it = r.begin();
            it != r.end(); it++) {
            C[idx] = 0;
            it->second = idx++;
        }
        tn = idx;
        long long pred, ans = 0;
        for(i = 0; i < n; i++) {
            tag = r[A[i]];
            pred = query(tag-1);
            modify(tag, tn, pred+A[i]);
            if(pred+A[i] > ans)
                ans = pred+A[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
