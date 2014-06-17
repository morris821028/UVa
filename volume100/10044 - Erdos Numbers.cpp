#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

char s[100005];
int main() {
    int t, cases = 0;
    int n, m, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        while(getchar() != '\n');
        map<string, int> name;
        map<string, int>::iterator it;
        vector<short> g[5005];
        int buf[5005];
        name["Erdos, P."] = 0;
        int name_size = 0;
        while(n--) {
            gets(s);
            int pre_idx = 0, bidx = 0;
            for(i = 1; s[i]; i++) {
                if((s[i] == ',' || s[i] == ':') && s[i-1] == '.') {
                    char tmp = s[i];
                    s[i] = '\0';
                    it = name.find(s+pre_idx);
                    if(it == name.end()) {
                        name[s+pre_idx] = ++name_size;
                        buf[bidx++] = name_size;
                    } else {
                        buf[bidx++] = it->second;
                    }
                    s[i] = tmp;
                    pre_idx = i+2;
                    if(s[i] == ':')
                        break;
                }
            }
            for(i = 0; i < bidx; i++) {
                for(j = i+1; j < bidx; j++) {
                    g[buf[i]].push_back(buf[j]);
                    g[buf[j]].push_back(buf[i]);
                }
            }
        }
        int used[5005] = {}, dp[5005] = {}, x;
        used[0] = 1, dp[0] = 0;
        queue<int> Q;
        Q.push(0);
        while(!Q.empty()) {
            x = Q.front(), Q.pop();
            for(vector<short>::iterator it = g[x].begin();
                it != g[x].end(); it++) {
                if(used[*it] == 0) {
                    dp[*it] = dp[x]+1;
                    used[*it] = 1;
                    Q.push(*it);
                }
            }
        }
        printf("Scenario %d\n", ++cases);
        while(m--) {
            gets(s);
            it = name.find(s);
            printf("%s ", s);
            if(it == name.end())
                puts("infinity");
            else if(!used[it->second])
                puts("infinity");
            else
                printf("%d\n", dp[it->second]);        }
    }
    return 0;
}
