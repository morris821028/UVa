#include <stdio.h>
int n, A[100005];
struct node {
    int l, r, v;
};
int size = 1, idx;
node Nd[100005];
int build(int vl, int vr, int nd) {
    Nd[nd].v = A[idx];
    idx++;
    if(idx < n && A[idx] < Nd[nd].v && A[idx] >= vl) {
        Nd[nd].l = ++size;
        build(vl, Nd[nd].v, size);
    }
    if(idx < n && A[idx] > Nd[nd].v && A[idx] <= vr) {
        Nd[nd].r = ++size;
        build(Nd[nd].v, vr, size);
    }
}
int travel(int nd) {
    if(Nd[nd].l)
        travel(Nd[nd].l);
    if(Nd[nd].r)
        travel(Nd[nd].r);
    printf("%d", Nd[nd].v);
    puts("");
}
int main() {
    n = 0, idx = 0;
    while(scanf("%d", &A[n]) == 1)
        n++;
    build(-0xfffffff, 0xfffffff, 1);
    travel(1);
    return 0;
}
