#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int main() {
    int n, m, a, b;
    while(scanf("%d %d", &n, &m) == 2) {
        vector<int> g[n+1];
        while(m--) {
            scanf("%d %d", &a, &b);
            g[a].push_back(b);
        }
        scanf("%d %d", &a, &b);
        int used[1000] = {}, tn;
        queue<int> q;
        q.push(a);
        while(!q.empty()) {
            tn = q.front();
            q.pop();
            for(vector<int>::iterator i = g[tn].begin(); i != g[tn].end(); i++) {
                if(used[*i] == 0) {
                    q.push(*i);
                    used[*i] = 1;
                }
            }
            if(used[b])
                break;
        }
        if(used[b] == 1)
            puts("Yes!!!");
        else
            puts("No!!!");
    }
    return 0;
}
