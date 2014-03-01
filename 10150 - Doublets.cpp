#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <iostream>
#include <map>
using namespace std;
char word[25145][17];
int n = 0;
vector<int> g[25145], bucket[17];
map<string, int> S2N[17];
int isDoublet(int x, int y, int len) {
    static int i, cnt;
    for(i = 0, cnt = 0; i < len; i++) {
        cnt += word[x][i] != word[y][i];
        if(cnt > 1)
            return 0;
    }
    return cnt == 1;
}
void build_graph() {
    int i, j, k, m, x, y;
    for(i = 1; i <= 16; i++) {
        m = bucket[i].size();
        for(j = 0; j < m; j++) {
            for(k = j+1; k < m; k++) {
                x = bucket[i][j], y = bucket[i][k];
                if(isDoublet(x, y, i)) {
                    g[x].push_back(y);
                    g[y].push_back(x);
                }
            }
        }
    }
}
int pre[25145];
void bfs(int st, int ed) {
    queue<int> Q;
    char used[25145] = {};
    Q.push(st), used[st] = 1, pre[st] = -1;
    while(!Q.empty()) {
        st = Q.front(), Q.pop();
        for(vector<int>::iterator it = g[st].begin();
            it != g[st].end(); it++) {
            if(!used[*it]) {
                used[*it] = 1;
                pre[*it] = st;
                Q.push(*it);
            }
        }
        if(used[ed])
            break;
    }
    if(!used[ed])
        puts("No solution.");
    else {
        while(ed >= 0) {
            puts(word[ed]);
            ed = pre[ed];
        }
    }
}
int main() {
    int word_len, st_len, ed_len;
    while(gets(word[n]) && word[n][0] != '\0') {
        word_len = strlen(word[n]);
        bucket[word_len].push_back(n);
        S2N[word_len][word[n]] = n;
        n++;
    }
    build_graph();
    char st[20], ed[20];
    int first = 0, x, y;
    while(scanf("%s %s", &st, &ed) == 2) {
        if(first)   puts("");
        first = 1;
        st_len = strlen(st);
        ed_len = strlen(ed);
        if(st_len != ed_len) {
            puts("No solution.");
            continue;
        }
        x = S2N[st_len][st];
        y = S2N[ed_len][ed];
        bfs(y, x);
    }
    return 0;
}
