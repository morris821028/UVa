#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
struct ND {
    int totm;
    vector<int> son;
};
ND T[10001];
long long ans = 0;
int used[10001];
int sol(int nd) {
    used[nd] = 1;
    int cnt = 0;
    for(vector<int>::iterator it = T[nd].son.begin();
        it != T[nd].son.end(); it++) {
        if(used[*it] == 0) {
            cnt += sol(*it);
            T[nd].totm += T[*it].totm;
        }
    }
    ans += abs(T[nd].totm-cnt-1);
    return cnt+1;
}
int main() {
    int n, v, m, s, x;
    int i, j;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 1; i <= n; i++)
            T[i].son.clear(), used[i] = 0;
        for(i = 1; i <= n; i++) {
            scanf("%d %d %d", &v, &m, &s);
            T[v].totm = m;
            while(s--) {
                scanf("%d", &x);
                T[v].son.push_back(x);
                T[x].son.push_back(v);
            }
        }
        ans = 0;
        sol(1);
        printf("%lld\n", ans);
    }
    return 0;
}
