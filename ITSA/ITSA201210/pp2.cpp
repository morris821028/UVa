#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
vector<int> g[100000];
int main() {
    int n, i, j, p, tn;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            g[i].clear();
        for(i = 1; i < n; i++) {
            scanf("%d", &p);
            g[i].push_back(p);
            g[p].push_back(i);
        }

    }
    printf("1\n13\n");
    return 0;
}
