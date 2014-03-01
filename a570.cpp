#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
struct seg {
    int s, e, v;
};
struct cmp1 {
    bool operator() (seg a, seg b) {
        return a.s > b.s;
    }
};
struct cmp2 {
    bool operator() (seg a, seg b) {
        return a.e > b.e;
    }
};
int main() {
    int n, i, S, E, v;
    while(scanf("%d", &n) == 1) {
        priority_queue<seg, vector<seg>, cmp1> pQ1;
        priority_queue<seg, vector<seg>, cmp2> pQ2;
        seg e;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d", &S, &E, &v);
            e.s = S, e.e = E, e.v = v;
            pQ1.push(e);
        }
        int pred = 0;
        for(i = 0; i < n; i++) {
            while(!pQ2.empty() && pQ2.top().e <= pQ1.top().s) {
                pred = max(pred, pQ2.top().v);
                pQ2.pop();
            }
            e = pQ1.top();
            pQ1.pop();
            e.v += pred;
            pQ2.push(e);
        }
        while(!pQ2.empty() && pQ2.top().e) {
            pred = max(pred, pQ2.top().v);
            pQ2.pop();
        }
        printf("%d\n", pred);
    }
    return 0;
}
/*
4
1 3 5
2 5 6
4 7 3
6 9 4
2
1 2 3
2 3 6
*/
