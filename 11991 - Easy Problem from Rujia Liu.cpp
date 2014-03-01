#include <stdio.h>
#include <vector>
using namespace std;
vector<int> ar[1000001];

int main() {
    int n, m, i, x, k, v;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            ar[x].push_back(i+1);
        }
        while(m--) {
            scanf("%d %d", &k, &v);
            if(k > ar[v].size())
                puts("0");
            else
                printf("%d\n", ar[v][k-1]);
        }
        for(i = 0; i <= 1000000; i++)
            ar[i].clear();
    }
    return 0;
}
