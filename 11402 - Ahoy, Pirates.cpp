#include <stdio.h>
#include <string.h>
char A[1048576];
struct st{
    int v, l, r, op;
} tree[2097153];
void build(int k, int l, int r) {
    tree[k].l = l, tree[k].r = r;
    tree[k].v = 0;
    if(l == r) {
        tree[k].v = A[l]-'0';
        tree[k].op = 0;
    }
    if(l < r) {
        int m = (l+r)>>1;
        build(k<<1, l, m);
        build(k<<1|1, m+1, r);
        tree[k].op = 0;
        tree[k].v = tree[k<<1].v + tree[k<<1|1].v;
    }
}
void single(int k) {
    if(tree[k].op) {
        if(tree[k].op == 1)
            tree[k].v = tree[k].r - tree[k].l + 1;
        else if(tree[k].op == 2)
            tree[k].v = 0;
        else
            tree[k].v = tree[k].r - tree[k].l + 1 - tree[k].v;
        if(tree[k].l < tree[k].r) {
            if(tree[k].op == 3) {
                tree[k<<1].op = 3 - tree[k<<1].op;
                tree[k<<1|1].op = 3 - tree[k<<1|1].op;
            } else {
                tree[k<<1].op = tree[k].op;
                tree[k<<1|1].op = tree[k].op;
            }
        }
        tree[k].op = 0;
    }
}
void modify(int k, int l, int r, int op) {
    if(l == tree[k].l && r == tree[k].r) {
        if(op == 3)
            tree[k].op = 3-tree[k].op;
        else
            tree[k].op = op;
    }
    single(k);
    if(l == tree[k].l && r == tree[k].r)
        return;
    int m = (tree[k].l+tree[k].r)>>1;
    if(r <= m)
        modify(k<<1, l, r, op);
    else if(l > m)
        modify(k<<1|1, l, r, op);
    else {
        modify(k<<1, l, m, op);
        modify(k<<1|1, m+1, r, op);
    }
    single(k<<1), single(k<<1|1);
    tree[k].v = tree[k<<1].v + tree[k<<1|1].v;
}
int count(int k, int l, int r) {
    single(k);
    if(l == tree[k].l && r == tree[k].r)
        return tree[k].v;
    int m = (tree[k].l+tree[k].r)>>1;
    if(r <= m)
        return count(k<<1, l, r);
    else if(l > m)
        return count(k<<1|1, l, r);
    else {
        return count(k<<1, l, m)+count(k<<1|1, m+1, r);
    }
    single(k<<1), single(k<<1|1);
    tree[k].v = tree[k<<1].v + tree[k<<1|1].v;
}
int main() {
    int T, M, N, Q, t, i, a, b;
    int Case = 0;
    char str[100], op[3];
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &M);
        N = 0;
        while(M--) {
            scanf("%d %s", &t, str);
            while(t--) {
                for(i = 0; str[i]; i++, N++)
                    A[N] = str[i];
            }
        }
        A[N] = '\0';
        build(1, 0, N-1);
        scanf("%d", &Q);
        printf("Case %d:\n", ++Case);
        int QCase = 0;
        while(Q--) {
            scanf("%s %d %d", op, &a, &b);
            if(op[0] == 'F') {//1
                modify(1, a, b, 1);
            } else if(op[0] == 'E') {//0
                modify(1, a, b, 2);
            } else if(op[0] == 'I') {//XOR
                modify(1, a, b, 3);
            } else {
                printf("Q%d: %d\n", ++QCase, count(1, a, b));
            }
        }
    }
    return 0;
}
