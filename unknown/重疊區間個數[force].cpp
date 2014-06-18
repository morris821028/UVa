#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);
    int n, i, j, cases = 0;
    int l[50000], r[50000];
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d %d", &l[i], &r[i]);
        int cnt = 0;
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                int ll = max(l[i], l[j]);
                int rr = min(r[i], r[j]);
                if(ll < rr)
                    cnt++;
            }
        }
        printf("Case %d: %d\n", ++cases, cnt);
    }
    return 0;
}
/*
2
0 10
10 20
2
0 10
5 8
2
0 10
5 20
2
0 10
-5 5
2
0 10
0 10
2
0 10
5 10
*/
