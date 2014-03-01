#include <stdio.h>
#include <algorithm>
using namespace std;
#define INF 0x7fffffff
#define MaxN 1000005
struct Node {
    int mxv, mnv, sum;
    int add, set;
    int son[4];
};
Node tree[MaxN<<2];
int NSize;
void build(int k, int lx, int rx, int ly, int ry) {
    tree[k].mxv = tree[k].mnv = tree[k].sum = 0;
    tree[k].add = tree[k].set = 0;
    tree[k].son[0] = tree[k].son[1] =
    tree[k].son[2] = tree[k].son[3] = 0; // NULL ptr
    if(lx == rx && ly == ry)
        return;
    int mx = (lx+rx)>>1, my = (ly+ry)>>1;
    if(lx <= mx) {
        if(ly <= my) {
            tree[k].son[0] = ++NSize;
            build(NSize, lx, mx, ly, my);
        }
        if(ry > my) {
            tree[k].son[1] = ++NSize;
            build(NSize, lx, mx, my+1, ry);
        }
    }
    if(rx > mx) {
        if(ly <= my) {
            tree[k].son[2] = ++NSize;
            build(NSize, mx+1, rx, ly, my);
        }
        if(ry > my) {
            tree[k].son[3] = ++NSize;
            build(NSize, mx+1, rx, my+1, ry);
        }
    }
}
#define downop1(k, v) {tree[k].add = 0; tree[k].set = tree[k].mxv = tree[k].mnv = v;}
#define downop2(k, v) {tree[k].add += v, tree[k].mxv += v, tree[k].mnv += v;}
void pushDown(int k, int lx, int rx, int ly, int ry) {
    int mx = (lx+rx)>>1, my = (ly+ry)>>1;
    if(tree[k].set) {
        if(tree[k].son[0]) {
            tree[tree[k].son[0]].sum = (mx-lx+1)*(my-ly+1)*tree[k].set;
            downop1(tree[k].son[0], tree[k].set);
        }
        if(tree[k].son[1]) {
            tree[tree[k].son[1]].sum = (mx-lx+1)*(ry-my)*tree[k].set;
            downop1(tree[k].son[1], tree[k].set);
        }
        if(tree[k].son[2]) {
            tree[tree[k].son[2]].sum = (rx-mx)*(my-ly+1)*tree[k].set;
            downop1(tree[k].son[2], tree[k].set);
        }
        if(tree[k].son[3]) {
            tree[tree[k].son[3]].sum = (rx-mx)*(ry-my)*tree[k].set;
            downop1(tree[k].son[3], tree[k].set);
        }
        tree[k].set = 0;
    }
    if(tree[k].add) {
        if(tree[k].son[0]) {
            tree[tree[k].son[0]].sum += (mx-lx+1)*(my-ly+1)*tree[k].add;
            downop2(tree[k].son[0], tree[k].add);
        }
        if(tree[k].son[1]) {
            tree[tree[k].son[1]].sum += (mx-lx+1)*(ry-my)*tree[k].add;
            downop2(tree[k].son[1], tree[k].add);
        }
        if(tree[k].son[2]) {
            tree[tree[k].son[2]].sum += (rx-mx)*(my-ly+1)*tree[k].add;
            downop2(tree[k].son[2], tree[k].add);
        }
        if(tree[k].son[3]) {
            tree[tree[k].son[3]].sum += (rx-mx)*(ry-my)*tree[k].add;
            downop2(tree[k].son[3], tree[k].add);
        }
        tree[k].add = 0;
    }
}
void pushUp(int k) {
    tree[k].mxv = 0;
    tree[k].mnv = INF;
    tree[k].sum = 0;
    if(tree[k].son[0]) {
        tree[k].sum += tree[tree[k].son[0]].sum;
        tree[k].mxv = max(tree[k].mxv, tree[tree[k].son[0]].mxv);
        tree[k].mnv = min(tree[k].mnv, tree[tree[k].son[0]].mnv);
    }
    if(tree[k].son[1]) {
        tree[k].sum += tree[tree[k].son[1]].sum;
        tree[k].mxv = max(tree[k].mxv, tree[tree[k].son[1]].mxv);
        tree[k].mnv = min(tree[k].mnv, tree[tree[k].son[1]].mnv);
    }
    if(tree[k].son[2]) {
        tree[k].sum += tree[tree[k].son[2]].sum;
        tree[k].mxv = max(tree[k].mxv, tree[tree[k].son[2]].mxv);
        tree[k].mnv = min(tree[k].mnv, tree[tree[k].son[2]].mnv);
    }
    if(tree[k].son[3]) {
        tree[k].sum += tree[tree[k].son[3]].sum;
        tree[k].mxv = max(tree[k].mxv, tree[tree[k].son[3]].mxv);
        tree[k].mnv = min(tree[k].mnv, tree[tree[k].son[3]].mnv);
    }
}
int op_v, op_argv;
int SUM, MXV, MNV;
void modify(int k, int lx, int rx, int ly, int ry, int a, int b, int c, int d) {
    if(a <= lx && rx <= b && c <= ly && ry <= d) {
        if(op_v == 0) {
            SUM += tree[k].sum;
            MXV = max(MXV, tree[k].mxv);
            MNV = min(MNV, tree[k].mnv);
        } else if(op_v == 1) {
            tree[k].add += op_argv;
            tree[k].mxv += op_argv;
            tree[k].mnv += op_argv;
            tree[k].sum += op_argv*(rx-lx+1)*(ry-ly+1);
        } else if(op_v == 2) {
            tree[k].add = 0;
            tree[k].set = tree[k].mxv = tree[k].mnv = op_argv;
            tree[k].sum = op_argv*(rx-lx+1)*(ry-ly+1);
        }
        return;
    }
    int mx = (lx+rx)>>1, my = (ly+ry)>>1;
    pushDown(k, lx, rx, ly, ry);
    if(a <= mx) {
        if(c <= my) {
            if(tree[k].son[0]) {
                modify(tree[k].son[0], lx, mx, ly, my, a, b, c, d);
            }
        }
        if(d > my) {
            if(tree[k].son[1]) {
                modify(tree[k].son[1], lx, mx, my+1, ry, a, b, c, d);
            }
        }
    }
    if(b > mx) {
        if(c <= my) {
            if(tree[k].son[2]) {
                modify(tree[k].son[2], mx+1, rx, ly, my, a, b, c, d);
            }
        }
        if(d > my) {
            if(tree[k].son[3]) {
                modify(tree[k].son[3], mx+1, rx, my+1, ry, a, b, c, d);
            }
        }
    }
    if(op_v)
        pushUp(k);
}
int main() {
    int r, c, q;
    int lx, ly, rx, ry;
    while(scanf("%d %d %d", &r, &c, &q) == 3) {
        NSize = 1;
        build(1, 1, r, 1, c);
        while(q--) {
            scanf("%d %d %d %d %d", &op_v, &lx, &ly, &rx, &ry);
            if(op_v == 1)
                scanf("%d", &op_argv);
            else if(op_v == 2)
                scanf("%d", &op_argv);
            else
                op_v = 0, SUM = 0, MXV = 0, MNV = INF;
            modify(1, 1, r, 1, c, lx, rx, ly, ry);
            if(op_v == 0)
                printf("%d %d %d\n", SUM, MNV, MXV);
        }
    }
    return 0;
}
