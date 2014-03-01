#include <stdio.h>

int main() {
    int n, a[10005], b[10005], g[10005], k[10005];
    int x, y, i;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%d %d %d %d", a+i, b+i, g+i, k+i);
    scanf("%d %d", &x, &y);
    for(i = n-1; i >= 0; i--) {
        if(a[i] <= x && b[i] <= y && x <= a[i]+g[i] && y <= b[i]+k[i]) {
            printf("%d\n", i+1);
            break;
        }
    }
    if(i < 0)   puts("-1");
    return 0;
}
