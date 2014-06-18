#include <stdio.h>
int A[(1<<18)+1], ST[(1<<19)+1];
void setTree(int k, int l, int r) {
    if(l == r)
        ST[k] = A[l];
    else if(l < r) {
        int m = (l+r)>>1;
        setTree(k<<1, l, m);
        setTree(k<<1|1, m+1, r);
        ST[k] = ST[k<<1] + ST[k<<1|1];
    } else
        ST[k] = 0;
}
int query(int k, int l, int r, int &x, int &y) {
    if(l > r)   return 0;
    if(x <= l && r <= y)
        return ST[k];
    int m = (l+r)>>1;
    if(y <= m)
        return query(k<<1, l, m, x, y);
    else if(x > m)
        return query(k<<1|1, m+1, r, x, y);
    else
        return query(k<<1, l, m, x, y)+
                query(k<<1|1, m+1, r, x, y);
}
void modify(int k, int l, int r, int &x, int &y) {
    if(l > r)   return ;
    if(l == r && l == x) {
        ST[k] = y;
        return;
    }
    int m = (l+r)>>1;
    if(x <= m)
        modify(k<<1, l, m, x, y);
    else
        modify(k<<1|1, m+1, r, x, y);
    if(l != r)
        ST[k] = ST[k<<1] + ST[k<<1|1];
}
int main() {
    int n, x, y, i;
    int cases = 0;
    char op[10], cmd[50];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        while(getchar() != '\n');
        setTree(1, 1, n);
        if(cases)   puts("");
        printf("Case %d:\n", ++cases);
        while(gets(cmd)) {
            if(cmd[0] == 'E')
                break;
            sscanf(cmd, "%s %d %d", op, &x, &y);
            if(op[0] == 'M')
                printf("%d\n", query(1, 1, n, x, y));
            else
                modify(1, 1, n, x, y);
        }
    }
    return 0;
}
