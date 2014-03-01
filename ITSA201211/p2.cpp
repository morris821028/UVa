#include <stdio.h>
#include <vector>
using namespace std;
vector<int> g[100005];
long long A[100005], ans;
long long dfs(int nd) {
    long long sum = 0, tmp;
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        tmp = dfs(*it);
        if(nd == 0 && tmp > ans)
            ans = tmp;
        sum += tmp;
    }
    sum += A[nd];
    return sum;
}
int main() {
    int n, i, p;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%lld", &A[i]);
    for(i = 1; i < n; i++) {
        scanf("%d", &p);
        g[p].push_back(i);
    }
    ans = 0;
    dfs(0);
    printf("%lld\n", ans);
    return 0;
}
