#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int p[300], pt = 0;
int cmp(const void *a, const void *b) {
    char x[10], y[10];
    sprintf(x, "%d", *(int *)a);
    sprintf(y, "%d", *(int *)b);
    return strcmp(x, y);
}
void sieve() {
    int i, j, mark[300] = {};
    for(i = 2; i < 300; i++) {
        if(mark[i] == 0) {
            p[pt++] = i;
            for(j = i+i; j < 300; j += i)
                mark[j] = 1;
        }
    }
    qsort(p, pt, sizeof(int), cmp);
}
int way[20], flag;
void dfs(int idx, int m, int sum, int i) {
    if(flag == 1 || sum < 0)   return;
    if(m == 0) {
        if(sum == 0) {
            for(i = 0; i < idx; i++) {
                if(i)   putchar('+');
                printf("%d", way[i]);
            }
            puts("");
            flag = 1;
        }
        return;
    }
    for(; i < pt; i++) {
        way[idx] = p[i];
        if(p[i] == 2)
            dfs(idx+1, m-1, sum-2, i+1);
        else
            dfs(idx+1, m-1, sum-p[i], i+(idx && way[idx-1] == way[idx]));
    }
}
int main() {
    sieve();
    int n, m, cases = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        printf("CASE %d:\n", ++cases);
        flag = 0;
        dfs(0, m, n, 0);
        if(!flag)
            puts("No Solution.");
    }
    return 0;
}
