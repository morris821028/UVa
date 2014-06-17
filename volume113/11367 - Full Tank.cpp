#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
struct Node {
    int nd, f, mncost;
    bool operator<(const Node &A) const {
        return mncost > A.mncost;
    }
    Node(int a, int b, int c):
        nd(a), f(b), mncost(c) {}
};
struct Edge {
    int to, v;
    Edge(int a, int b):
        to(a), v(b) {}
};
vector<Edge> g[1005];
int price[1005];
int dp[1005][101];
void sol(int s, int e, int c, int n) {
    int i, j, k;
    Node tn(0,0,0);
    for(i = 0; i < n; i++)
        for(j = 0; j <= c; j++)
            dp[i][j] = 0xfffffff;
    priority_queue<Node, vector<Node> > pQ;
    dp[s][0] = 0;
    pQ.push(Node(s, 0, dp[s][0]));
    while(!pQ.empty()) {
        tn = pQ.top(), pQ.pop();
        if(tn.nd == e) {
            printf("%d\n", tn.mncost);
            return ;
        }
        // add one unit of fuel;
        if(tn.f != c) {
            if(dp[tn.nd][tn.f+1] > dp[tn.nd][tn.f] + price[tn.nd]) {
                dp[tn.nd][tn.f+1] = dp[tn.nd][tn.f] + price[tn.nd];
                pQ.push(Node(tn.nd, tn.f+1, dp[tn.nd][tn.f+1]));
            }
        }
        // goto next city
        for(vector<Edge>::iterator it = g[tn.nd].begin();
            it != g[tn.nd].end(); it++) {
            if(tn.f >= it->v) {
                if(dp[it->to][tn.f-(it->v)] > dp[tn.nd][tn.f]) {
                    dp[it->to][tn.f-(it->v)] = dp[tn.nd][tn.f];
                    pQ.push(Node(it->to, tn.f-(it->v), dp[tn.nd][tn.f]));
                }
            }
        }
    }
    puts("impossible");
}
int main() {
    int n, m, q;
    int x, y, d;
    int i, j, k;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < n; i++) {
            scanf("%d", &price[i]);
            g[i].clear();
        }
        while(m--) {
            scanf("%d %d %d", &x, &y, &d);
            g[x].push_back(Edge(y, d));
            g[y].push_back(Edge(x, d));
        }
        scanf("%d", &q);
        while(q--) {
            scanf("%d %d %d", &d, &x, &y);
            sol(x, y, d, n);
        }
    }
    return 0;
}
