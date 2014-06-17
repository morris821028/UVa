#include <stdio.h>
#include <set>
using namespace std;
int p[128];
int findp(int x) {
    return x == p[x] ? x : p[x]=findp(p[x]);
}
int main() {
    int v, e, i, x, y;
    char a[5], b[5];
    while(scanf("%d %d", &v, &e) == 2) {
        int used[128] = {}, size = 0;
        for(i = 0; i < 128; i++)
            p[i] = i;
        for(i = 0; i < e; i++) {
            scanf("%s %s", a, b);
            if(used[a[0]] == 0)
                used[a[0]] = ++size;
            if(used[b[0]] == 0)
                used[b[0]] = ++size;
            x = findp(used[a[0]]), y = findp(used[b[0]]);
            if(x != y) {
                p[x] = y;
            }
        }
        set<int> S;
        for(i = 1; i <= v; i++)
            S.insert(findp(i));
        int K = S.size();
        printf("%d\n", 1 + K - v + e);
    }
    return 0;
}
/*
Another formula induced from Euler¡¦s
V + F - E = 1 + K
K components
*/
