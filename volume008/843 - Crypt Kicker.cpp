#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <set>
using namespace std;
string word[1005];
set<string> W;
string buf[1005];
int n, m;
bool hasSol;
char mapped[128], mapped2[128];
char trans[128];
void dfs(int idx) {//decode buf[idx]
    if(hasSol)  return;
    int i, j, err;
    int exist = 1;
    if(idx == m) {
        for(i = 0; i < m; i++) {
            if(i)   putchar(' ');
            for(j = 0; j < buf[i].length(); j++)
                putchar(mapped[buf[i][j]]);
        }
        puts("");
        hasSol = 1;
        return;
    }
    for(i = 0; i < buf[idx].length(); i++) {
        if(mapped[buf[idx][i]] == 0)
            exist = 0;
        else {
            trans[i] = mapped[buf[idx][i]];
        }
    }
    trans[i] = '\0';
    if(exist == 1) {
        if(W.find(trans) == W.end())
            return;
        dfs(idx+1);
    } else {//try new mapped function
        char ori[128], ori2[128];
        for(i = 0; i < n; i++) {
            if(buf[idx].length() != word[i].length())
                continue;
            memcpy(ori, mapped, sizeof(ori));//copy
            memcpy(ori2, mapped2, sizeof(ori2));//copy
            err = 0;
            for(j = 0; j < word[i].length(); j++) {
                if(mapped[buf[idx][j]] == 0) {
                    if(mapped2[word[i][j]])
                        err = 1;
                    mapped[buf[idx][j]] = word[i][j];
                    mapped2[word[i][j]] = buf[idx][j];
                    // new function
                } else {
                    if(mapped[buf[idx][j]] != word[i][j]) {
                        err = 1;
                        break;
                    }
                }
            }
            if(err == 0)
                dfs(idx+1);
            memcpy(mapped, ori, sizeof(ori));//recover
            memcpy(mapped2, ori2, sizeof(ori2));//recover
            if(hasSol)
                return;
        }
    }
}
int main() {
    scanf("%d", &n);
    int i, j;
    string line;
    char s[128];
    for(i = 0; i < n; i++) {
        scanf("%s", s);
        word[i] = s;
        W.insert(s);
    }
    while(getchar() != '\n');
    while(getline(cin, line)) {
        stringstream sin(line);
        m = 0;
        while(sin >> line)
            buf[m++] = line;
        memset(mapped, 0, sizeof(mapped));
        memset(mapped2, 0, sizeof(mapped2));
        hasSol = false;
        dfs(0);
        if(!hasSol) {
            for(i = 0; i < m; i++) {
                if(i)   putchar(' ');
                for(j = buf[i].length()-1; j >= 0; j--)
                    putchar('*');
            }
            puts("");
        }
    }
    return 0;
}
