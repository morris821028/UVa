#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#define maxN 100
using namespace std;
vector<int> g[maxN];
set<string> ans;
int vfind[maxN], findIdx;
int stk[maxN], stkIdx;
int in_stk[maxN], visited[maxN];
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(!visited[*it])
            mn = min(mn, scc(*it));
        if(in_stk[*it])
            mn = min(mn, vfind[*it]);
    }
    if(mn == vfind[nd]) {
        string tmp = "";
        do {
            tmp += (stk[stkIdx]+'A');
            in_stk[stk[stkIdx]] = 0;
        } while(stk[stkIdx--] != nd);
        sort(tmp.begin(), tmp.end());
        ans.insert(tmp);
    }
    return mn;
}
int main() {
    int n, i, j, first = 0;
    char x[4], y[5][4];
    while(scanf("%d", &n) == 1 && n) {
        int app[26] = {};
        for(i = 0; i < 26; i++) {
            g[i].clear();
            visited[i] = in_stk[i] = 0;
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < 5; j++)
                scanf("%s", y[j]);
            scanf("%s", x);
            app[x[0]-'A'] = 1;
            for(j = 0; j < 5; j++) {
                app[y[j][0]-'A'] = 1;
                if(y[j][0] != x[0]) {
                    g[y[j][0]-'A'].push_back(x[0]-'A');
                }
            }
        }
        ans.clear();
        for(i = 0; i < 26; i++) {
            if(!visited[i] && app[i]) {
                findIdx = stkIdx = 0;
                scc(i);
            }
        }
        if(first)
            puts("");
        first = 1;
        for(set<string>::iterator it = ans.begin();
            it != ans.end(); it++) {
            printf("%c", (*it)[0]);
            for(int j = 1; j < (*it).length(); j++)
                printf(" %c", (*it)[j]);
            puts("");
        }
    }
    return 0;
}
