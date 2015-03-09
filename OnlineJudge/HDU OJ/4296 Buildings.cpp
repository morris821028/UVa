#include <stdio.h>
#include <algorithm>
using namespace std;
struct ele {
    long long w, s;
};
bool cmp(ele a, ele b) {
    return a.w+a.s < b.w+b.s;
}
int main() {
    int n, i;
    ele A[100000];
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%I64d %I64d", &A[i].w, &A[i].s);
        sort(A, A+n, cmp);
        long long sum = 0, ans = 0;
        for(i = 0; i < n; i++) {
            sum += A[i].w;
            ans = max(ans, sum-A[i].s-A[i].w);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
