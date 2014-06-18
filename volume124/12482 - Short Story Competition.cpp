#include <stdio.h>
#include <string.h>

int main() {
    int N, L, C;
    char s[100];
    while(scanf("%d %d %d", &N, &L, &C) == 3) {
        int len, line = 0, sum = 0;
        while(N--) {
            scanf("%s", s);
            len = strlen(s);
            if(sum + len <= C) {
                sum += len+1;
            } else {
                sum = len+1;
                line++;
            }
        }
        line += (sum != 0);
        if(line%L)  printf("%d\n", line/L+1);
        else    printf("%d\n", line/L);
    }
    return 0;
}
