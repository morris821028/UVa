#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct Node {
    int mxv;
    int op, v;
};
int R, C;
Node ST[600000]; // init_zero
int op_label, op_v;
int res_sum, res_min, res_max;
int xxxx = 0;
void label_node(int k, int lx, int rx, int ly, int ry, int op, int v) {
    if(lx > rx || ly > ry)  return;
    if(k > 500000) {
        puts("error");
        return;
    }
    if(op == 1) {
        if(ST[k].op == 0) {
            ST[k].op = 1, ST[k].v = v;
        } else if(ST[k].op == 1) {
            ST[k].op = 1, ST[k].v += v;
        } else if(ST[k].op == 2) {
            ST[k].op = 2, ST[k].v = v;
        }
    }
    if(op == 2) {
        ST[k].op = 2, ST[k].v = v;
    }
}
void relax_node(int k, int lx, int rx, int ly, int ry) {
    if(lx > rx || ly > ry)  return;
    if(ST[k].op == 0)   return;
    if(k > 500000) {
        puts("error");
        return;
    }
    int mx = (lx+rx)/2;
    int my = (ly+ry)/2;
    if(ST[k].op == 1) { // add a number
        ST[k].mxv += ST[k].v;
    }
    if(ST[k].op == 2) { // set a number
        ST[k].mxv = ST[k].v;
    }
    label_node(k*4-2, lx, mx, ly, my, ST[k].op, ST[k].v);
    label_node(k*4-1, mx+1, rx, ly, my, ST[k].op, ST[k].v);
    label_node(k*4, lx, mx, my+1, ry, ST[k].op, ST[k].v);
    label_node(k*4+1, mx+1, rx, my+1, ry, ST[k].op, ST[k].v);
    ST[k].op = 0;
}

int getMax(int k, int lx, int rx, int ly, int ry) {
    if(lx > rx || ly > ry)  return -2147483647;
    return ST[k].mxv;
}
void update_node(int k, int lx, int rx, int ly, int ry) {
    if(lx > rx || ly > ry)  return;
    if(k > 500000)  {
        puts("ERROR");
        return;
    }
    int mx = (lx+rx)/2;
    int my = (ly+ry)/2;
    relax_node(k*4-2, lx, mx, ly, my);
    relax_node(k*4-1, mx+1, rx, ly, my);
    relax_node(k*4, lx, mx, my+1, ry);
    relax_node(k*4+1, mx+1, rx, my+1, ry);
    ST[k].mxv = max(getMax(k*4-2, lx, mx, ly, my), max(getMax(k*4-1, mx+1, rx, ly, my),
            max(getMax(k*4, lx, mx, my+1, ry), getMax(k*4+1, mx+1, rx, my+1, ry))));
}
void modify(int k, int lx, int rx, int ly, int ry, int qlx, int qrx, int qly, int qry) {
    if(lx > rx || ly > ry)  return;
    if(k > 600000)  puts("ERROR");
    if(k > xxxx)    xxxx = k;
    relax_node(k, lx, rx, ly, ry);
    if(lx >= qlx && qrx >= rx && ly >= qly && qry >= ry) {
        if(op_label) {
            label_node(k, lx, rx, ly, ry, op_label, op_v);
            relax_node(k, lx, rx, ly, ry);
        } else {
            res_max = max(res_max, ST[k].mxv);
        }
        //printf("[%d] [%d %d][%d %d] sum = %d\n", k, lx, ly, rx, ry, ST[k].sum);
        return ;
    }
    int mx = (lx+rx)/2;
    int my = (ly+ry)/2;
    if(qlx <= mx && qly <= my)
        modify(k*4-2, lx, mx, ly, my, qlx, qrx, qly, qry);
    if(res_max >= ST[k].mxv && !op_label)    return;
    if(qrx > mx && qly <= my)
        modify(k*4-1, mx+1, rx, ly, my, qlx, qrx, qly, qry);
    if(res_max >= ST[k].mxv && !op_label)    return;
    if(qlx <= mx && qry > my)
        modify(k*4, lx, mx, my+1, ry, qlx, qrx, qly, qry);
    if(res_max >= ST[k].mxv && !op_label)    return;
    if(qrx > mx && qry > my)
        modify(k*4+1, mx+1, rx, my+1, ry, qlx, qrx, qly, qry);
    update_node(k, lx, rx, ly, ry);
}
int main() {
    int r, c, m;
    int i, j;
    int op, v, x1, x2, y1, y2;
    while(scanf("%d %d", &r, &c) == 2) {
        op_label = 2, op_v = 0;
        for(i = 1; i <= r; i++)
            for(j = 1; j <= c; j++) {
                op_label = 2;
                scanf("%d", &op_v);
                modify(1, 1, r, 1, c, i, i, j, j);
            }
        scanf("%d", &m);
        while(m--) {
            op_label = 0;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            res_sum = 0, res_min = 2147483647, res_max = -res_min;
            modify(1, 1, r, 1, c, x1, x2, y1, y2);
            //printf("%d\n", res_max);
        }
    }
    printf("%d\n", xxxx);
    return 0;
}
/*
5 6
7 4 3 7 5 1
3 4 7 1 1 6
0 1 8 3 2 5
1 5 9 5 1 5
8 2 6 6 4 5
10
2 4 5 5
1 4 5 5
1 2 3 5
4 2 5 3
4 4 5 5
2 1 5 4
3 4 5 5
2 2 4 2
2 2 2 5
4 3 4 4
*/
