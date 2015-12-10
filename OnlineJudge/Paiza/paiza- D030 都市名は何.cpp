#include <stdio.h>
#include <string.h>
int main() {
    char s[1024];
    while (scanf("%s", s) == 1) {
        int n = strlen(s);
        for (int i = 0; i < n-3; i++)
            putchar(s[i]);
        puts("");
    }
    return 0;
}