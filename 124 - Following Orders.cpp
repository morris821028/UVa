#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;

int can[26], map[26][26], used[26];
char str[26];
void DFS(int idx, int n) {
    if(idx == n) {
        str[idx] = '\0';
        puts(str);
        return;
    }
    int i, j;
    for(i = 0; i < 26; i++) {
        if(can[i] == 1 && used[i] == 0) {
            for(j = 0; j < 26; j++)
                if(map[i][j] == 1 && used[j] == 1)
                    return;
            used[i] = 1;
            str[idx] = i+'a';
            DFS(idx+1, n);
            used[i] = 0;
        }
    }
}
int main() {
    stringstream sin;
    string line;
    char ch1, ch2, first = 0;
    while(getline(cin, line)) {
        if(first)
            puts("");
        first = 1;
        memset(can, 0, sizeof(can));
        memset(map, 0, sizeof(map));
        memset(used, 0, sizeof(used));
        sin.clear();
        sin << line;
        while(sin >> ch1) {
            can[ch1-'a'] = 1;
        }
        int n = 0;
        for(int i = 0; i < 26; i++)
            n += can[i];
        getline(cin, line);
        sin.clear();
        sin << line;
        while(sin >> ch1 >> ch2) {
            map[ch1-'a'][ch2-'a'] = 1;
        }
        DFS(0, n);
    }
    return 0;
}
