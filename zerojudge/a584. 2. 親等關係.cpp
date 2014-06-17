#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#define tran(i) (s[i]-'A'+(s[i]-'A')*26+(s[i]-'A')*676)
using namespace std;
vector<int> g[20000];
int used[20000] = {};
int main() {
    int n, i, j, x, y;
    char s[1000];
    scanf("%d ", &n);
    while(n--) {
        gets(s), j = strlen(s);
        x = tran(0);
        for(i = 4; i < j; i += 4) {
            y = tran(i);
            g[x].push_back(y), g[y].push_back(x);
        }
    }
    scanf("%s", s), x = tran(0);
    scanf("%s", s), y = tran(0);
    queue<int> Q;
    Q.push(x);
    used[x] = 1;
    while(!Q.empty()) {
        x = Q.front(), Q.pop();
        for(i = 0; i < g[x].size(); i++)
            if(!used[g[x][i]])
                used[g[x][i]] = used[x]+1, Q.push(g[x][i]);
    }
    printf("%d\n", used[y]-1);
    return 0;
}
