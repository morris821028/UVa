#include <stdio.h>
#include <algorithm>
using namespace std;
struct pt {
    int x, y;
};
bool cmp(pt a, pt b) {
    return a.y > b.y;
}
int main() {
    int n, cases = 0, i;
    pt A[1000];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d %d", &A[i].x, &A[i].y);
        sort(A, A+n, cmp);
        int sum = 0, ans = 0;
        for(i = 0; i < n; i++) {
            sum += A[i].x;
            ans = max(ans, sum+A[i].y);
        }
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
