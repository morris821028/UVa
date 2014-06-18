#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct Node {
    int mxv, mnv, sum;
    int op, v;
    int by[4];
};
int R, C;
Node ST[2000005]; // init_zero
int STsize = 0;
int op_label, op_v;
int res_sum, res_min, res_max;
void relax_node(int, int, int, int, int);
int getSum(int k, int lx, int rx, int ly, int ry) {
    if(lx > rx || ly > ry)  return 0;
    return ST[k].sum;
}
int getMax(int k, int lx, int rx, int ly, int ry) {
    if(lx > rx || ly > ry)  return -2147483647;
    return ST[k].mxv;
}
int getMin(int k, int lx, int rx, int ly, int ry) {
    if(lx > rx || ly > ry)  return 2147483647;
    return ST[k].mnv;
}
int init_ST(int lx, int rx, int ly, int ry) {
    if(lx > rx || ly > ry)  return -1;
    //printf("[%d %d] [%d %d]\n", lx, ly, rx, ry);
    //getchar();
    int mx = (lx+rx)/2;
    int my = (ly+ry)/2;
    int by[4];
    if(lx == rx && ly == ry) {
        by[0] = by[1] = by[2] = by[3] = -1;}
    else {
        by[0] = init_ST(lx, mx, ly, my);
        by[1] = init_ST(mx+1, rx, ly, my);
        by[2] = init_ST(lx, mx, my+1, ry);
        by[3] = init_ST(mx+1, rx, my+1, ry);
    }
    ++STsize;
    memcpy(ST[STsize].by, by, sizeof(by));
    return STsize;
}
void label_node(int k, int lx, int rx, int ly, int ry, int op, int v) {
    if(lx > rx || ly > ry || op == 0 || k < 0)  return;
    //puts("label");
    if(op == 1) {
        if(ST[k].op == 0) {
            ST[k].op = 1, ST[k].v = v;
        } else if(ST[k].op == 1) {
            ST[k].op = 1, ST[k].v += v;
        } else if(ST[k].op == 2) {
            ST[k].op = 2, ST[k].v = v;
        }
    }
    if(op == 2)
        ST[k].op = 2, ST[k].v = v;
}
void update_node(int k, int lx, int rx, int ly, int ry) {
    //puts("update");
    if(lx > rx || ly > ry || k < 0)  return ;
    int mx = (lx+rx)/2;
    int my = (ly+ry)/2;
    if(lx == rx && ly == ry)
        return;
    relax_node(ST[k].by[0], lx, mx, ly, my);
    relax_node(ST[k].by[1], mx+1, rx, ly, my);
    relax_node(ST[k].by[2], lx, mx, my+1, ry);
    relax_node(ST[k].by[3], mx+1, rx, my+1, ry);
    ST[k].sum = getSum(ST[k].by[0], lx, mx, ly, my)+getSum(ST[k].by[1], mx+1, rx, ly, my)+
            getSum(ST[k].by[2], lx, mx, my+1, ry)+getSum(ST[k].by[3], mx+1, rx, my+1, ry);
    ST[k].mxv = max(getMax(ST[k].by[0], lx, mx, ly, my), max(getMax(ST[k].by[1], mx+1, rx, ly, my),
            max(getMax(ST[k].by[2], lx, mx, my+1, ry), getMax(ST[k].by[3], mx+1, rx, my+1, ry))));
    ST[k].mnv = min(getMin(ST[k].by[0], lx, mx, ly, my), min(getMin(ST[k].by[1], mx+1, rx, ly, my),
            min(getMin(ST[k].by[2], lx, mx, my+1, ry), getMin(ST[k].by[3], mx+1, rx, my+1, ry))));
}
void relax_node(int k, int lx, int rx, int ly, int ry) {
    if(lx > rx || ly > ry || k < 0)  return;
    //puts("relax");
    if(ST[k].op == 0)   return;
    int mx = (lx+rx)/2;
    int my = (ly+ry)/2;
    if(ST[k].op == 1) { // add a number
        ST[k].mxv += ST[k].v;
        ST[k].mnv += ST[k].v;
        ST[k].sum += ST[k].v * (rx-lx+1) * (ry-ly+1);
    }
    if(ST[k].op == 2) { // set a number
        ST[k].mxv = ST[k].v;
        ST[k].mnv = ST[k].v;
        ST[k].sum = ST[k].v * (rx-lx+1) * (ry-ly+1);
    }

    if(lx == rx && ly == ry) {}
    else {
        label_node(ST[k].by[0], lx, mx, ly, my, ST[k].op, ST[k].v);
        label_node(ST[k].by[1], mx+1, rx, ly, my, ST[k].op, ST[k].v);
        label_node(ST[k].by[2], lx, mx, my+1, ry, ST[k].op, ST[k].v);
        label_node(ST[k].by[3], mx+1, rx, my+1, ry, ST[k].op, ST[k].v);
    }
    //if(flag == 0)
        //update_node(k, lx, rx, ly, ry);
    ST[k].op = 0;
}
void modify(int k, int lx, int rx, int ly, int ry, int qlx, int qrx, int qly, int qry) {
    if(lx > rx || ly > ry)  return;
    //update_node(k, lx, rx, ly, ry);
    int mx = (lx+rx)/2;
    int my = (ly+ry)/2;
    relax_node(k, lx, rx, ly, ry);
    relax_node(ST[k].by[0], lx, mx, ly, my);
    relax_node(ST[k].by[1], mx+1, rx, ly, my);
    relax_node(ST[k].by[2], lx, mx, my+1, ry);
    relax_node(ST[k].by[3], mx+1, rx, my+1, ry);
    update_node(ST[k].by[0], lx, mx, ly, my);
    update_node(ST[k].by[1], mx+1, rx, ly, my);
    update_node(ST[k].by[2], lx, mx, my+1, ry);
    update_node(ST[k].by[3], mx+1, rx, my+1, ry);
    update_node(k, lx, rx, ly, ry);
    //printf("[%d %d] [%d %d]\n", lx, ly, rx, ry);
    if(lx >= qlx && qrx >= rx && ly >= qly && qry >= ry) {
        if(op_label) {
            label_node(k, lx, rx, ly, ry, op_label, op_v);
            relax_node(k, lx, rx, ly, ry);
            relax_node(ST[k].by[0], lx, mx, ly, my);
            relax_node(ST[k].by[1], mx+1, rx, ly, my);
            relax_node(ST[k].by[2], lx, mx, my+1, ry);
            relax_node(ST[k].by[3], mx+1, rx, my+1, ry);
            update_node(ST[k].by[0], lx, mx, ly, my);
            update_node(ST[k].by[1], mx+1, rx, ly, my);
            update_node(ST[k].by[2], lx, mx, my+1, ry);
            update_node(ST[k].by[3], mx+1, rx, my+1, ry);
            update_node(k, lx, rx, ly, ry);
        }
        if(op_label == 0 || op_label < 0) {
            res_sum += ST[k].sum;
            res_max = max(res_max, ST[k].mxv);
            res_min = min(res_min, ST[k].mnv);
            //if(op_label == 0)
            //printf("[%d %d] [%d %d] %d\n", lx, ly, rx, ry, ST[k].sum);
        }
        return ;
    }
    if(qlx <= mx && qly <= my)
        modify(ST[k].by[0], lx, mx, ly, my, qlx, qrx, qly, qry);
    if(qrx > mx && qly <= my)
        modify(ST[k].by[1], mx+1, rx, ly, my, qlx, qrx, qly, qry);
    if(qlx <= mx && qry > my)
        modify(ST[k].by[2], lx, mx, my+1, ry, qlx, qrx, qly, qry);
    if(qrx > mx && qry > my)
        modify(ST[k].by[3], mx+1, rx, my+1, ry, qlx, qrx, qly, qry);
    if(op_label) {
        relax_node(k, lx, rx, ly, ry);
        relax_node(ST[k].by[0], lx, mx, ly, my);
        relax_node(ST[k].by[1], mx+1, rx, ly, my);
        relax_node(ST[k].by[2], lx, mx, my+1, ry);
        relax_node(ST[k].by[3], mx+1, rx, my+1, ry);
        update_node(ST[k].by[0], lx, mx, ly, my);
        update_node(ST[k].by[1], mx+1, rx, ly, my);
        update_node(ST[k].by[2], lx, mx, my+1, ry);
        update_node(ST[k].by[3], mx+1, rx, my+1, ry);
        update_node(k, lx, rx, ly, ry);
    }
}
int main() {
    int r, c, m;
    int i, j;
    int op, v, x1, x2, y1, y2;
    int g[20][20] = {};
    int runtime = 0;
    while(scanf("%d %d %d", &r, &c, &m) == 3) {
        STsize = 0;
        int root = init_ST(1, r, 1, c);
        op_label = 2, op_v = 0;
        modify(root, 1, r, 1, c, 1, r, 1, c);
        while(m--) {
            runtime++;
            if(runtime == 1000) {
                return 0;
            }
            scanf("%d", &op);
            op_label = op;
            if(op == 1) {
                scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &v);
                op_v = v;
                /*for(i = x1; i <= x2; i++)
                    for(j = y1; j <= y2; j++)
                        g[i][j] += v;*/
            } else if(op == 2) {
                scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &v);
                op_v = v;
                /*for(i = x1; i <= x2; i++)
                    for(j = y1; j <= y2; j++)
                        g[i][j] = v;*/
            } else {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                op_label = 0;
            }
            //printf("%d %d %d %d\n", x1, y1, x2, y2);
            res_sum = 0, res_min = 2147483647, res_max = -res_min;
            modify(root, 1, r, 1, c, x1, x2, y1, y2);
            if(op_label == 0)
                printf("%d %d %d\n", res_sum, res_min, res_max);
            /*for(i = 1; i <= r; i++) {
                for(j = 1; j <= c; j++) {
                    res_sum = 0, op_label = -1;
                    modify(root, 1, r, 1, c, i, i, j, j);
                    if(res_sum != g[i][j]) {
                        puts("error");
                        i = r+1, j = c+1;
                    }
                }
            }*/

        }
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

15 15 10000
2 4 6 14 8 54
1 7 4 13 11 46
1 8 10 14 15 67
1 2 3 13 10 21
3 2 10 14 15
2 7 7 15 11 32
1 6 2 14 14 59
2 9 7 15 14 71
2 5 8 11 12 92
2 5 8 14 15 59
2 6 1 13 4 64
3 6 1 14 10

15 15 1000
2 1 2 12 12 42
1 7 1 15 8 15
1 4 2 12 15 40
2 2 2 14 14 97
2 3 3 6 12 62
3 4 3 5 15
*/
