#include <stdio.h>
int A[100005], n, m;
int check(int res) {
    int sum = 0, cnt = 0, i;
    for(i = 0; i <= n; i++) {
        if(A[i] > res)  return 0;
        if(sum+A[i] > res)
            sum = A[i], cnt++;
        else
            sum += A[i];
    }
    if(sum) cnt++;
    return cnt <= m;
}
int main() {
    int i;
    scanf("%*d");
    while(scanf("%d %d", &n, &m) == 2) {
        int idx, w;
        for(i = 0; i < n; i++)
            scanf("%d %d", &idx, &w), A[idx] = w;
        int l = 0, r = 10000, mid;
        while(l <= r) {
            mid = (l+r)/2;
            if(check(mid))
                r = mid-1;
            else
                l = mid+1;
        }
        printf("%d\n", r+1);
    }
    return 0;
}
