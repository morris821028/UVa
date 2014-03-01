#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
using namespace std;
typedef struct {
    int i, j, v;
} E;
E D[1000000];
int R[1005], P[1005];
int cmp(const void *i, const void *j) {
    static E *a, *b;
    a = (E *)i, b = (E *)j;
    return a->v - b->v;
}
void init(int n) {
    int i;
    for(i = 0; i < n; i++)
        R[i] = 1, P[i] = i;
}
int findp(int x) {
    return P[x] == x ? x : P[x]=findp(P[x]);
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x != y) {
        if(R[x] > R[y])
            R[x] += R[y], P[y] = x;
        else
            R[y] += R[x], P[x] = y;
        return 1;
    }
    return 0;
}
int main() {
    int n, m, i, j, cases = 0;
    int x, y, v;
    char s[1000];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        map<string, int> toN;
        for(i = 0; i < n; i++) {
            scanf("%s", s);
            toN[s] = i;
        }
        for(i = 0; i < m; i++) {
            scanf("%s", s), x = toN[s];
            scanf("%s", s), y = toN[s];
            scanf("%d", &v);
            D[i].i = x, D[i].j = y, D[i].v = v;
        }
        scanf("%s", s);
        init(n);
        qsort(D, m, sizeof(E), cmp);
        int ac = 0, ans = 0;
        for(i = 0; i < m; i++) {
            if(joint(D[i].i, D[i].j)) {
                ans += D[i].v;
                ac++;
                if(ac == n-1)   break;
            }
        }
        if(ac == n-1)
            printf("%d\n", ans);
        else
            puts("Impossible");
    }
    return 0;
}
