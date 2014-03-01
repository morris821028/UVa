#include <stdio.h>

int main() {
    int t, cases = 0;
    int i, j;
    long long p[55][55] = {};
    p[0][0] = 1;
    for(i = 1; i <= 50; i++) {
        p[i][0] = 1;
        for(j = 1; j <= i; j++)
            p[i][j] = p[i-1][j]+p[i-1][j-1];
    }
    char s[128], word[2][55];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int n = 0, k, idx;
        for(i = 1; s[i]; i++) {
            idx = 0;
            while(s[i] != '+' && s[i] != ')')
                word[n][idx++] = s[i++];
            word[n++][idx] = '\0';
            if(s[i] == ')') break;
        }
        sscanf(s+i+2,"%d", &k);
        printf("Case %d: ", ++cases);
        for(i = 0; i <= k; i++) {
            if(i)   putchar('+');
            if(p[k][i] != 1)
                printf("%lld*", p[k][i]);
            if(i != k) {
                printf("%s", word[0]);
                if(k-i != 1)
                    printf("^%d", k-i);
                if(i)   printf("*");
            }
            if(i) {
                printf("%s", word[1]);
                if(i != 1)
                    printf("^%d", i);
            }
        }
        puts("");
    }
    return 0;
}
