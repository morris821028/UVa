#include <stdio.h>
#include <string.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

int main() {
    int t;
    char str[1001];
    short DP[1001][1001];
    scanf("%d", &t);
    getchar();
    while(t--) {
        gets(str);
        memset(DP, 0, sizeof(DP));
        int len = strlen(str), i, j;
        for(i = 0; i < len; i++) {
            for(j = 0; j + i < len; j++) {
                if(str[j] == str[i+j]) {
                    DP[j][j+i] = DP[j+1][j+i-1] + (i == 0 ? 1 : 2);
                } else {
                    DP[j][j+i] = max(DP[j+1][j+i], DP[j][j+i-1]);
                }
            }
        }
        printf("%d\n", DP[0][len-1]);
    }
    return 0;
}
