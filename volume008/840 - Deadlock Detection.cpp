#include <stdio.h>
#include <vector>
#include <iostream>
#include <set>
using namespace std;
vector<int> g[60];
int used[60], path[120];
set<string> ansbuf[150];
void save(int dep) {
    int i, j, buf[60], flag;
    for(i = 0; i <= dep; i++)
        buf[i] = path[i];
    for(i = dep+1, j = 1; j <= dep; j++, i++)
        path[i] = path[j];
    for(i = 1; i <= dep; i++) {
        flag = 0;
        for(j = 0; j <= dep; j++) {
            if(path[i+j] < buf[j]) {
                flag = 1;
                break;
            }
            if(path[i+j] > buf[j]) {
                flag = -1;
                break;
            }
        }
        if(flag == 1) {
            for(j = 0; j <= dep; j++)
                buf[j] = path[i+j];
        }
    }
    string ans = "";
    for(j = 0; j <= dep; j++) {
        if(j)   ans += "-";
        if(buf[j] >= 26)
            ans = ans + (char)(buf[j]-26+'a');
        else
            ans = ans + (char)(buf[j]+'A');
    }
    ansbuf[ans.length()].insert(ans);
}
void dfs(int idx, int st, int dep) {
    used[idx] = 1;
    int i;
    for(i = 0; i < g[idx].size(); i++) {
        if(g[idx][i] == st) {
            path[dep+1] = g[idx][i];
            save(dep+1);
        }
        if(used[g[idx][i]] == 0) {
            path[dep+1] = g[idx][i];
            dfs(g[idx][i], st, dep+1);
        }
    }
    used[idx] = 0;
}
int main() {
    int t, n, m, e;
    int i, j, k;
    char s[100], x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &e);
        for(i = 0; i < 52; i++)
            g[i].clear();
        while(e--) {
            scanf("%s", s);
            sscanf(s, "%c-%c", &x, &y);
            if(x >= 'a')    x = x-'a'+26;
            else            x = x-'A';
            if(y >= 'a')    y = y-'a'+26;
            else            y = y-'A';
            g[x].push_back(y);
        }
        for(i = 0; i < 52; i++) {
            path[0] = i;
            dfs(i, i, 0);
        }
        int flag = 0;
        for(i = 0; i < 150; i++)
            if(ansbuf[i].size())
                flag = 1;
        if(flag == 0) {
            puts("NO");
        } else {
            puts("YES");
            for(i = 0; i < 150; i++) {
                for(set<string>::iterator it = ansbuf[i].begin();
                    it != ansbuf[i].end(); it++)
                    cout << *it << endl;
                ansbuf[i].clear();
            }
        }
        if(t)
            puts("");
    }
    return 0;
}
