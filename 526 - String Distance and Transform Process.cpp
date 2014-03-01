#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define maxN 100
using namespace std;
int dp[maxN][maxN], lx, ly;
int arg_dp[maxN][maxN];
char x[maxN], y[maxN];
int step, cont = 0;
void print(int i, int j) {
    if(i == 0 && j == 0)
        return;
    if(arg_dp[i][j] == -1) {
        print(i-1, j-1);
    } else if(arg_dp[i][j] == -2) {
        print(i-1, j-1);
        printf("%d Replace %d,%c\n", ++step, i-cont, y[j-1]);
    } else if(arg_dp[i][j] == -3) {
        print(i-1, j);
        printf("%d Delete %d\n", ++step, i-cont);
        cont++;
    } else if(arg_dp[i][j] == -4) {
        print(i, j-1);
        cont--;
        printf("%d Insert %d,%c\n", ++step, i-cont, y[j-1]);
    }
}
int main() {
    int i, j, first = 0;
    while(gets(x)) {
        gets(y);
        if(first)
            puts("");
        first = 1;
        lx = strlen(x), ly = strlen(y);
        for(i = 0; i <= lx; i++) {
            for(j = 0; j <= ly; j++) {
                dp[i][j] = 0xffff;
            }
        }
        dp[0][0] = 0;
        int cost[4] = {0,1,1,1};
        for(i = 0; i <= lx; i++) {
            for(j = 0; j <= ly; j++) {
                //copy
                if(x[i] == y[j]) {
                    dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+cost[0]);
                    if(dp[i+1][j+1] == dp[i][j]+cost[0])
                        arg_dp[i+1][j+1] = -1;
                }
                //replace
                if(x[i] != y[j]) {
                    dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+cost[1]);
                    if(dp[i+1][j+1] == dp[i][j]+cost[1])
                        arg_dp[i+1][j+1] = -2;
                }
                //delete
                dp[i+1][j] = min(dp[i+1][j], dp[i][j]+cost[2]);
                if(dp[i+1][j] == dp[i][j]+cost[2])
                    arg_dp[i+1][j] = -3;
                //insert
                dp[i][j+1] = min(dp[i][j+1], dp[i][j]+cost[3]);
                if(dp[i][j+1] == dp[i][j]+cost[3])
                    arg_dp[i][j+1] = -4;
            }
        }
        printf("%d\n", dp[lx][ly]);
        step = cont = 0;
        print(lx, ly);
    }
    return 0;
}
