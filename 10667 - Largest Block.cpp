#include <stdio.h>

int main() {
    int p, s, b;
    int r1, r2, c1, c2, i, j, k;
    scanf("%d", &p);
    while(p--) {
        scanf("%d %d", &s, &b);
        char map[101][101] = {};
        while(b--) {
            scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
            for(i = r1; i <= r2; i++)
                for(j = c1; j <= c2; j++)
                    map[i][j] = 1;
        }
        int length, width, tmp = 0, ans = 0;
        for(i = 1; i <= s; i++) {
            int sum[101] = {};
            for(j = i; j <= s; j++) {
                for(k = 1; k <= s; k++) {
                    sum[k] += !map[j][k];
                    if(k == 1 || tmp != length*width)
                        tmp = 0, length = 0;
                    tmp += sum[k];
                    length++, width = j-i+1;
                    if(tmp == length*width) {
                        if(tmp > ans)
                            ans = tmp;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
