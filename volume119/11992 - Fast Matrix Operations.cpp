#include <stdio.h>
#include <algorithm>
using namespace std;
struct Node {
    int mxv, mnv, sum;
    int op, v;
    Node() {
        mxv = 0;
        mnv = 0;
        sum = 0;
        op = v = 0;
    }
};
int R, C;
Node *ST[1000000];
int op_label, op_v;
int res_sum, res_min, res_max;
void label_node(int, int, int, int, int, int, int, int);
int node_sum(int fk, int sk, int lr, int rr, int lc, int rc) {
    if(lc > rc) return 0;
    if(lr > rr) return 0;
    return ST[fk][sk].sum;
}
void update_node(int fk, int sk, int lr, int rr, int lc, int rc) {
    int mr, mc;
    mr = (lr+rr)/2;
    mc = (lc+rc)/2;
    ST[fk][sk].sum = node_sum(fk<<1, sk, lr, mr, lc, rc)+node_sum(fk<<1|1, sk, mr+1, rr, lc, rc);
}
void update_col_node(int fk, int sk, int lr, int rr, int lc, int rc) {
    int mr, mc;
    mr = (lr+rr)/2;
    mc = (lc+rc)/2;
    ST[fk][sk].sum = node_sum(fk, sk<<1, lr, rr, lc, mc)+node_sum(fk, sk<<1|1, lr, rr, mc+1, rc);
}
void relax_node(int fk, int sk, int lr, int rr, int lc, int rc) {
    if(lr > rr || lc > rc)
        return;
    if(ST[fk][sk].op == 0)
        return;
    int mr, mc;
    mr = (lr+rr)/2;
    mc = (lc+rc)/2;
    label_node(fk, sk<<1, lr, rr, lc, mc, ST[fk][sk].op, ST[fk][sk].v);
    label_node(fk, sk<<1|1, lr, rr, mc+1, rc, ST[fk][sk].op, ST[fk][sk].v);
    label_node(fk<<1, sk, lr, mr, lc, rc, ST[fk][sk].op, ST[fk][sk].v);
    label_node(fk<<1|1, sk, mr+1, rr, lc, rc, ST[fk][sk].op, ST[fk][sk].v);
    if(ST[fk][sk].op == 1) { // add a number
        ST[fk][sk].sum += ST[fk][sk].v * (rr-lr+1) * (rc-lc+1);
        ST[fk][sk].mxv += ST[fk][sk].v;
        ST[fk][sk].mnv += ST[fk][sk].v;
    } else { // assign a number
        ST[fk][sk].sum = ST[fk][sk].v * (rr-lr+1) * (rc-lc+1);
        ST[fk][sk].mxv = ST[fk][sk].v;
        ST[fk][sk].mnv = ST[fk][sk].v;
    }
    ST[fk][sk].op = 0;
}
void label_node(int fk, int sk, int lr, int rr, int lc, int rc, int op, int v) {
    if(lr > rr || lc > rc)
        return;
    if(op == 0)   return;
    if(ST[fk][sk].op == 0) {
        ST[fk][sk].op = op;
        ST[fk][sk].v = v;
        return;
    }
    if(op == 1 && ST[fk][sk].op == 1) // add1 then add2 = add1+add2
        ST[fk][sk].v += v;
    else if(op == 2 && ST[fk][sk].op == 2) // assign1 then assign2 = assign2
        ST[fk][sk].v = v;
    else if(op == 1 && ST[fk][sk].op == 2) // assign then add = assign v+add
        ST[fk][sk].v += v;
    else //add then assign = assign
        ST[fk][sk].v = v, ST[fk][sk].op = 2;
}
void submodify(int fk, int sk, int lr, int rr, int lc, int rc, int qlr, int qrr, int qlc, int qrc) {
    if(lc > rc) return;
    printf("%d %d %d %d %d %d submodify\n", fk, sk, lc, rc, qlc, qrc);
   // getchar();
    relax_node(fk, sk, lr, rr, lc, rc);
    printf("matched [%d %d][%d %d] %d\n", lr, rr, lc, rc, ST[fk][sk].sum);
    if(lc == qlc && rc == qrc) {
        label_node(fk, sk, lr, rr, lc, rc, op_label, op_v);
        relax_node(fk, sk, lr, rr, lc, rc);
        printf("labeled [%d %d][%d %d] %d\n", lr, rr, lc, rc, ST[fk][sk].sum);
        if(lr == qlr && rr == qrr && lc == qlc && rc == qrc) {
            res_sum += ST[fk][sk].sum;
            res_min = min(res_min, ST[fk][sk].mnv);
            res_max = max(res_max, ST[fk][sk].mxv);
        }
        return;
    }
    int m = (lc+rc)/2;
    printf("[%d %d] => [%d %d] [%d %d]\n", lc, rc, lc, m, m+1, rc);
    if(qrc <= m)
        submodify(fk, sk<<1, lr, rr, lc, m, qlr, qrr, qlc, qrc);
    else if(qlc > m)
        submodify(fk, sk<<1|1, lr, rr, m+1, rc, qlr, qrr, qlc, qrc);
    else {
        submodify(fk, sk<<1, lr, rr, lc, m, qlr, qrr, qlc, m);
        submodify(fk, sk<<1|1, lr, rr, m+1, rc, qlr, qrr, m+1, qrc);
    }
    if(lr == qlr && rr == qrr)
        update_col_node(fk, sk, lr, rr, lc, rc);
    else update_node(fk, sk, lr, rr, lc, rc);
    printf("Node : [%d %d][%d %d] %d %d\n", lr, rr, lc, rc, ST[fk][sk].sum, res_sum);
}
void modify(int fk, int lr, int rr, int lc, int rc, int qlr, int qrr, int qlc, int qrc) {
    if(lr > rr) return;
    if(lr == qlr && rr == qrr) {
        printf("modifty [%d %d]\n", lr, rr);
        submodify(fk, 1, lr, rr, lc, rc, qlr, qrr, qlc, qrc);
        return;
    }
    //printf("%d modifty\n", fk);
    //getchar();
    int m = (lr+rr)/2;
    if(qrr <= m)
        modify(fk<<1, lr, m, lc, rc, qlr, qrr, qlc, qrc);
    else if(qlr > m)
        modify(fk<<1|1, m+1, rr, lc, rc, qlr, qrr, qlc, qrc);
    else {
        modify(fk<<1, lr, m, lc, rc, qlr, m, qlc, qrc);
        modify(fk<<1|1, m+1, rr, lc, rc, m+1, qrr, qlc, qrc);
    }
    submodify(fk, 1, lr, rr, lc, rc, qlr, qrr, qlc, qrc);
}
int main() {
    int r, c, m;
    int i, j;
    int op, v, x1, x2, y1, y2;
    while(scanf("%d %d %d", &r, &c, &m) == 3) {
        for(R = 1; R <= r; R <<= 1);
        for(C = 1; C <= c; C <<= 1);
        for(i = 1; i <= R; i++)
            ST[i] = new Node[C];
        while(m--) {
            scanf("%d", &op);
            op_label = op;
            if(op == 1) {
                scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &v);
                op_v = v;
            } else if(op == 2) {
                scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &v);
                op_v = v;
            } else {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                op_label = 0;
            }
            res_sum = 0, res_min = 2147483647, res_max = -res_min;
            modify(1, 1, r, 1, c, x1, x2, y1, y2);
            printf("%d %d %d\n", res_sum, res_min, res_max);
        }
        for(i = 1; i <= R; i++)
            delete[] ST[i];
    }
    return 0;
}
/*
4 4 8
1 1 2 4 4 5
3 2 1 4 4
1 1 1 3 4 2
3 1 2 4 4
3 1 1 3 4
2 2 1 4 4 2
3 1 2 4 4
1 1 1 4 3 3
*/
