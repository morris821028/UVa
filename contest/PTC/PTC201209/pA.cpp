#include <stdio.h>
using namespace std;
typedef struct {
    long long x, y;
} Pt;
Pt P[1000005], Q[1000005];
int main() {
    int n, i, j, m;
    long long d;
    while(scanf("%d", &n) == 1) {
        int tn = 0;
        for(i = 0; i < n; i++) {
            scanf("%lld %lld", &P[i].x, &P[i].y);
        }
        while(scanf("%d %lld", &m, &d) == 2) {
            if(m == 0 && d == 0)    break;
            for(i = 0; i < m; i++)
                scanf("%lld %lld", &Q[i].x, &Q[i].y);
            int ans = 0;
            for(i = 0; i < n; i++) {
                for(j = 0; j < m; j++) {
                    if((P[i].x-Q[j].x)*(P[i].x-Q[j].x)
                       + (P[i].y-Q[j].y)*(P[i].y-Q[j].y)
                       <= d*d) {
                       ans++;
                    }
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
/*
10
0 0
100 100
200 200
300 300
400 400
500 500
600 600
600 600
700 700
59999 59999
3 150
0 0
150 150
500 650
2 300
100 10000
10000 100
2 600
500 500
500 500
0 0
*/
