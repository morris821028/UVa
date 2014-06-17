#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int w[10005], a[10005], len;
int n, cnt[20005], h[20005];
void init() {
    int i;
    for(i = n+n-1; i > 0; i--)
        h[i] = 0;
    for(i = n-1; i > 0; i--)
        h[i] = h[i+i]+1;
}
void dfs(int idx, int mx) {
    if(idx+h[w[idx-1]] >= len)
        return;
    int i, j;
    if(w[idx-1] == n) {
        len = idx;
        for(i = 0; i < len; i++)
            a[i] = w[i];
        return ;
    }
    for(i = min(n, mx); i > w[idx-1]; i--) {
        if(!cnt[i]) continue;
        w[idx] = i;
        for(j = 0; j <= idx; j++)
            cnt[w[j]+i]++;
        dfs(idx+1, 2*i);
        for(j = 0; j <= idx; j++)
            cnt[w[j]+i]--;
    }
}
int main() {
    int i;
    while(scanf("%d", &n) == 1 && n) {
        memset(cnt, 0, sizeof(cnt));
        len = n+1;
        init();
        w[0] = a[0] = 1;
        cnt[1]++, cnt[2]++;
        dfs(1, 2);
        printf("%d", a[0]);
        for(i = 1; i < len; i++)
            printf(" %d", a[i]);
        puts("");
    }
    return 0;
}
