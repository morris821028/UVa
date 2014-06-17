#include <stdio.h>
#include <string.h>
#include <set>
#include <iostream>
using namespace std;
int main() {
    char cmd[1005];
    int i, j, k;
    /*freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);*/
    while(gets(cmd)) {
        int len = strlen(cmd);
        int op[105], num[105], nidx = 0, oidx = 0;
        for(i = 0; i < len; ) {
            while(cmd[i] == ' ')
                i++;
            if(cmd[i] >= '0' && cmd[i] <= '9') {
                int tmp = 0;
                while(cmd[i] >= '0' && cmd[i] <= '9')
                    tmp = tmp*10 + cmd[i]-'0', i++;
                num[nidx++] = tmp;
            } else if(cmd[i] == '+' || cmd[i] == '-'){
                op[oidx++] = cmd[i++];
            }
        }
        set<int> dp[50][50];
        for(i = 0; i < nidx; i++) {
            for(j = 0; i+j < nidx; j++) {
                if(i == 0) {
                    dp[j][j+i].insert(num[j]);
                    continue;
                }
                for(k = j; k < i+j; k++) {
                    for(set<int>::iterator it = dp[j][k].begin();
                        it != dp[j][k].end(); it++)
                    for(set<int>::iterator jt = dp[k+1][i+j].begin();
                        jt != dp[k+1][i+j].end(); jt++) {
                        if(op[k] == '+')
                            dp[j][i+j].insert(*it+*jt);
                        else
                            dp[j][i+j].insert(*it-*jt);
                    }
                }
            }
        }
        printf("%d\n", dp[0][nidx-1].size());
    }
    return 0;
}
