#include <stdio.h>
#include <limits.h>
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int ax, ay, av;
    av = INT_MIN;
    for (int i = 0; i < n; i++) {
        int pc, qc, pv, qv;
        int x;
        pv = qv = INT_MIN;
        for (int j = 0; j < m; j++) {
            scanf("%d", &x);
            if (x >= pv) {
                qv = pv, qc = pc;
                pv = x, pc = j;
            } else if (x >= qv) {
                qv = x, qc = j;
            }
        }
        printf("%d %d\n", pc+1, qc+1);
        if (pv >= av)
            av = pv, ax = i, ay = pc;
    }
    printf("%d %d\n", ax+1, ay+1);
    return 0;
}

