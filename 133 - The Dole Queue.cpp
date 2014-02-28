#include <stdio.h>

int main() {
    int i, n, k, m;
    int next[30], pre[30];
    while(scanf("%d %d %d", &n, &k, &m) == 3) {
        if(n == 0 && k == 0 && m == 0)
            break;
        for(i = 1; i <= n; i++)
            next[i] = i+1, pre[i] = i-1;
        next[n] = 1, pre[1] = n;
        int idx1 = 1, idx2 = n, used[30] = {};
        int flag = 0;
        while(n) {
            for(i = 1; i < k; i++)
                idx1 = next[idx1];
            for(i = 1; i < m; i++)
                idx2 = pre[idx2];
            if(flag)
                putchar(',');
            flag = 1;
            if(idx1 != idx2) {
                printf("%3d%3d", idx1, idx2);
                used[idx1] = used[idx2] = 1;
                n -= 2;
                next[pre[idx1]] = next[idx1];
                pre[next[idx1]] = pre[idx1];
                next[pre[idx2]] = next[idx2];
                pre[next[idx2]] = pre[idx2];
            } else {
                used[idx1] = 1;
                printf("%3d", idx1);
                next[pre[idx1]] = next[idx1];
                pre[next[idx1]] = pre[idx1];
                n--;
            }
            if(n == 0)
                break;
            while(used[idx1])
                idx1 = next[idx1];
            while(used[idx2])
                idx2 = pre[idx2];
        }
        puts("");
    }
    return 0;
}
