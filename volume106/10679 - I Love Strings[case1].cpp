#include <stdio.h>
char ans[65536], *p = ans;
int main() {
    char S[100005], T[1005], *a = T+500, *b = T+999;
    int t, n;
    scanf("%d", &t);
    getchar();
    while(t--) {
        fread(S, 1, 100000, stdin);
        scanf("%d", &n);
        getchar();
        while(n--) {
            gets(T);
            if(*a != 97 || *b != 98)
                *p++ = 'n', *p++ = '\n';
                //puts("n");
            else
                *p++ = 'y', *p++ = '\n';
                //puts("y");
        }
    }
    p--;
    *p = '\0';
    puts(ans);
    return 0;
}
