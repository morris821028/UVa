#include <stdio.h>
#include <stdlib.h>
int ST[1048577], M, N = 300005;
char CLR[1048577];
void setST() {
    for(M = 1; M < N+2; M <<= 1);
    int i;
    for(i = 2*M-1; i >= M; i--)
        ST[i] = 0, CLR[i] = 0;
    for(i = M-1; i > 0; i--)
        ST[i] = ST[i<<1]+ST[i<<1|1], CLR[i] = 0;
}
int relax(int k) {
    if(CLR[k]) {
        CLR[k] = 0;
        if(k < M) {
            ST[k<<1] = ST[k<<1|1] = 0;
            CLR[k<<1] = CLR[k<<1|1] = 1;
        }
    }
}
int query(int l, int r, int x, int y, int k) {
    relax(k);
    int m = (l+r)>>1;
    if(l == x && r == y)
        return ST[k];
    if(x > m)
        return query(m+1, r, x, y, k<<1|1);
    else if(y <= m)
        return query(l, m, x, y, k<<1);
    else
        return query(l, m, x, m, k<<1)+
                query(m+1, r, m+1, y, k<<1|1);
} // query(1, M, x, y, 1)
void modifyCLR(int l, int r, int x, int y, int k) {
    relax(k);
    int m = (l+r)>>1;
    if(l == x && r == y) {
        CLR[k] = 1, ST[k] = 0;
        return ;
    }
    if(x > m)
        modifyCLR(m+1, r, x, y, k<<1|1);
    else if(y <= m)
        modifyCLR(l, m, x, y, k<<1);
    else
        modifyCLR(l, m, x, m, k<<1), modifyCLR(m+1, r, m+1, y, k<<1|1);
    ST[k] = ST[k<<1] + ST[k<<1|1];
}
void modify(int s, int val) {
    static int t, l, r, m;
    t = 1;
    l = 0, r = M-1;
    do {
        relax(t);
        ST[t] += val;
        m = (l+r)>>1;
        if(m < s)
            t = t<<1|1, l = m+1;
        else
            t <<= 1, r = m;
    } while(t < 2*M);
}
int main() {
    setST();
    int n, mn, arg;
    int base_line = 100005;
    int tot = 0, leave = 0, tmp;
    char cmd[20];
    scanf("%d %d", &n, &mn);
    while(n--) {
        scanf("%s %d", cmd, &arg);
        if(cmd[0] == 'I') {
            if(arg >= mn) {
                modify(arg+base_line, 1), tot++;
            }
        } else if(cmd[0] == 'A') {
            base_line -= arg; // 基線下降
        } else if(cmd[0] == 'S') {
            if(arg == 0)    continue;
            tmp = query(0, M-1, base_line, base_line+arg+mn-1, 1);
            tot -= tmp, leave += tmp;
            modifyCLR(0, M-1, base_line, base_line+arg+mn-1, 1);
            base_line += arg; // 基線上升
        } else {
            if(tot < arg) {
                puts("-1");
                continue;
            }
            int s;
            arg = tot-arg+1;
            for(s = 1; s < M;) {
                relax(s);
                if(ST[s<<1] < arg)
                    arg -= ST[s<<1], s = s<<1|1;
                else
                    s = s<<1;
            }
            printf("%d\n", s-M-base_line);
        }
    }
    printf("%d\n", leave);
    return 0;
}
