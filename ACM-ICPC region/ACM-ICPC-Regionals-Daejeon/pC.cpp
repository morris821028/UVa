#include <stdio.h>
#include <string.h>
#include <algorithm>
#define L 5005
using namespace std;
char a[L], b[L];
int la, lb;
int dp[L][L], ta[L][26], tb[L][26];
int isEnd(int pa, int pb, char ch) {
    ch -= 'A';
    if(ta[pa][ch]+tb[pb][ch] == ta[la-1][ch]+tb[lb-1][ch])
        return pa+pb;
    return 0;
}
int isBegin(int pa, int pb, char ch) {
    ch -= 'A';
    if(ta[pa][ch] + tb[pb][ch] == 1)
        return pa+pb;
    return 0;
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    getchar();
    while(t--) {
        a[0] = b[0] = ' ';
        gets(a+1);
        gets(b+1);
        la = strlen(a);
        lb = strlen(b);
        for(i = 0; i < 26; i++)
            ta[0][i] = tb[0][i] = 0;
        for(i = 1; i < la; i++) {
            for(j = 0; j < 26; j++)
                ta[i][j] = ta[i-1][j];
            ta[i][a[i]-'A']++;
        }
        for(i = 1; i < lb; i++) {
            for(j = 0; j < 26; j++)
                tb[i][j] = tb[i-1][j];
            tb[i][b[i]-'A']++;
        }
        for(i = 0; i < la; i++)
            for(j = 0; j < lb; j++)
                dp[i][j] = 1<<30;
        dp[0][0] = 0;
        for(i = 0; i < la; i++) {
            for(j = 0; j < lb; j++) {
                dp[i+1][j] = min(dp[i+1][j], dp[i][j]+isEnd(i+1, j, a[i+1])-isBegin(i+1, j, a[i+1]));
                dp[i][j+1] = min(dp[i][j+1], dp[i][j]+isEnd(i, j+1, b[j+1])-isBegin(i, j+1, b[j+1]));
            }
        }
        printf("%d\n", dp[la-1][lb-1]);
    }
    return 0;
}
