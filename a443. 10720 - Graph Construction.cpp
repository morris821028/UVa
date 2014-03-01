#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
int n, i, k;
long long sum[1000005], d[1000005];
int main() {
    while(scanf("%d", &n) == 1 && n) {
        sum[0] = 0;
        for(i = 0; i < n; i++)
            scanf("%lld", &d[i]);
        sort(d, d+n, greater<int>());
        for(i = 0; i < n; i++)
            sum[i+1] = sum[i] + d[i];
        long long left = 0, right;
        int ans = 0;
        if(sum[n]&1)    ans = -1;
        else
        for(k = 0; k < n; k++) {
            left += d[k];
            right = (long long)k * (k+1);
            int l = 0, r = n-1, m;
            while(l < r) {
                m = (l+r)>>1;
                if(d[m] <= k+1)
                    r = m;
                else
                    l = m+1;
            }
            if(l < k+1)
                right += sum[n] - sum[k+1];
            else
                right += sum[n] - sum[l] + (long long)(k+1)*(l - k - 1);
            if(left > right) {
                ans = -1;break;
            }
        }
        if(ans)
            puts("Not possible");
        else
            puts("Possible");
    }
    return 0;
}
