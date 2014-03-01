#include <stdio.h>

int main() {
    int t, Case = 0;
    char str[205];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", str);
        printf("Case %d: ", ++Case);
        int i, tmp = 0;
        char ch;
        for(i = 0; str[i]; i++) {
            if(str[i] >= 'A' && str[i] <= 'Z') {
                while(tmp)
                    putchar(ch), tmp--;
                ch = str[i];
            } else {
                tmp = tmp*10 + str[i]-'0';
            }
        }
        while(tmp)
            putchar(ch), tmp--;
        puts("");
    }
    return 0;
}
