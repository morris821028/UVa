#include <stdio.h>

void multiply(int a[], int b[], int c[]) {
    int i, j, k;
    for(i = 0; i < 100; i++)
        for(j = 0; j < 100; j++)
            if(i+j < 100)
                c[i+j] += a[i]*b[j];
    for(i = 0; i < 100; i++)
        if(c[i] >= 10)
            c[i+1] += c[i]/10, c[i] %= 10;
}
int compare(int a[], int b[]) {
    int i;
    for(i = 99; i >= 0; i--)
        if(a[i] > b[i])
            return 1;
        else if(a[i] < b[i])
            return 0;
    return 1;
}
void assign(int a[], int b[]) {
    int i;
    for(i = 0; i < 100; i++)
        a[i] = b[i];
}
void print(int a[]) {
    int i = 99;
    while(i >= 1 && a[i] == 0)  i--;
    while(i >= 0)   putchar(a[i]+'0'), i--;
}
int main() {
    int N, K, i, j, k, ti, tj;
    char s[50];
    scanf("%d %d", &N, &K);
    scanf("%s", s+1);
    K++;
    for(i = 1; i <= N; i++)
        s[i] -= '0';
    int dp[50][10][100] = {};
    dp[0][0][0] = 1;
    for(i = 1; i <= N; i++) {
        for(j = 0; j < K; j++) {
            for(k = i; k <= N; k++) {
                //dp[k][j+1] = dp[i-1][j]*num[i~>k];
                int tmp[100] = {}, num[100] = {};
                for(ti = 0, tj = k; tj >= i; ti++, tj--)
                    num[ti] = s[tj];
                multiply(dp[i-1][j], num, tmp); // tmp = dp[i-1][j]*num
                /*printf("[%d %d] %d\n", k, j+1, i);
                print(dp[i-1][j]);
                printf(" * "), print(num), printf(" = "), print(tmp);
                puts("\n ========== ");*/
                if(!compare(dp[k][j+1], tmp))
                    assign(dp[k][j+1], tmp);
            }
        }
    }
    print(dp[N][K]);
    puts("");
    return 0;
}
