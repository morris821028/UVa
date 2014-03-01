#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;
vector<int> g[10005];
int dp[10005][11];
void dfs(int nd, int p) {
    int i, j, tmp;
    for(i = 1; i <= 10; i++)
        dp[nd][i] = i;
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(*it != p) {
            dfs(*it, nd);
        }
    }
    for(i = 1; i <= 10; i++) {
        for(vector<int>::iterator it = g[nd].begin();
            it != g[nd].end(); it++) {
            if(*it != p) {
                tmp = 0xfffffff;
                for(j = 1; j <= 10; j++) {
                    if(i == j)
                        continue;
                    tmp = min(tmp, dp[*it][j]);
                }
                dp[nd][i] += tmp;
            }
        }
    }
}
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
int flag;
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0' && c <= '9')
        *x = (*x << 3) + (*x << 1) + c-'0';
    if(c == '\n')   flag = 0;
    *x *= neg;
    return 1;
}
int main() {
    int n, m, i, x;
    while(ReadInt(&n) && n) {
        for(i = 0; i < n; i++)
            g[i].clear();
        //string line;
        for(i = 0; i < n; i++) {
            flag = 1;
            ReadInt(&m);
            /*getline(cin, line);
            stringstream sin(line);*/
            if(readchar() != '\n')
            while(flag) {
                ReadInt(&x);
                g[m].push_back(x);
                g[x].push_back(m);
            }
        }
        dfs(0, -1);
        int res = 0xfffffff;
        for(i = 1; i <= 10; i++)
            res = min(res, dp[0][i]);
        printf("%d\n", res);
    }
    return 0;
}
