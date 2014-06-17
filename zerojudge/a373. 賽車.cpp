#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef struct {
    int x, v, i;
} Car;
typedef struct {
    double t, s;
    int a, b;
} ele;
struct cmp {
    bool operator() (ele a, ele b) {
        if(a.t != b.t)
            return a.t > b.t;
        return a.s > b.s;
    }
};
Car A[250000], X[250000];
int ans;
void Merge(int l, int m, int r) {
    int idx1 = l, idx2 = m+1, top = 0, i, j;
    int D = 0;
    while(idx1 <= m && idx2 <= r) {
        if(A[idx1].v <= A[idx2].v)
            X[top++] = A[idx1++], ans += D;
        else
            X[top++] = A[idx2++], D++;
        if(ans >= 1000000)  ans -= 1000000;
        if(D >= 1000000)    D -= 1000000;
    }
    while(idx1 <= m) {
        X[top++] = A[idx1++], ans += D;
        if(ans >= 1000000)
            ans -= 1000000;
    }
    while(idx2 <= r)    X[top++] = A[idx2++], D++;
    for(i = 0, j = l; i < top; i++, j++)
        A[j] = X[i];
}
void Msort(int l, int r) {
    if(l < r) {
        int m = (l+r)>>1;
        Msort(l, m);
        Msort(m+1, r);
        Merge(l, m, r);
    }
}
int main() {
    int n, i;
    int wh[250000];
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++) {
            scanf("%d %d", &A[i].x, &A[i].v);
            A[i].i = i;
            wh[i] = i;
        }
        ele E, T;
        priority_queue<ele, vector<ele>, cmp> Q;
        for(i = 1; i < n; i++) {
            if(A[i-1].v > A[i].v) {
                E.a = A[i-1].i, E.b = A[i].i;
                E.t = (double)(A[i].x - A[i-1].x)/(A[i-1].v - A[i].v);
                E.s = A[i].x + E.t*A[i].v;
                Q.push(E);
            }
        }
        int cnt = 0, Ea[10000], Eb[10000];
        while(cnt < 10000 && !Q.empty()) {
            E = Q.top();
            Q.pop();
            if(wh[E.a]+1 == wh[E.b]) {
                Ea[cnt] = E.a+1, Eb[cnt] = E.b+1;
                cnt++;
                i = wh[E.a];
                swap(A[wh[E.a]], A[wh[E.b]]);
                wh[A[i].i] = i, wh[A[i+1].i] = i+1;
                i = wh[E.b];
                if(i-1 >= 0 && A[i-1].v > A[i].v) {
                    T.a = A[i-1].i, T.b = A[i].i;
                    T.t = (double)(A[i].x - A[i-1].x)/(A[i-1].v - A[i].v);
                    T.s = A[i].x + T.t*A[i].v;
                    Q.push(T);
                }
                i = wh[E.a];
                if(i+1 < n && A[i].v > A[i+1].v) {
                    T.a = A[i].i, T.b = A[i+1].i;
                    T.t = (double)(A[i+1].x - A[i].x)/(A[i].v - A[i+1].v);
                    T.s = A[i].x + T.t*A[i].v;
                    Q.push(T);
                }
            }
        }
        ans = 0;
        Msort(0, n-1);
        ans += cnt;
        printf("%d\n", ans);
        for(i = 0; i < cnt; i++)
            printf("%d %d\n", Ea[i], Eb[i]);
    }
    return 0;
}
