#include <stdio.h>
#include <string.h>
#define NIL -0xffff
typedef struct {
    int v, L, R;
    int r[40], b[40];
} Nd;
Nd D[80];
int err;
void dfs(int nd, int l, int r) {
    if(D[nd].v != NIL && (D[nd].v < l || D[nd].v > r))
        err = 1;
    if(err) return;
    if(D[nd].L) dfs(D[nd].L, l, D[nd].v);
    if(D[nd].R) dfs(D[nd].R, D[nd].v, r);
    if(!D[nd].L && !D[nd].R) { /*leaf*/
        D[nd].b[1] = 1;
    } else {
        int i, blw, brw, rlw, rrw;
        for(i = 0; i < 39; i++) {
            if(D[nd].L) {
                blw = D[D[nd].L].b[i];
                rlw = D[D[nd].L].r[i];
            }
            if(D[nd].R) {
                brw = D[D[nd].R].b[i];
                rrw = D[D[nd].R].r[i];
            }
            if(!D[nd].L)        D[nd].r[i] = brw;
            else if(!D[nd].R)   D[nd].r[i] = blw;
            else                D[nd].r[i] = blw*brw;
            if(!D[nd].L)        D[nd].b[i+1] = brw+rrw;
            else if(!D[nd].R)   D[nd].b[i+1] = blw+rlw;
            else                D[nd].b[i+1] = (blw+rlw)*(brw+rrw);
        }
    }
}
int main() {
    int n, p, s, x, y;
    int i, j, cases = 0;
    while(scanf("%d", &n) == 1) {
        memset(D, 0, sizeof(D));
        int size = 1, in[40] = {};
        err = 0;
        for(i = 1; i < n; i++) {
            scanf("%d %d", &p, &s);
            for(j = 1; j < size; j++)
                if(D[j].v == p)
                    break;
            x = j;
            if(x == size) {D[x].v = p, size++;}
            for(j = 1; j < size; j++)
                if(D[j].v == s)
                    break;
            y = j;
            if(y == size) {D[y].v = s, size++;}
            if(p > s) {
                if(D[x].L)  err = 1;
                D[x].L = y;
            } else {
                if(D[x].R)  err = 1;
                D[x].R = y;
            }
            in[y] = 1;
        }
        if(size != n+1)   err = 1;
        int rt = 0;
        for(i = 1; i < size; i++) {
            if(!in[i]) {
                if(rt)  err = 1;
                rt = i;
            }
        }
        int os = size;
        for(i = 1; i < os; i++) {
            if(!D[i].L) {
                D[i].L = size;
                D[size].v = NIL;
                size++;
            }
            if(!D[i].R) {
                D[i].R = size;
                D[size].v = NIL;
                size++;
            }
        }
        dfs(rt, -0xffff, 0xffff);
        printf("Case %d:", ++cases);
        if(n == 1) {puts("1");continue;}
        if(err) {
            puts("0");
            continue;
        }
        int ans = 0;
        for(i = 0; i < 40; i++)
            ans += D[rt].b[i];
        printf("%d\n", ans);
    }
    return 0;
}
