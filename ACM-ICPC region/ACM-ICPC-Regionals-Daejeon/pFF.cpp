#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
using namespace std;
map<char, string> r;
int k, sL, letL, flag;
string s, let;
void dfs(int i, int j) {
    if(i == sL && j == letL) {
        flag = 1;
        return;
    }
    if(i > sL || j > letL)
        return;
    if(flag)    return;
    if(r[s[i]] != "") {
        string tmp = r[s[i]];
        int len = tmp.length(), h;
        for(h = 0; h < len; h++) {
            if(let[j+h] != tmp[h])
                return;
        }
        dfs(i+1, j+len);
    } else {
        int h;
        for(h = 1; h <= k; h++) {
            r[s[i]] = let.substr(j, h);
            dfs(i+1, j+h);
        }
        r[s[i]] = "";
    }
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &k);
        cin >> s >> let;
        flag = 0;
        sL = s.length(), letL = let.length();
        r.clear();
        dfs(0,0);
        printf("%d\n", flag);
    }
    return 0;
}
