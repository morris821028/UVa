#include <stdio.h>
#include <string.h>

int main() {
    int g, i, j;
    char str[101];
    while(scanf("%d", &g) == 1 && g) {
        scanf("%s", str);
        int len = strlen(str), p = len/g;
        for(i = 0; i < len; i += p) {
            for(j = i+p-1; j >= i; j--)
                putchar(str[j]);
        }
        puts("");
    }
    return 0;
}
