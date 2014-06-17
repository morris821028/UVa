#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
struct ele {
    int nd;
    long long v;
};
struct NODE {
    int l, r;
    long long v;
    char c;
};
struct cmp {
    bool operator() (ele a, ele b) {
        return a.v > b.v;
    }
};
NODE ND[99999];
long long ans;
void dfs(int nd, int dep) {
    if(!ND[nd].l && !ND[nd].r)
        ans += dep*ND[nd].v;
    if(ND[nd].l)
        dfs(ND[nd].l, dep+1);
    if(ND[nd].r)
        dfs(ND[nd].r, dep+1);
}
int main() {
    int n, A[99999];
    int i;
    while(scanf("%d", &n) == 1) {
        priority_queue<ele, vector<ele>, cmp> pQ;
        ele l, r, e;
        for(i = 1; i <= n; i++) {
            scanf("%d", &A[i]);
            e.nd = i, e.v = A[i];
            ND[i].l = 0, ND[i].r = 0;
            ND[i].v = A[i];
            pQ.push(e);
        }
        int size = n;
        while(pQ.size() > 1) {
            l = pQ.top(), pQ.pop();
            r = pQ.top(), pQ.pop();
            size++;
            e.nd = size, e.v = l.v+r.v;
            ND[size].l = l.nd;
            ND[size].r = r.nd;
            ND[size].v = l.v+r.v;
            pQ.push(e);
        }
        ans = 0;
        dfs(size, 0);
        printf("%lld\n", ans);
    }
    return 0;
}
