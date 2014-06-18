#include <stdio.h>

int main() {
    int t, n, test = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int a[100001] = {}, i;
        for(i = 1; i <= n; i++)
            scanf("%d", a+i);
        int k = 0, ans;
        for(i = 1; i <= n; i++) {
            if(a[i]-a[i-1] > k)
                k = a[i]-a[i-1];
        }
        ans = k;
        for(i = 1; i <= n; i++) {
            if(a[i]-a[i-1] == k)
                k--;
            else if(a[i]-a[i-1] > k) {
                ans++;
                break;
            }
        }
        printf("Case %d: %d\n", ++test, ans);
    }
    return 0;
}
