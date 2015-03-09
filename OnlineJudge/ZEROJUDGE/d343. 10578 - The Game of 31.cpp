#include <stdio.h>
#include <string.h>
int C[6];
int dp[5][5][5][5][5][5], done[5][5][5][5][5][5];
int calu() {
    int tot =  4 * (6 + 5 + 4 + 3 + 2 + 1), i;
    for(i = 0; i < 6; i++)
        tot -= C[i]*(i+1);
    return tot;
}
int dfs(int a) {
    int score = calu();
    if(score > 31)  return a;
    if(done[C[0]][C[1]][C[2]][C[3]][C[4]][C[5]])
        return dp[C[0]][C[1]][C[2]][C[3]][C[4]][C[5]];
    done[C[0]][C[1]][C[2]][C[3]][C[4]][C[5]] = 1;
    int i, win = 1^a;
    for(i = 0; i < 6; i++) {
        if(C[i] > 0) {
            C[i]--;
            if(dfs(1^a) != win) {
                win = a;
                C[i]++;
                break;
            }
            C[i]++;
        }
    }
    dp[C[0]][C[1]][C[2]][C[3]][C[4]][C[5]] = win;
    return win;
}
int main() {
    char s[100];
    int i;
    memset(done, 0, sizeof(done));
    memset(dp, 0, sizeof(dp));
    while(scanf("%s", s) == 1) {
        int len = strlen(s);
        for(i = 0; i < 6; i++)
            C[i] = 4;
        for(i = 0; i < len; i++)
            C[s[i]-'1']--;
        printf("%s %c\n", s, dfs(len%2)+'A');
    }
    return 0;
}
