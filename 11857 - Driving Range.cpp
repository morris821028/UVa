#include <stdio.h>
struct edge {
    int x, y, v;
};
edge D[1000000], E[1000000];
void RadixSort(edge *A, edge *B, int n) {
    int a, x, d, C[65536];
    edge *T;
    for(x = 0; x < 2; x++) {
        d = x*16;
        for(a = 0; a < 65536; a++)     C[a] = 0;
        for(a = 0; a < n; a++)      C[(A[a].v>>d)&65535]++;
        for(a = 1; a < 65536 ; a++)    C[a] += C[a-1];
        for(a = n-1; a >= 0; a--)   B[--C[(A[a].v>>d)&65535]] = A[a];
        T = A, A = B, B = T;
    }
}
int p[1000001], r[1000001];
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
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, m, i;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        for(i = 0; i < m; i++) {
            ReadInt(&D[i].x);
            ReadInt(&D[i].y);
            ReadInt(&D[i].v);
        }
        RadixSort(D, E, m);
        init(n);
        int ans = 0, select = 0;
        for(i = 0; i < m; i++) {
            if(joint(D[i].x, D[i].y))
                ans = D[i].v, select++;
        }
        if(select == n-1)
            printf("%d\n", ans);
        else
            puts("IMPOSSIBLE");
    }
    return 0;
}
