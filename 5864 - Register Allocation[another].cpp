#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
struct var {
    int s, f;
};
struct cmp2 {
    bool operator() (int x, int y) {
        return x - y > 0;
    }
};
bool cmp(var i, var j) {
    if(i.s != j.s)
        return i.s - j.s < 0;
    return i.f - j.f < 0;
}
int main() {
    int t, n, i;
    var V[10000];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &V[i].s, &V[i].f);
        }
        sort(V, V+n, cmp);
        priority_queue<int, vector<int>, cmp2> pQ;
        int ans = 0, end;
        for(i = 0; i < n; i++) {
            while(!pQ.empty()) {
                end = pQ.top();
                if(end < V[i].s) {
                    pQ.pop();
                } else {
                    break;
                }
            }
            pQ.push(V[i].f);
            if(pQ.size() > ans)
                ans = pQ.size();
        }
        printf("%d\n", ans);
    }
    return 0;
}
