#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int n;
    int v[8] = {200, 100, 50, 20, 10, 5, 2, 1};
    while(scanf("%d", &n) == 1 && n != -1) {
        int a[8], i, j, sum = 0;
        for(i = 0; i < 8; i++)
            scanf("%d", &a[7-i]);
        for(i = 0; i < 8; i++)
            sum += a[i]*v[i];
        if(sum%n) {
            puts("no");
            continue;
        }
        for(i = 0; i < n; i++) {
            int tmp = sum/n;
            for(j = 0; j < 8; j++) {
                int h = tmp/v[j];
                h = min(h, a[j]);
                a[j] -= h;
                tmp -= h*v[j];
            }
            if(tmp) break;
        }
        puts(i == n ? "yes" : "no");
    }
    return 0;
}
/*
2
1 1 1 1 1 1 1 1
2
2 1 2 1 5 2 2 1
1
3423 234 324 972 740 12 234 901
4
147 5502 3486 434 76 66 267 20
5
3015 3590 1559 1219 78 507 23 8
-1
*/
