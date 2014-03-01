#include <stdio.h>
int A[10005], Idx[10005];
int n, i, j, idx, val, cnt;
int check() {
    int diff = n/2;
    for(i = -diff; i <= diff; i++) {
        for(j = 0; j < n; j++) {
            val = A[j], idx = j;
            cnt = 0;
            while(cnt < 2) {
                val = val+i;
                if(val < 0 || val >= n)
                    break;
                if(idx >= Idx[val])
                    break;
                idx = Idx[val];
                cnt++;
            }
            if(cnt >= 2)
                return 0;
        }
    }
    return 1;
}
int main() {
    while(scanf("%d%*c", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            Idx[A[i]] = i;
        }
        if(check())
            puts("yes");
        else
            puts("no");
    }
    return 0;
}
