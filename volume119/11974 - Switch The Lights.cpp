#include <stdio.h>
#include <queue>
using namespace std;
int main() {
    int t, cases = 0, n, m, i, j, x;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        int ch[105];
        for(i = 0; i < m; i++) {
            ch[i] = 0;
            for(j = 0; j < n; j++) {
                scanf("%d", &x);
                ch[i] |= x<<j;
            }
        }
        queue<int> Q;
        int step[65536] = {}, tn, tm;
        Q.push((1<<n)-1);
        step[(1<<n)-1] = 1;
        while(!Q.empty() && step[0] == 0) {
            tn = Q.front(), Q.pop();
            for(i = 0; i < m; i++) {
                tm = tn^ch[i];
                if(step[tm] == 0) {
                    step[tm] = step[tn]+1;
                    Q.push(tm);
                }
            }
        }
        printf("Case %d: ", ++cases);
        if(step[0] == 0)
            puts("IMPOSSIBLE");
        else
            printf("%d\n", step[0]-1);
    }
    return 0;
}
