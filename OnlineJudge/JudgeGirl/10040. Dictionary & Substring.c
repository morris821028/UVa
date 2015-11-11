#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 131072
#define MAXS 1048576

char *str[MAXN];
char sbuf[MAXS];
int count_str(const char *s, int N) {
    int ret = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; str[i][j]; j++) {
            int p = j, q = 0;
            while (s[q] && str[i][p] == s[q])
                p++, q++;
            if (s[q] == '\0') {
                ret++;
                break;
            }
        }
    }
    return ret;
}
int main() {
    int N, Q;
    char s[1024];
    while (scanf("%d", &N) == 1 && N) {
        char *p = sbuf, *st;
        for (int i = 0; i < N; i++) {
            str[i] = p, scanf("%s", p);
            while (*p != '\0')
                p++;
            p++;
        }
        scanf("%d", &Q);
        for (int i = 0; i < Q; i++) {
            scanf("%s", s);
            printf("%d\n", count_str(s, N));
        }
    }
    return 0;
}



