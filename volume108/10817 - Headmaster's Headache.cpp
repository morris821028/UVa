#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;
int dp[105][6700];
int main() {
    int S, M, N, P, x, state;
    int i, j, k, cost;
    while(scanf("%d %d %d", &S, &M, &N) == 3) {
        if(S == 0)  break;
        cin.ignore(100, '\n');
        int sub[30] = {}, base = 0;
        for(i = 1; i <= S; i++)
            sub[i] = 2;
        for(i = 0; i < M; i++) {
            string line;
            getline(cin, line);
            stringstream sin(line);
            sin >> cost;
            base += cost;
            while(sin >> x) {
                if(sub[x])
                    sub[x]--;
            }
        }
        int v[105], teach[105][10], tidx[105] = {};
        for(i = 1; i <= N; i++) {
            string line;
            getline(cin, line);
            stringstream sin(line);
            sin >> v[i];
            while(sin >> x) {
                teach[i][tidx[i]++] = x;
            }
        }
        memset(dp, 63, sizeof(dp));
        P = 0;
        for(i = 1; i <= S; i++)
            P = P*3 + 2;
        int ch[30];
        for(i = 0; i <= P; i++) {
            state = i;
            for(j = S; j >= 1; j--)
                ch[j] = state%3, state /= 3;
            for(j = 1; j <= S && ch[j] >= sub[j]; j++);
            if(j == S+1)
                dp[0][i] = base;
        }
        for(i = 1; i <= N; i++) {
            for(j = 0; j <= P; j++) {
                dp[i][j] = dp[i-1][j];
                state = j;
                for(k = S; k >= 1; k--)
                    ch[k] = state%3, state /= 3;
                for(k = 0; k < tidx[i]; k++)
                    if(ch[teach[i][k]] < 2)
                        ch[teach[i][k]]++;
                state = 0;
                for(k = 1; k <= S; k++)
                    state = state*3 + ch[k];
                if(dp[i-1][state] + v[i] < dp[i][j])
                    dp[i][j] = dp[i-1][state] + v[i];
            }
        }
        printf("%d\n", dp[N][0]);
    }
    return 0;
}
