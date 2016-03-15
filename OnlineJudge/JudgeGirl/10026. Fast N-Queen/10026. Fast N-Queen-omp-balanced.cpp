#include <stdio.h>
#define MAXQ 16384
#define MAXN 32
int y_valid[32] = {};
typedef struct Board {
    int row, dia1, dia2;
} Board;
Board R[MAXQ*MAXN];
int dfs(int lv, int row, int dia1, int dia2, int mask) {
    if (row == mask)
        return 1;
    int pos = mask & (~(row | dia1 | dia2)) & y_valid[lv], p;
    int ret = 0;
    while (pos) {
        p = pos & (-pos);
        pos -= p;
        ret += dfs(lv+1, row|p, (dia1|p)<<1, (dia2|p)>>1, mask);
    }
    return ret;
}
int ida_dep, ida_cnt;
void IDA(int lv, int row, int dia1, int dia2, int mask) {
    if (lv == ida_dep) {
        Board b = {.row = row, .dia1 = dia1, .dia2 = dia2};
        R[ida_cnt++] = b;
        return ;
    }
    int pos = mask & (~(row | dia1 | dia2)) & y_valid[lv], p;
    while (pos) {
        p = pos & (-pos);
        pos -= p;
        IDA(lv+1, row|p, (dia1|p)<<1, (dia2|p)>>1, mask);
    }
}
int totalNQueens(int n) {
    int it = 0;
    int row = 0, dia1 = 0, dia2 = 0, mask = (1<<n)-1, lv = 0;
    for (it = 1; it <= n; it++) {
        ida_dep = it, ida_cnt = 0;
        IDA(0, row, dia1, dia2, mask);
        if (ida_cnt >= MAXQ) {
            int sum = 0;
            int chunk = 1024;
            #pragma omp parallel for schedule(static, chunk) reduction(+:sum)
            for (int i = 0; i < ida_cnt; i++)
                sum += dfs(it, R[i].row, R[i].dia1, R[i].dia2, mask);
            return sum;
        }
    }
    return ida_cnt;
}
int main() {
    int cases = 0, n;
    char s[32] = {};
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            y_valid[i] = (1<<n)-1;
            for (int j = 0; j < n; j++) {
                if (s[j] == '*')
                    y_valid[i] ^= (1<<j);
            }
        }
        int ret = totalNQueens(n);
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}