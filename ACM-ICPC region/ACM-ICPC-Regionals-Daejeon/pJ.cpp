#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
typedef struct {
    int x, y;
} co;
co R[100000], B[100000];
bool cmp1(co a, co b) {
    return a.x > b.x;
}
bool cmp2(co a, co b) {
    return a.x < b.x;
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        int n, m;
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &B[i].x, &B[i].y);
        }
        scanf("%d", &m);
        for(i = 0; i < m; i++) {
            scanf("%d %d", &R[i].x, &R[i].y);
        }
        sort(B, B+n, cmp1);
        sort(R, R+m, cmp2);
        int ans = abs(B[0].x - R[0].x) + abs(B[0].y - R[0].y);
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(R[j].x - B[i].x >= ans)  break;
                int tmp = abs(B[i].x - R[j].x) + abs(B[i].y - R[j].y);
                if(tmp < ans)   ans = tmp;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
2
10
-16 -4
-1 -3
-9 -1
-4 -10
-11 -6
-20 4
-13 6
-3 -10
-19 -1
-12 -4
10
8 2
10 3
10 10
20 -3
20 3
16 2
3 -5
14 -10
8 -2
14 0
10
-3 39
-2 -28
-1 20
-3 11
-3 45
-2 -44
-1 -47
-5 -35
-5 -19
-5 -45
10
27 5
28 0
28 5
21 5
2 3
13 -1
16 -2
20 -2
33 -3
27 1
*/
