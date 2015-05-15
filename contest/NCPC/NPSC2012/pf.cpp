#include <stdio.h>

int main() {
    int t, n, c;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &c);
        int ans;
        if(n&1)
            ans = (1<<(n-1))*(n+1);
        else
            ans = (1<<n)*n/2;
        printf("%d\n", ans*c);
    }
    return 0;
}
