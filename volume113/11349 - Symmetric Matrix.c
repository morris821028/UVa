#include <stdio.h>

int main() {
    int t, n, Case = 0;
    long long map[101][101];
    char str[3];
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s %d", str, str, &n);
        int flag = 0, i, j;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%lld", &map[i][j]);
                if(map[i][j] < 0)   flag = 1;
            }
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < n-i; j++) {
                if(map[i][j] != map[n-1-i][n-1-j]) {
                    flag = 1;
                    goto end;
                }
            }
        }
        end:
        printf("Test #%d: ", ++Case);
        if(flag)
            puts("Non-symmetric.");
        else
            puts("Symmetric.");
    }
    return 0;
}
