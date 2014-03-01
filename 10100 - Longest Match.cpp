#include <cstdio>
#include <iostream>
#include <cstring>
#define isalpha(x) (('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z'))
#define isdigit(x) ('0' <= x && x <= '9')
using namespace std;

int main() {
    char line[1024];
    int cases = 0, i, j;
    while(gets(line)) {
        string x[1005], y[1005];
        int lx = 0, ly = 0;
        int lenx = strlen(line);
        for(i = 0; line[i]; i++) {
            if(isalpha(line[i]) || isdigit(line[i])) {
                char buf[64], *p = buf;
                *p = line[i], p++, i++;
                while(isalpha(line[i]) || isdigit(line[i])) {
                    *p = line[i], p++, i++;
                }
                *p = '\0';
                x[lx++] = buf, i--;
            }
        }
        gets(line);
        int leny = strlen(line);
        for(i = 0; line[i]; i++) {
            if(isalpha(line[i]) || isdigit(line[i])) {
                char buf[64], *p = buf;
                *p = line[i], p++, i++;
                while(isalpha(line[i]) || isdigit(line[i])) {
                    *p = line[i], p++, i++;
                }
                *p = '\0';
                y[ly++] = buf, i--;
            }
        }
        int dp[305][305] = {};
        for(i = 1; i <= lx; i++) {
            for(j = 1; j <= ly; j++) {
                if(x[i-1] == y[j-1]) {
                    dp[i][j] = dp[i-1][j-1]+1;
                } else {
                    dp[i][j] = dp[i][j-1] > dp[i-1][j] ?
                        dp[i][j-1] : dp[i-1][j];
                }
            }
        }
        printf("%2d. ", ++cases);
        if(lenx == 0 || leny == 0)  puts("Blank!");
        else
            printf("Length of longest match: %d\n", dp[lx][ly]);
    }
    return 0;
}
