#include <stdio.h>
#include <stdlib.h>
struct edge {
    int x, y, v;
};
edge D[130000], E[130000];
int p[501], r[501];
void init(int n) {
    int i;
    for(i = 0; i <= n; i++)
        p[i] = i, r[i] = 1;
}
int find(int x) {
    return p[x] == x ? x : (p[x]=find(p[x]));
}
int joint(int x, int y) {
    x = find(x), y = find(y);
    if(x != y) {
        if(r[x] > r[y])
            r[x] += r[y], p[y] = x;
        else
            r[y] += r[x], p[x] = y;
        return 1;
    }
    return 0;
}
int sort(int n) {
    int w[40] = {}, i;
    for(i = 0; i < n; i++)
        w[D[i].v]++;
    for(i = 1; i < 40; i++)
        w[i] += w[i-1];
    for(i = 0; i < n; i++)
        E[--w[D[i].v]] = D[i];

}
int main() {
    int t, n, tmp;
    char s[501][5] = {"0000"};
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int i, j, k, sum, m = 0;
        for(i = 1; i <= n; i++) {
            scanf("%s", s[i]);
            for(j = 1; j < i; j++) {
                sum = 0;
                for(k = 0; k < 4; k++) {
                    tmp = abs(s[i][k]-s[j][k]);
                    if(tmp > 5) tmp = 10-tmp;
                    sum += tmp;
                }
                D[m].x = i, D[m].y = j, D[m].v = sum;
                m++;
            }
        }
        sort(m);
        init(n);
        int ans = 0, cnt = 0;
        for(i = 0; i < m; i++) {
            if(joint(E[i].x, E[i].y)) {
                ans += E[i].v;
                cnt++;
                if(cnt == n)
                    break;
            }
        }
        int link = 40;
        for(i = 1; i <= n; i++) {
            sum = 0;
            for(k = 0; k < 4; k++) {
                tmp = abs(s[0][k]-s[i][k]);
                if(tmp > 5) tmp = 10-tmp;
                sum += tmp;
            }
            if(sum < link)
                link = sum;
        }
        printf("%d\n", ans+link);
    }
    return 0;
}
