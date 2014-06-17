#include <stdio.h>

int n, m, V[1000];
int judge(int c) {
    int cap = 0, cnt = 0;
    int i = 0;
    for(i = 0; i < n; i++) {
        if(V[i] > c)
            return 1000000;
        if(cap < V[i])
            cap = c, cnt++;
        cap -= V[i];
    }
    return cnt;
}
int main() {
    int i;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < n; i++)
            scanf("%d", &V[i]);
        int left = 1, right = 1000000*n, mid;
        int r;
        while(left < right) {
            mid = (left + right) >> 1;
            r = judge(mid);
            if(r > m)
                left = mid+1;
            else
                right = mid;
        }
        printf("%d\n", left);
    }
    return 0;
}
