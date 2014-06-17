#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
char s[20], buf[5] = {0,1,6,8,9};
int n = 0;
LL stk[1000005];
void dfs(int idx, LL head, LL tail, LL t) {
    if(head > 680000000)
        return;
    int i, tmp;
    if(idx > 0) {
        stk[n] = head*t+tail;
        if(stk[n] <= 68000000000000089LL)
            n++;
        if(s[idx-1] != 6 && s[idx-1] != 9) {
            stk[n] = head*t/10+tail-s[idx-1]*t/10;
            if(stk[n] <= 68000000000000089LL)
                n++;
        }
    }
    if(idx == 9)    return;
    for(i = 1-(idx!=0); i < 5; i++) {
        s[idx] = buf[i];
        tmp = s[idx];
        if(tmp == 6)        tmp = 9;
        else if(tmp == 9)   tmp = 6;
        dfs(idx+1, head*10+s[idx], tail+t*tmp, t*10);
    }
}
int main() {
    dfs(0,0,0,1);
    stk[n++] = 0;
    sort(stk, stk+n);
    while(scanf("%d", &n) == 1 && n)
        printf("%lld\n", stk[n-1]);
    return 0;
}
