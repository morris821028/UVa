#include <stdio.h>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
char board[21][21], used[21][21] = {}, tmp[401];
set<string> ans;
int n;
void dfs(int x, int y, int idx) {
    if(idx >= 3) {
        tmp[idx] = '\0';
        ans.insert(tmp);
    }
    if(x < 0 || y < 0 || x >= n || y >= n)
        return;
    if(idx > 0 && board[x][y] <= tmp[idx-1])
        return;
    if(used[x][y])
        return;
    tmp[idx] = board[x][y];
    used[x][y] = 1;
    dfs(x+1, y, idx+1);
    dfs(x-1, y, idx+1);
    dfs(x, y+1, idx+1);
    dfs(x, y-1, idx+1);
    dfs(x-1, y-1, idx+1);
    dfs(x-1, y+1, idx+1);
    dfs(x+1, y+1, idx+1);
    dfs(x+1, y-1, idx+1);
    used[x][y] = 0;
}
bool cmp(string a, string b) {
    return a.length() < b.length();
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%s", board[i]);
        }
        ans.clear();
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                dfs(i, j, 0);
            }
        }
        string tot[50000];
        int totIdx = 0;
        for(set<string>::iterator it = ans.begin();
            it != ans.end(); it++) {
            tot[totIdx++] = *it;
        }
        stable_sort(tot, tot+totIdx, cmp);
        for(i = 0; i < totIdx; i++)
            cout << tot[i] << endl;
        if(t)
            puts("");
    }
    return 0;
}
