#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
int n, i, k;
long long sum[1005], d[1005];
int main() {
    while(scanf("%d", &n) == 1 && n) {
        sum[0] = 0;
        for(i = 0; i < n; i++)
            scanf("%lld", &d[i]);
        sort(d, d+n, greater<int>());
        for(i = 0; i < n; i++)
            sum[i+1] = sum[i] + d[i];
        long long left = 0, right;
        int ret = 1;
        if(sum[n]&1)    ret = 0;
        for(k = 0; k < n; k++) {
            left += d[k];
            right = (long long)k * (k+1);
            int l =  lower_bound(d , d + n, k+1, greater<int>()) - d;
            if(l < k+1)
                right += sum[n] - sum[k+1];
            else
                right += sum[n] - sum[l] + (long long)(k+1)*(l - k - 1);
            if(left > right)	ret = 0;
        }
        printf("%d\n", ret);
    }
    return 0;
}
