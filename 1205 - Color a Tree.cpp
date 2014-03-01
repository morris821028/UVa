#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct Arc {
    int to;
};
struct ele {
    int node, v;
};
int C[1001], TC[1001];
struct cmp {
    bool operator() (ele a, ele b) {
        if(a.v != b.v)
            return a.v < b.v;
        return C[a.node] < C[b.node];
    }
};
vector<Arc> myLink[1001];
void dfs(int node) {
    for(vector<Arc>::iterator i = myLink[node].begin(); i != myLink[node].end(); i++) {
        dfs(i->to);
        TC[node] += TC[i->to];
    }
}
int main() {
    int N, R, i, from, to;
    while(scanf("%d %d", &N, &R) == 2) {
        if(N == 0 && R == 0)
            break;
        for(i = 1; i <= N; i++) {
            scanf("%d", C+i);
            TC[i] = C[i];
            myLink[i].clear();
        }
        Arc tmp;
        for(i = 1; i < N; i++) {
            scanf("%d %d", &from, &to);
            tmp.to = to;
            myLink[from].push_back(tmp);
        }
        dfs(R);
        priority_queue<ele, vector<ele>, cmp> Q;
        ele tn;
        tn.node = R, tn.v = TC[R];
        Q.push(tn);
        int ans = 0, F = 1, node;
        while(!Q.empty()) {
            tn = Q.top();
            Q.pop();
            ans += F*C[tn.node];
            node = tn.node;
            printf("%d %d %d\n", node, tn.v, F*C[node]);
            for(vector<Arc>::iterator i = myLink[node].begin(); i != myLink[node].end(); i++) {
                tn.v = TC[i->to];
                tn.node = i->to;
                Q.push(tn);
            }
            F++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
