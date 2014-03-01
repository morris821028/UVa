#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int n, d, r;
    while(scanf("%d %d %d", &n, &d, &r) == 3) {
        if(n == 0)
            break;
        int a[101], b[101], i;
        for(i = 0; i < n; i++)
            scanf("%d", a+i);
        for(i = 0; i < n; i++)
            scanf("%d", b+i);
        sort(a, a+n);
        sort(b, b+n);
        int sum = 0;
        for(i = 0; i < n; i++) {
            if(a[i]+b[n-i-1] > d) {
                sum += (a[i]+b[n-i-1]-d)*r;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}
