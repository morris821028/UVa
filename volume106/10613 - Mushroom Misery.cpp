#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

struct Seg {
    int st, ed, x;
    void set(int a, int b, int c) {
        st = a, ed = b, x = c;
    }
};
Seg S[2000000];
int Ssize;
bool cmp(Seg a, Seg b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.st < b.st;
}
void cut2seg(double x, double y, double r, int size) {
    int L, R, M, i, st, ed;
    L = max(0, (int)floor(y-r));
    R = min(size, (int)ceil(y+r));
    M = (int)floor(y);
    for(i = L; i < M; i++) {
        st = max(0, (int)floor(x-sqrt(r*r-(y-i-1)*(y-i-1))));
        ed = min(size, (int)ceil(x+sqrt(r*r-(y-i-1)*(y-i-1))));
        S[Ssize++].set(st, ed, i);
    }
    st = max(0, (int)floor(x-r));
    ed = min(size, (int)ceil(x+r));
    S[Ssize++].set(st, ed, M);
    for(i = M+1; i < R; i++) {
        st = max(0, (int)floor(x-sqrt(r*r-(y-i)*(y-i))));
        ed = min(size, (int)ceil(x+sqrt(r*r-(y-i)*(y-i))));
        S[Ssize++].set(st, ed, i);
    }
}
int main() {
    int t, n, size;
    double x, y, r;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        Ssize = 0;
        scanf("%d %d", &size, &n);
        for(i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &x, &y, &r);
            cut2seg(x, y, r, size);
        }
        sort(S, S+Ssize, cmp);
        int res = 0, pre = 0;
        int L, R;
        for(i = 0; i <= Ssize; i++) {
            if(S[i].x != S[pre].x || i == Ssize) {
                L = S[pre].st, R = S[pre].ed;
                for(j = pre; j < i; j++) {
                    if(S[j].st <= R) {
                        if(S[j].ed >= R)
                            R = S[j].ed;
                    } else {
                        res += R-L;
                        L = S[j].st, R = S[j].ed;
                    }
                }
                res += R-L;
                pre = i;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
