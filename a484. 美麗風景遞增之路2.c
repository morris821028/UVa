#include <stdio.h>
#include <stdlib.h>
typedef struct {
    short x, y, v;
} ele;
ele D[1000005];
int cmp(const void *i, const void *j) {
    ele *a, *b;
    a = (ele *)i, b = (ele *)j;
    if(a->v != b->v)
        return a->v - b->v;
    if(a->x != b->x)
        return b->x - a->x;
    return b->y - a->y;
}
int BIT[1001][1001], lowbit[1001];
int t, R, C, i, j, v;
int query(int x, int y) {
    int sum = 0, i, j;
    for(i = x; i > 0; i -= lowbit[i]) {
        for(j = y; j > 0; j -= lowbit[j]) {
            sum += BIT[i][j];
            if(sum >= 1000000007)
                sum -= 1000000007;
        }
    }
    return sum;
}
void modify(int x, int y, int v) {
    int i, j;
    for(i = x; i <= R; i += lowbit[i]) {
        for(j = y; j <= C; j += lowbit[j]) {
            BIT[i][j] += v;
            if(BIT[i][j] >= 1000000007)
                BIT[i][j] -= 1000000007;
        }
    }
}
int main() {
    for(i = 0; i <= 1000; i++)
        lowbit[i] = i&(-i);
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &R, &C);
        int m = 0;
        for(i = 0; i < R; i++) {
            for(j = 0; j < C; j++) {
                scanf("%d", &v);
                D[m].x = i, D[m].y = j, D[m].v = v;
                m++;
            }
        }
        qsort(D, m, sizeof(ele), cmp);
        for(i = 0; i <= R; i++)
            for(j = 0; j <= C; j++)
                BIT[i][j] = 0;
        for(i = 0; i < m; i++) {
            int tmp = query(D[i].x+1, D[i].y+1);
            tmp++;
            modify(D[i].x+1, D[i].y+1, tmp);
        }
        printf("%d\n", query(R, C));
    }
    return 0;
}
