#include <stdio.h>
#include <string.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
long long hp[2][20][20];
void dfs(int idx, long long num) {
    int i;
    for(i = 1; i <= 17; i++) {
        if(num%(1<<i) == 0) {
            hp[0][idx][i] = min(hp[0][idx][i], num);
            hp[1][idx][i] = max(hp[1][idx][i], num);
        } else {
            break;
        }
    }
    if(idx == 17)
        return;
    dfs(idx+1, num*10 + 1);
    dfs(idx+1, num*10 + 2);
}
int main() {
    memset(hp[0], 127, sizeof(hp[0]));
    memset(hp[1], 0, sizeof(hp[1]));
    dfs(0, 0);
    int t, p, q, c = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &p, &q);
        printf("Case %d: ", ++c);
        if(hp[0][p][q] == hp[1][p][q])
            printf("%lld\n", hp[0][p][q]);
        else if(hp[1][p][q] == 0)
            puts("impossible");
        else
            printf("%lld %lld\n", hp[0][p][q], hp[1][p][q]);
    }
    return 0;
}
