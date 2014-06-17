#include <stdio.h>
#include <vector>
using namespace std;
int main() {
    int t, n, m;
    int i, x;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int day[n+1], indeg[1001] = {};
        vector<int> g[n+1], b[n+1];
        for(i = 1; i <= n; i++) {
            scanf("%d %d", &day[i], &m);
            while(m--) {
                scanf("%d", &x);
                indeg[x]++;
                g[i].push_back(x);
                b[x].push_back(i);
            }
        }
        int ac[1001] = {}, used[1001] = {}, flag = 1;
        do {
            flag = 0;
            for(i = 1; i <= n; i++) {
                if(indeg[i] <= 0 && used[i] == 0) {
                    used[i] = 1;
                    for(vector<int>::iterator it = b[i].begin();
                        it != b[i].end(); it++) {
                            ac[i] = ac[i] > ac[*it] ? ac[i] : ac[*it];
                    }
                    ac[i] += day[i];
                    for(vector<int>::iterator it = g[i].begin();
                        it != g[i].end(); it++) {
                            indeg[*it]--;
                    }
                    flag = 1;
                }
            }
        } while(flag);
        int ans = 0;
        for(i = 1; i <= n; i++)
            ans = ans > ac[i] ? ans : ac[i];
        printf("%d\n", ans);
    }
    return 0;
}
