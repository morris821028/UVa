#include <stdio.h>

int main() {
    int t, n, i;
    char s[3000];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        scanf("%s", s);
        int tmp = 0;
        for(i = 0; s[i]; i++) {
            tmp = tmp*10 + s[i]-'0';
            tmp %= n;
        }
        printf("%d\n", tmp);
    }
    return 0;
}
