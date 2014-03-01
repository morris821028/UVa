#include <stdio.h>

int main() {
    scanf("%*d");
    char w[2][105];
    int k, n, i, j, l;
    while(scanf("%d %d", &k, &n) == 2) {
        scanf("%s", w[0]);
        int ans = n*k, flag = 1;
        for(i= 1; i < n; i++) {
            scanf("%s", w[flag]);
            for(j = 0; j < k; j++) {
                for(l = 0; w[!flag][j+l]; l++)
                    if(w[flag][l] != w[!flag][j+l])
                        break;
                if(w[!flag][j+l] == '\0') {
                    ans -= k-j;
                    break;
                }
            }
            flag = !flag;
        }
        printf("%d\n", ans);
    }
    return 0;
}
