#include <stdio.h>
long long A[1000000];
long long n, m;
int check(long long val) {
    long long sum, k;
    int p, q, r;
    sum = A[0], k = 0, r = 0;
    for(p = 0, q = -1; p < n; sum += A[++p]) {
        while(sum > val)    sum -= A[++q];
        k += p-q;
        if(k > m)   return 1; // high
        if(sum == val)  r = 1;
    }
    if(k < m)   return -1;  // low
    return !r;
}
int main() {
    int cases, i;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%lld %lld", &n, &m);
        long long mn = 0xffff, mx = 0, mid;
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            mx += A[i], mn = mn < A[i] ? mn : A[i];
        }
        int flag = 0;
        while(mn <= mx) {
            mid = (mn+mx)/2;
            flag = check(mid);
            if(flag > 0)
                mx = mid-1;
            else if(flag < 0)
                mn = mid+1;
            else
                break;
        }
        if(flag < 0)    mid++;
        printf("%lld\n", mid%1000000007);
    }
    return 0;
}
