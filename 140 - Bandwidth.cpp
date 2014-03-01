#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int map[26][26] = {};
int app[26] = {}, n;
int set[26] = {}, tmp[26];
int way[26] = {}, used[26] = {};
int ans;
int dfs(int idx) {
    if(idx == n) {
        int i, j;
        int bandwidth = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < 26; j++) {
                if(map[app[i]][j]) {
                    if(abs(set[app[i]] - set[j]) > bandwidth)
                        bandwidth = abs(set[app[i]] - set[j]);
                }
            }
        }
        if(bandwidth < ans) {
            ans = bandwidth;
            memcpy(way, tmp, sizeof(way));
        }
        return 0;
    }
    int i;
    for(i = 0; i < n; i++) {
        if(used[i] == 0) {
            used[i] = 1;
            tmp[idx] = app[i];
            set[app[i]] = idx;
            dfs(idx+1);
            used[i] = 0;
        }
    }
}
int main() {
    char s[100];
    int i, j, st, ed;
    while(scanf("%s", s) == 1) {
        if(!strcmp(s, "#"))
            break;
        memset(map, 0, sizeof(map));
        int len = strlen(s), used[26] = {};
        n = 0;
        for(i = 0; i < len; i++) {
            st = s[i]-'A';
            if(used[st] == 0) {
                used[st] = 1;
                app[n++] = st;
            }
            j = i+2;
            while(s[j] != ';' && s[j] != '\0') {
                ed = s[j]-'A';
                map[st][ed] = 1;
                if(used[ed] == 0) {
                    used[ed] = 1;
                    app[n++] = ed;
                }
                j++;
            }
            i = j;
        }
        std::sort(app, app+n);
        ans = 0xffff;
        dfs(0);
        for(i = 0; i < n; i++)
            printf("%c ", way[i]+'A');
        printf("-> %d\n", ans);
    }
    return 0;
}
