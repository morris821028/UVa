#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define SIZE 550
struct ele {
    int v, idx;
};
ele piece[SIZE][SIZE];
int A[SIZE*SIZE];
bool cmp(ele a, ele b) {
    return a.v < b.v;
}
int query(int l, int r, int v) {
    static int cnt, lp, rp, m, tl, tr;
    cnt = 0;
    tl = l;
    tr = r;
    while(l%SIZE && l <= r) {
        if(A[l] < v)    cnt++;
        l++;
    }
    while((r+1)%SIZE && l <= r) {
        if(A[r] < v)    cnt++;
        r--;
    }
    if(l > r)   return cnt;
    lp = l/SIZE, rp = r/SIZE, v--;
    while(lp <= rp) {
        l = 0, r = SIZE-1;
        while(l < r) {
            m = (l+r+1)>>1;
            if(piece[lp][m].v <= v)
                l = m;
            else
                r = m-1;
        }
        if(piece[lp][l].v > v)    l--;
        cnt += l+1;
        lp++;
    }
    return cnt;
}
int main() {
    int n, m, u, l, r, v, p;
    int i, j, x, y;
    while(scanf("%d %d %d", &n, &m, &u) == 3) {
        for(i = 0, j = (n-1)/SIZE; i < SIZE; i++)
            piece[j][i].v = 2147483647, piece[j][i].idx = -1;
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            piece[i/SIZE][i%SIZE].v = A[i];
            piece[i/SIZE][i%SIZE].idx = i;
        }
        for(i = (n-1)/SIZE; i >= 0; i--)
            sort(piece[i], piece[i]+SIZE, cmp);
        /*for(i = 0; i <= psize; i++, puts(""))
            for(j = 0; j < pidx[i]; j++)
                printf("%d ", piece[i][j].v);*/
        while(m--) {
            scanf("%d %d %d %d", &l, &r, &v, &p);
            l--, r--, p--;
            x = query(l, r, v);
            y = (int)((long long)x*u/(r-l+1));
            x = p/SIZE;
            for(i = 0; piece[x][i].idx != p; i++);
            for(; i < SIZE; i++) {
                piece[x][i].v = piece[x][i+1].v;
                piece[x][i].idx = piece[x][i+1].idx;
            }
            for(i = SIZE-2; i >= 0 && piece[x][i].v > y; i--) {
                piece[x][i+1].v = piece[x][i].v;
                piece[x][i+1].idx = piece[x][i].idx;
            }
            piece[x][i+1].v = y;
            piece[x][i+1].idx = p;
            A[p] = y;
        }
        for(i = 0; i < n; i++)
            printf("%d\n", A[i]);
    }
    return 0;
}
