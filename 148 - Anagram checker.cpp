#include <stdio.h>
#include <string.h>
#include <sstream>
#include <set>
using namespace std;
char dictionary[2001][101], test[101];
int dIdx = 0, letter[128], len, i, ans[2001];
set<string> word;
void dfs(int idx, int i) {
    if(len == 0) {
        printf("%s =", test);
        for(i = 0; i < idx; i++) {
            printf(" %s", dictionary[ans[i]]);
        }
        puts("");
        return ;
    }
    int j;
    for(; i < dIdx; i++) {
        if(word.find(dictionary[i]) != word.end())
            continue;
        int flag = 0;
        for(j = 0; dictionary[i][j]; j++) {
            letter[dictionary[i][j]]--;
            len--;
            if(letter[dictionary[i][j]] < 0) {
                while(j >= 0) {
                    letter[dictionary[i][j]]++;
                    len++;
                    j--;
                }
                flag = 1;
                break;
            }
        }
        if(!flag) {
            ans[idx] = i;
            dfs(idx+1, i+1);
            for(j = 0; dictionary[i][j]; j++) {
                letter[dictionary[i][j]]++;
                len++;
            }
        }
    }
}
int main() {
    while(gets(dictionary[dIdx])) {
        if(dictionary[dIdx][0] == '#')
            break;
        dIdx++;
    }
    while(gets(test)) {
        if(!strcmp(test, "#"))
            break;
        stringstream sin;
        sin << test;
        string in;
        word.clear();
        while(sin >> in) {
            word.insert(in);
        }
        memset(letter, 0, sizeof(letter));
        len = 0;
        for(i = 0; test[i]; i++) {
            if(test[i] == ' ') {
                continue;
            }
            letter[test[i]]++;
            len++;
        }
        dfs(0, 0);
    }
    return 0;
}
