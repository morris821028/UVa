#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
int cut(const char s[], int len, int n) {
    map<int, int> dp[50][10] = {}; //[lengh][numbers]
    int i, j, k;
    dp[1][0][0] = 1;
    printf("%s\n", s);
    for(i = 1; i < len; i++) {
        for(j = i; j < len; j++) {
            if(s[j+1] != '0') {
                for(k = 0; k < n; k++) {

                    dp[j+1][k+1] += dp[i][k];
                }
            }
        }
    }
    for(i = 1; i < len; i++, puts(""))
        for(k = 0; k <= n; k++)
        printf("%d ", dp[i][k]);
    printf("%d\n", dp[len][n]);
}
int main() {
    int t;
    char s[50];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int num = s[0]-'0';
        cut(s, strlen(s), num);
    }
    return 0;
}
