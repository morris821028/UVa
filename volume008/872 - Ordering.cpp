#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;

string s;
int g[26][26], n, has;
char ans[26], used[26] = {};
void dfs(int Idx) {
    if(Idx == n) {
        has = 1;
        putchar(ans[0]);
        int i;
        for(i = 1; i < n; i++)
            printf(" %c", ans[i]);
        puts("");
        return ;
    }
    int i, j;
    for(i = 0; i < n; i++) {
        if(!used[i]) {
            for(j = 0; j < Idx; j++) {
                if(g[s[i]-'A'][ans[j]-'A'])
                    break;
            }
            if(j == Idx) {
                ans[Idx] = s[i];
                used[i] = 1;
                dfs(Idx+1);
                used[i] = 0;
            }
        }
    }
}
int main() {
    int t;
    scanf("%d", &t);
    getchar();
    string line;
    while(t--) {
        getchar();
        getline(cin, line);
        stringstream sin;
        sin << line;
        s = "";
        while(sin >> line)  s += line;
        sort(s.begin(), s.end());
        getline(cin, line);
        memset(g, 0, sizeof(g));
        sin.clear();
        sin << line;
        while(sin >> line) {
            g[line[0]-'A'][line[2]-'A'] = 1;
        }
        n = s.length();
        has = 0;
        dfs(0);
        if(!has)
            puts("NO");
        if(t)
            puts("");
    }
    return 0;
}
