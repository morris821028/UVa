#include <stdio.h>
#include <queue>
using namespace std;
int main() {
    int t, cases = 0, n, m;
    char bin[20];
    scanf("%d", &t);
    while(t--) {
        printf("Case %d:\n", ++cases);
        scanf("%d %d", &n, &m);
        int mark[40] = {}, x, y;
        int i, j;
        for(i = 0; i < m; i++) {
            scanf("%d", &x);
            while(x--) {
                scanf("%d", &y);
                mark[i] |= 1<<y;
            }
        }
        int ans[32768] = {};
        ans[0] = 1;
        queue<int> Q;
        Q.push(0);
        while(!Q.empty()) {
            x = Q.front();
            Q.pop();
            for(i = 0; i < m; i++) {
                if(!ans[x^mark[i]]) {
                    ans[x^mark[i]] = ans[x]+1;
                    Q.push(x^mark[i]);
                }
            }
        }
        scanf("%d", &m);
        while(m--) {
            scanf("%s", bin);
            for(i = 0, x = 0; bin[i]; i++)
                x |= (1&(bin[i]-'0'))<<(n-i-1);
            if(ans[x] == 0)
                puts("-1");
            else
                printf("%d\n", ans[x]-1);
        }
        puts("");
    }
    return 0;
}
