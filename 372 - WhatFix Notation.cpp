#include <stdio.h>
char infix[105], prefix[105];
int idx;
void dfs(int l, int r) {
    if(l > r)   return;
    char p = prefix[idx], i;
    idx++;
    for(i = l; i <= r; i++)
        if(infix[i] == p)
            break;
    dfs(l, i-1);
    dfs(i+1, r);
    printf(" %c", p);
}
int main() {
    while(gets(infix)) {
        gets(prefix);
        int i, j;
        for(i = 0, j = 0; infix[i]; i++) {
            if(infix[i] != ' ')
                infix[j++] = infix[i];
        }
        infix[j] = '\0';
        for(i = 0, j = 0; prefix[i]; i++) {
            if(prefix[i] != ' ')
                prefix[j++] = prefix[i];
        }
        prefix[j] = '\0';
        printf("INFIX   =>");
        for(i = 0; infix[i]; i++)
            printf(" %c", infix[i]);
        puts("");
        printf("PREFIX  =>");
        for(i = 0; prefix[i]; i++)
            printf(" %c", prefix[i]);
        puts("");
        printf("POSTFIX =>");
        idx = 0;
        dfs(0, j-1);
        puts("");
    }
    return 0;
}
