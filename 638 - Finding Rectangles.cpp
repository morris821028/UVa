#include <stdio.h>
#include <set>
#include <iostream>
using namespace std;
int main() {
    int n, cases = 0;
    int x, y, i, j, ki, kj, idx1, idx2;
    char s[2];
    while(scanf("%d", &n) == 1 && n) {
        char g[50][50] = {}, ap[50] = {};
        int next[50][50] = {}, nx[50] = {};
        for(i = 0; i < n; i++) {
            scanf("%s %d %d", s, &x, &y);
            g[x][y] = s[0];
            ap[x] = 1;
        }
        int xpre = 0;
        for(i = 0; i < 50; i++) {
            if(ap[i])
                nx[xpre] = i, xpre = i;
            else
                continue;
            int pre = 0;
            for(j = 0; j < 50; j++) {
                if(g[i][j]) {
                    next[i][pre] = j;
                    pre = j;
                }
            }
            next[i][pre] = -1;
        }
        nx[xpre] = -1;
        set<string> ans;
        char buf[26][2], buft;
        for(i = ap[0] == 0 ? nx[0] : 0; i != -1; i = nx[i]) {
            for(j = nx[i]; j != -1; j = nx[j]) {
                idx1 = 0, idx2 = 0, buft = 0;
                if(!g[i][idx1])  idx1 = next[i][idx1];
                if(!g[j][idx2])  idx2 = next[j][idx2];
                while(idx1 != -1 && idx2 != -1) {
                    if(idx1 == idx2)
                        buf[buft][0] = g[i][idx1], buf[buft++][1] = g[j][idx2];
                    if(idx1 <= idx2)
                        idx1 = next[i][idx1];
                    else
                        idx2 = next[j][idx2];
                }
                for(ki = 0; ki < buft; ki++) {
                    for(kj = ki+1; kj < buft; kj++) {
                        string tmp = "";
                        tmp = tmp + buf[kj][0] + buf[kj][1] + buf[ki][1] + buf[ki][0];
                        ans.insert(tmp);
                    }
                }
            }
        }
        printf("Point set %d:", ++cases);
        if(ans.size() == 0)
            puts(" No rectangles");
        else {
            puts("");
            int cnt = 0;
            for(set<string>::iterator it = ans.begin();
                it != ans.end(); it++) {
                putchar(' ');
                putchar((*it)[0]);
                putchar((*it)[1]);
                putchar((*it)[2]);
                putchar((*it)[3]);
                cnt++;
                if(cnt == 10)
                    cnt = 0, puts("");
            }
            if(cnt)
                puts("");
        }
    }
    return 0;
}
