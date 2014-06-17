#include <stdio.h>
#include <stdlib.h>
#define maxN 65000
typedef struct {
    int x, i, org;
} Arr;
typedef struct {
    int l, r;
} Node;
Arr a[maxN];
Node ST[131072];
Arr seg[20][maxN];
int bit[20][maxN];
int ibound[maxN], jbound[maxN];
int cmp(const void *i, const void *j) {
    static Arr *a, *b;
    a = (Arr *)i, b = (Arr *)j;
    if(a->i != b->i)
        return a->i - b->i;
    return a->x - b->x;
}
void build(int l, int r, int k, int dep) {
    ST[k].l = ibound[l], ST[k].r = jbound[r];
    int i, j;
    if(l == r) {
        for(i = ibound[l]; i <= jbound[r]; i++)
            seg[dep][i] = a[i];
        return;
    }
    int m = (l+r)>>1;
    build(l, m, k<<1, dep+1);
    build(m+1, r, k<<1|1, dep+1);
    int idx1 = ibound[l], idx2 = ibound[m+1], top = ibound[l];
    while(idx1 <= jbound[m] && idx2 <= jbound[r]) {
        if(seg[dep+1][idx1].x <= seg[dep+1][idx2].x)
            seg[dep][top++] = seg[dep+1][idx1++];
        else
            seg[dep][top++] = seg[dep+1][idx2++];
    }
    while(idx1 <= jbound[m])    seg[dep][top++] = seg[dep+1][idx1++];
    while(idx2 <= jbound[r])    seg[dep][top++] = seg[dep+1][idx2++];
    idx2 = jbound[r] - ibound[l] + 1;
    for(i = ibound[l]; i <= jbound[r]; i++) {
        if(seg[dep][i].org) {
            idx1 = i - ibound[l]+1;
            while(idx1 <= idx2) {
                bit[dep][idx1 + ibound[l] - 1]++;
                idx1 += idx1&(-idx1);
                //puts("loop2");
            }
            //puts("end");
        }
    }
}
int find(int ql, int qr, int k, int dep, int val) {
    if(ql <= ST[k].l && ST[k].r <= qr) {
        int l = ST[k].l, r = ST[k].r, m;
        while(l < r) {
            m = (l+r)>>1;
            //printf("l %d r %d x %d\n", l, r, seg[dep][m].x);
            if(seg[dep][m].x < val)
                l = m+1;
            else
                r = m;
        }
        //for(int i = ST[k].l; i <= ST[k].r; i++)
          //  printf("%d ", seg[dep][i].x);
        //puts("seg");
        l--;
        //printf("%d - ", seg[dep][l].x);
        int sum = 0, idx = l - ST[k].l+1;
        while(idx) {
            sum += bit[dep][idx + ST[k].l - 1];
            idx -= idx&(-idx);
        }
        //printf("%d\n", sum);
        return sum;
    }
    int res = 0;
    if(ql <= ST[k<<1].r)
        res += find(ql, qr, k<<1, dep+1, val);
    if(qr >= ST[k<<1|1].l)
        res += find(ql, qr, k<<1|1, dep+1, val);
    return res;
}
void modify(int idx, int k, int dep, int org, int val) {
    if(ST[k].l <= idx && ST[k].r >= idx) {
        int l = ST[k].l, r = ST[k].r, m;
        while(l < r) {
            m = (l+r)>>1;
            if(seg[dep][m].x < org)
                l = m+1;
            else
                r = m;
        }
        //printf("C- %d\n", seg[dep][l].x);
        int idx1, idx2;
        idx1 = l - ibound[ST[k].l]+1;
        idx2 = jbound[ST[k].r] - ibound[ST[k].l]+1;
        while(idx1 <= idx2) {
            bit[dep][idx1 + ibound[ST[k].l] - 1]--;
            idx1 += idx1&(-idx1);
        }
        l = ST[k].l, r = ST[k].r;
        while(l < r) {
            m = (l+r)>>1;
            if(seg[dep][m].x < val)
                l = m+1;
            else
                r = m;
        }
        //printf("C+ %d\n", seg[dep][l].x);
        idx1 = l - ibound[ST[k].l]+1;
        idx2 = jbound[ST[k].r] - ibound[ST[k].l]+1;
        while(idx1 <= idx2) {
            bit[dep][idx1 + ibound[ST[k].l] - 1]++;
            idx1 += idx1&(-idx1);
        }
        modify(idx, k<<1, dep+1, org, val);
        modify(idx, k<<1|1, dep+1, org, val);
    }
}
int main() {
    int n, m, i, j;
    int ci[10000], cj[10000], ck[10000];
    char cmd[10000][2];
    int org[maxN];
    while(scanf("%d %d", &n, &m) == 2) {
        int rn = n;
        for(i = 1; i <= n; i++) {
            scanf("%d", &org[i]);
            a[i].x = org[i];
            a[i].i = i;
            a[i].org = 1;
        }
        for(i = 0; i < m; i++) {
            scanf("%s %d %d", cmd[i], &ci[i], &cj[i]);
            if(cmd[i][0] == 'Q') {
                scanf("%d", &ck[i]);
            } else {
                n++;
                a[n].x = cj[i];
                a[n].i = ci[i];
                a[n].org = 0;
            }
        }
        qsort(a+1, n, sizeof(Arr), cmp);

        for(i = 1, j = n; i <= n; i++, j--)
            ibound[a[j].i] = j, jbound[a[i].i] = i;
        build(1, rn, 1, 1);
        for(i = 0; i < m; i++) {
            if(cmd[i][0] == 'Q') {
                int l = 1, r = n, tm;
                while(l < r) {
                    tm = (l+r)>>1;
                   // printf("Q %d %d %d\n", ci[i], cj[i], ck[i]);
                    //printf("%d %d %d %d\n", l, tm, r, seg[1][tm].x);
                    if(find(ci[i], cj[i], 1, 1, seg[1][tm].x) < ck[i]) {
                        l = tm+1;
                        //printf("ac %d\n", seg[1][tm].x);
                    } else
                        r = tm;
                }
                printf("%d\n", seg[1][l-1].x);
            } else {
                if(org[ci[i]] != cj[i]) {
                    modify(ci[i], 1, 1, org[ci[i]], cj[i]);
                    org[ci[i]] = cj[i];
                }
            }
        }
    }
    return 0;
}
/*
n < 50000
m < 10000
*/
