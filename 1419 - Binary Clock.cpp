#include <stdio.h>

int main() {
    int cases = 0, h, m, s, i;
    scanf("%*d");
    while(scanf("%d:%d:%d", &h, &m, &s) == 3) {
        printf("%d ", ++cases);
        for(i = 5; i >= 0; i--)
            printf("%d%d%d", (h>>i)&1, (m>>i)&1, (s>>i)&1);
        putchar(' ');
        for(i = 5; i >= 0; i--)
            printf("%d", (h>>i)&1);
        for(i = 5; i >= 0; i--)
            printf("%d", (m>>i)&1);
        for(i = 5; i >= 0; i--)
            printf("%d", (s>>i)&1);
        puts("");
    }
    return 0;
}
