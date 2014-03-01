#include <stdio.h>

int main() {
    int testcase;
    int n, m, i, j, k;
    int x, v;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        int A[105];
        for(i = 0; i < m; i++) {
            v = 0;
            for(j = 0; j < n; j++) {
                scanf("%d", &x);
                v |= (1&x)<<j;
            }
            A[i] = v;
        }
        int ret = 0xffff, rr = 1<<n;
        int mark[32768] = {};
        for(i = 0; i < rr; i++) {
            int flag = 0;
            x = 0;
            for(j = 0; j < n; j++)
                x += (i>>j)&1;
            if(x >= ret)    continue;
            for(j = 0; j < m && !flag; j++) {
                v = A[j]&i;
                if(mark[v]) {
                    while(j >= 0) {
                        v = A[j]&i;
                        mark[v] = 0;
                        j--;
                    }
                    flag = 1;
                    break;
                }
                mark[v] = 1;
            }
            if(flag == 0) {
                x = 0;
                for(j = 0; j < n; j++)
                    x += (i>>j)&1;
                if(x < ret)
                    ret = x;
                for(j = 0; j < m; j++) {
                    v = A[j]&i;
                    mark[v] = 0;
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
