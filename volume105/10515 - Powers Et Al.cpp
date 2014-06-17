#include <stdio.h>
#include <string.h>
char g[][5] = {"0000","1111","6248","1397","6464",
"5555","6666","1793","6842","1919"};
int main() {
    char m[105], n[105];
    while(scanf("%s %s", m, n) == 2) {
        if(m[0] == '0' && n[0] == '0' && m[1] == '\0' && n[1] == '\0')
            break;
        if(n[0] == '0' && n[1] == '\0') {
            puts("1");
            continue;
        }
        int a = m[strlen(m)-1]-'0';
        int c = strlen(n)-1;
        int b = (n[c]-'0')+(c-1 >= 0 ? (n[c-1]-'0')*10 : 0);
        b %= 4;
        printf("%c\n", g[a][b]);
    }
    return 0;
}
