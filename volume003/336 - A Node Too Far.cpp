#include <stdio.h>
#include <map>
#include <vector>
#include <queue>
using namespace std;
int main() {
    int n, test = 0, TTL;
    while(scanf("%d", &n) == 1 && n) {
        int i, j, size = 0, x, y;
        map<int, int> r;
        vector<int> Link[40];
        while(n--) {
            scanf("%d %d", &i, &j);
            x = r[i];
            if(x == 0) {
                r[i] = ++size;
                x = size;
            }
            y = r[j];
            if(y == 0) {
                r[j] = ++size;
                y = size;
            }
            Link[x].push_back(y);
            Link[y].push_back(x);
        }
        while(scanf("%d %d", &x, &TTL) == 2) {
            if(x == 0 && TTL == 0)
                break;
            int used[40] = {}, dp[40] = {}, cnt = 0;
            y = x, x = r[x];
            queue<int> Q;
            Q.push(x), used[x] = 1, dp[x] = 0;
            while(!Q.empty()) {
                x = Q.front();
                if(dp[x] > TTL)
                    break;
                cnt++;
                Q.pop();
                for(vector<int>::iterator i = Link[x].begin(); i != Link[x].end(); i++) {
                    if(used[*i] == 0) {
                        used[*i] = 1;
                        dp[*i] = dp[x]+1;
                        Q.push(*i);
                    }
                }
            }
            printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n", ++test, size-cnt, y, TTL);
        }
    }
    return 0;
}
