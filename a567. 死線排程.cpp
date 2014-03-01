#include <stdio.h>
#include <algorithm>
using namespace std;
struct task {
    int d, p;
};
bool cmp(task a, task b) {
    return a.p > b.p;
}
int p[10005], r[10005], inter[10005];
void init(int n) {
    for(int i = 0; i <= n; i++)
        p[i] = i, r[i] = 1, inter[i] = i;
}
int findp(int x) {
    return p[x] == x ? x : (p[x]=findp(p[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x != y) {
        if(r[x] > r[y]) {
            p[y] = x, r[x] += r[y];
            inter[x] = min(inter[x], inter[y]);
        } else {
            p[x] = y, r[y] += r[x];
            inter[y] = min(inter[x], inter[y]);
        }
        return 1;
    }
    return 0;
}
int main() {
    int n, i, x, y;
    int sche[10005];
    while(scanf("%d", &n) == 1) {
        task A[10005];
        int day = 1, ans = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &A[i].d, &A[i].p);
            day = max(day, A[i].d);
        }
        day++;
        for(i = 1; i <= day; i++)
            sche[i] = 0;
        sort(A, A+n, cmp);
        init(day);
        for(i = 0; i < n; i++) {
            if(sche[A[i].d] == 0) {
                x = y = A[i].d;
                if(sche[x+1])
                    x++;
            } else {
                x = findp(A[i].d);
                y = inter[x]-1;
                if(!y)  continue;
            }
            sche[y] = i+1;
            ans += A[i].p;
            joint(x, y);
            if(y-1 > 0 && sche[y-1])
                joint(y-1, y);
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
6
2 5
3 6
4 4
4 2
5 3
5 1
8
7 1
7 1
7 1
10 1
11 1
9 1
10 1
11 1
*/
