#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
vector<int> g[1005];
int vfind[1005], findIdx;
int stk[1005], stkIdx;
int in_stk[1005], visited[1005];
int contract[1005];
int scc_cnt;
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    for(int i = 0; i < g[nd].size(); i++) {
        if(!visited[g[nd][i]])
            mn = min(mn, scc(g[nd][i]));
        if(in_stk[g[nd][i]])
            mn = min(mn, vfind[g[nd][i]]);
    }
    if(mn == vfind[nd]) {
        do {
            in_stk[stk[stkIdx]] = 0;
            contract[stk[stkIdx]] = nd;
        } while(stk[stkIdx--] != nd);
        scc_cnt++;
    }
    return mn;
}
int main() {
    int testcase, S, A, m, i, j;
    int s1, s2, a1, a2;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &S, &A, &m);
        int n = (S+A)*2;
        for(i = 0; i < n; i++)
            g[i].clear();
        // 2*node: false, 2*node+1: true
        while(m--) {
            scanf("%d %d %d %d", &s1, &a1, &s2, &a2);
            s1--, a1--, s2--, a2--;
            s1 <<= 1, a1 <<= 1;
            s2 <<= 1, a2 <<= 1;
            a1 += 2*S, a2 += 2*S;
            if(a1 > a2) s1 ^= 1, s2 ^= 1;
            if(s1 > s2) a1 ^= 1, a2 ^= 1;
            if(s1 == s2) {
                g[s1^1].push_back(s2);
                continue;
            }
            if(a1 == a2) {
                g[a1^1].push_back(a2);
                continue;
            }
            //(s1,a1)->(s2,a2)
            //transform: (s1 and a2) or (s2 and a1)
            //to 2-SAT model: (s1 or a1) and (s2 or a2) and (a1 or a2) and (s1 or s2)
            g[s1^1].push_back(a1);
            g[a1^1].push_back(s1);

            g[s2^1].push_back(a2);
            g[a2^1].push_back(s2);

            g[a1^1].push_back(a2);
            g[a2^1].push_back(a1);

            g[s2^1].push_back(s1);
            g[s1^1].push_back(s2);
        }
        //SCC
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        scc_cnt = 1;
        for(i = 0; i < n; i++) {
            if(!visited[i]) {
                stkIdx = 0;
                findIdx = 0;
                scc(i);
            }
        }
        //2-SAT check
        int hasSol = 1;
        for(i = 0; i < n && hasSol; i+=2)
            if(contract[i] == contract[i^1])
                hasSol = 0;
        puts(hasSol ? "Yes" : "No");
    }
    return 0;
}
