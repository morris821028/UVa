#include <stdio.h>
#include <queue>
#include <functional>
#include <vector>
using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int> > pQ;
    vector<int> g[105];
    int t, M, N, indeg[105];
    int i, j, x, y, z;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &N, &M);
        for(i = 0; i <= N; i++)
            g[i].clear(), indeg[i] = 0;
        while(M--) {
            scanf("%d %d", &x, &z);
            while(z--) {
                scanf("%d", &y);
                g[y].push_back(x);
                indeg[x]++;
            }
        }
        for(i = 1; i <= N; i++)
            if(indeg[i] == 0)
                pQ.push(i);
        int tn, flag = 0;
        while(!pQ.empty()) {
            if(flag)    putchar(' ');
            flag = 1;
            tn = pQ.top(), pQ.pop();
            printf("%d", tn);
            for(vector<int>::iterator it = g[tn].begin();
                it != g[tn].end(); it++)
                if(--indeg[*it] == 0)
                    pQ.push(*it);
        }
        puts("");
        if(t)
            puts("");
    }
    return 0;
}
