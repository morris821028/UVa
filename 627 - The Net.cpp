#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
vector<int> g[305];
int main() {
    int n, i, j, x, y;
    char line[1024];
    while(scanf("%d", &n) == 1) {
        while(getchar() != '\n');
        for(i = 1; i <= n; i++)
            g[i].clear();
        for(i = 1; i <= n; i++) {
            gets(line);
            sscanf(line, "%d%*c", &x);
            j = 0;
            while(line[j] >= '0' && line[j] <= '9') j++;
            j++;
            while(line[j]) {
                sscanf(line+j, "%d%*c", &y);
                g[y].push_back(x);
                while(line[j] >= '0' && line[j] <= '9') j++;
                if(!line[j])    break;
                j++;
            }
        }
        puts("-----");
        scanf("%d", &n);
        while(n--) {
            scanf("%d %d", &y, &x);
            queue<int> Q;
            int ox = x;
            int used[305] = {}, pre[305] = {};
            Q.push(x), used[x] = 1; // x->y
            while(!Q.empty()) {
                x = Q.front(), Q.pop();
                for(vector<int>::iterator it = g[x].begin();
                    it != g[x].end(); it++) {
                    if(!used[*it]) {
                        used[*it] = 1;
                        pre[*it] = x;
                        Q.push(*it);
                    }
                }
            }
            if(used[y]) {
                while(y != ox)
                    printf("%d ", y), y = pre[y];
                printf("%d\n", ox);
            } else {
                puts("connection impossible");
            }
        }

    }
    return 0;
}
