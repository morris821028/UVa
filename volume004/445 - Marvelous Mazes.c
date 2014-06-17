#include <stdio.h>

int main() {
    char str[200];
    while(gets(str)) {
        int num = 0, i, j;
        for(i = 0; str[i]; i++) {
            switch(str[i]) {
                case '0' ... '9': num += str[i]-'0';break;
                case 'b':
                    for(j = 0; j < num; j++)
                        putchar(' ');
                    num = 0;
                    break;
                case '!':
                    puts("");
                    break;
                default:
                    for(j = 0; j < num; j++)
                        putchar(str[i]);
                    num = 0;
            }
        }
        puts("");
    }
    return 0;
}
