#include <stdio.h>

int main() {
    char str[50], ch[] = " 123 12  22455 12623 1 2 2";
    while(scanf("%s", str) == 1) {
        int last = -1, i;
        for(i = 0; str[i]; i++) {
            if(ch[str[i]-'A'] >= '0') {
                if(ch[str[i]-'A'] != last) {
                    last = ch[str[i]-'A'];
                    printf("%c", ch[str[i]-'A']);
                }
            } else
                last = -1;
        }
        puts("");
    }
    return 0;
}
