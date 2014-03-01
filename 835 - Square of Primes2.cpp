#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
vector<int> dsum[50];
int p[100000] = {};
int head[100000] = {}, tail[100000] = {};
void sieve() {
    int i, j, k;
    for(i = 2; i < 100000; i++) {
        if(p[i] == 0) {
            for(j = i+i; j < 100000; j += i)
                p[j] = 1;
            if(i > 10000) {
                k = i;
                int res = 0;
                while(k) {
                    head[k] = 1;
                    res += k%10;
                    k /= 10;
                }
                dsum[res].push_back(i);
                k = i, j = 10;
                while(j <= 100000)
                    tail[k%j] = 1, j *= 10;
            }
        }
    }
}
char g[20][20];
int firstline = 0;
void dfs(int idx, int sum, int d) {
    if(idx == 5) {
        int i;
        if(firstline)   puts("");
        firstline = 1;
        for(i = 0; i < 5; i++)
            puts(g[i]);
        return;
    }
    int i, j, err, tmp;
    for(vector<int>::iterator it = dsum[sum].begin();
        it != dsum[sum].end(); it++) {
        sprintf(g[idx], "%d", *it);
        if(idx == 0 && g[0][0] != d+'0')    continue;
        err = 0;
        for(i = 0; i < 5; i++) {
            tmp = 0;
            for(j = 0; j <= idx; j++)
                tmp = tmp*10 + g[j][i]-'0';
            if(!head[tmp])  err = 1;
        }
        if(err) continue;
        for(i = 0; i < 5; i++) {
            tmp = 0;
            for(j = 0; j <= idx; j++)
                tmp += g[j][i]-'0';
            if(tmp > sum  || (idx != 4 && (sum-tmp)/(4-idx) >= 10))  err = 1;
        }
        if(err) continue;
        for(i = 0, tmp = 0; i <= idx; i++)
            tmp = tmp * 10 + g[i][i]-'0';
        if(!head[tmp])  continue;
        for(i = 0, tmp = 0; i <= idx; i++)
            tmp += g[i][i]-'0';
        if(tmp > sum  || (idx != 4 && (sum-tmp)/(4-idx) >= 10))  continue;
        if(idx == 4) {
            for(i = 0; i < 5; i++) {
                tmp = 0;
                for(j = 0; j < 5; j++)
                    tmp += g[j][i]-'0';
                if(tmp != sum)  err = 1;
            }
            for(i = 0, tmp = 0; i < 5; i++)
                tmp = tmp*10 + g[i][i]-'0';
            if(!head[tmp])  err = 1;
            for(i = 0, tmp = 0; i < 5; i++)
                tmp += g[i][i]-'0';
            if(tmp != sum)  err = 1;
            for(i = 0, tmp = 0; i < 5; i++)
                tmp = tmp*10 + g[4-i][i]-'0';
            if(!head[tmp])  err = 1;
            for(i = 0, tmp = 0; i < 5; i++)
                tmp += g[4-i][i]-'0';
            if(tmp != sum)  err = 1;
        }
        if(err) continue;
        for(i = idx, tmp = 0; i >= 0; i--)
            tmp = tmp*10 + g[i][4-i]-'0';
        if(!tail[tmp])  continue;
        for(i = idx, tmp = 0; i >= 0; i--)
            tmp += g[i][4-i]-'0';
        if(tmp > sum || (idx != 4 && (sum-tmp)/(4-idx) >= 10))  continue;
        dfs(idx+1, sum, d);
    }
}
int main() {
    sieve();
    int t, sum, d;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &sum, &d);
        memset(g, '0', sizeof(g));
        g[0][0] = d+'0';
        firstline = 0;
        printf("%d\n", dsum[sum].size());
        dfs(0, sum, d);
        if(t)   puts("");
    }
    return 0;
}
