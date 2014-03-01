#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
char s[32][32], buf[105];
int n, res, used[105] = {};
void dfs(int idx, int len) {
    if(len >= res)  return;
    if(idx == n) {
        res = min(res, len);
        return;
    }
    int i, j, k;
    for(i = 0; i < n; i++) {
        if(used[i] == 0) {
            used[i] = 1;
            if(idx == 0) {
                for(j = 0; s[i][j]; j++)
                    buf[j] = s[i][j];
                dfs(idx+1, j);
            } else {
                for(j = len-strlen(s[i]); j <= len; j++) {
                    for(k = 0; s[i][k] && j+k < len; k++) {
                        if(buf[j+k] != s[i][k])
                            break;
                    }
                    if(j+k == len) {
                        int p = len, q = k;
                        for(; s[i][q]; q++)
                            buf[p++] = s[i][q];
                        dfs(idx+1, p);
                        break;
                    }
                }
            }
            used[i] = 0;
        }
    }
}
int main() {
    int testcase, cases = 0;
    int i;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%s", s[i]);
        res = 0xffff;
        dfs(0, 0);
        printf("Case %d: %d\n", ++cases, res);
    }
    return 0;
}
/*
1000
6
abcde
a
b
c
d
e
2
abcba
bcb
2
abcba
cba
*/
