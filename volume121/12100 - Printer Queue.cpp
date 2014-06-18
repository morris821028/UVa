#include <stdio.h>
#include <queue>
using namespace std;
int main() {
    int t, n, m, x, i, j, v, idx;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        queue<int> Qv, Qidx;
        int inQ[10] = {};
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            Qv.push(x), Qidx.push(i);
            inQ[x]++;
        }
        int time = 0;
        while(true) {
            v = Qv.front(), Qv.pop();
            idx = Qidx.front(), Qidx.pop();

            int canPop(1);
            for(i = v+1; i < 10; i++)
                canPop &= inQ[i] == 0;
            if(canPop) {
                time++;
                if(idx == m) {
                    printf("%d\n", time);
                    break;
                }
                inQ[v]--;
            } else {
                Qv.push(v), Qidx.push(idx);
            }
        }
    }
    return 0;
}
