#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n, x;
    long long m;
    while (scanf("%d %lld", &n, &m) == 2) {
        int f[2048], a[2048];
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            f[i] = x;
        }
        
        int visited[2048] = {};
        for (int i = 1; i <= n; i++) {
            if (visited[i]) continue;
            vector<int> cycle;
            for (int j = i; !visited[j]; j = f[j]) {
                visited[j] = 1;
                cycle.push_back(j);
            }
            for (int j = 0; j < cycle.size(); j++) {
                int v = cycle[j];
                a[v] = cycle[(j + m%cycle.size())%cycle.size()];
            }
        }
        for (int i = 1; i <= n; i++) {
            printf("%d%c", a[i], i == n ? '\n' : ' ');
        }
    }
    return 0;
}
/*
 5 0
 4 2 1 5 3
 5 1
 4 2 1 5 3
 5 2
 4 2 1 5 3
 */