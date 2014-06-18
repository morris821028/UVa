#include <stdio.h>
#include <algorithm>
using namespace std;
struct E {
    int x, y, v;
};
bool cmp(E a, E b) {
    return a.v < b.v;
}
int P[105], R[105];
void init(int n) {
    for(int i = 0; i <= n; i++)
        P[i] = i, R[i] = 1;
}
int findP(int x) {
    return P[x] == x ? x : P[x] = findP(P[x]);
}
int joint(int x, int y) {
    x = findP(x);
    y = findP(y);
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
    E e[105];
    int n, m, K, t, A[105];
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &K);
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &e[i].x, &e[i].y, &e[i].v);
            e[i].x--;
            e[i].y--;
        }
        sort(e, e+m, cmp);
        int res = A[0];
        for(i = (1<<n)-1; i >= 0; i -= 2) {
            int people = 0, tn = 0;
            for(j = 0; j < n; j++)
                if((i>>j)&1)
                    people += A[j], tn++;
            if(people <= res)
                continue;
            int cost = 0, edge = 0;
            init(n);
            for(j = 0; j < m; j++) {
                if(((i>>e[j].x)&1) && ((i>>e[j].y)&1) && joint(e[j].x, e[j].y)) {
                    edge++;
                    cost += e[j].v;
                }
            }
            if(edge == tn-1 && cost <= K) {
                res = people;
            }

        }
        printf("%d\n", res);
    }
    return 0;
}
