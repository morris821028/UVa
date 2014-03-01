#include <stdio.h>
#include <string.h>
int main() {
    char str[999];
    char ascii[128] = {};
    int i;
    ascii[' '] = ascii['!'] = ascii[','] = 1;
    ascii['.'] = ascii[':'] = ascii[';'] = 1;
    ascii['?'] = 1;
    for(i = 'a'; i <= 'z'; i++)
        ascii[i] = 1;
    for(i = 'A'; i <= 'Z'; i++)
        ascii[i] = 1;
    while(gets(str)) {
        int i, j, tmp, idx = 0;
        char code[999];
        if(str[0] >= '0' && str[0] <= '9') {
            tmp = 0;
            for(i = strlen(str)-1; i >= 0; i--) {
                tmp = tmp*10 + str[i]-'0';
                if(ascii[tmp]) {
                    code[idx++] = tmp;
                    tmp = 0;
                }
            }
            if(ascii[tmp]) {
                putchar(tmp);
                tmp = 0;
            }
        } else {
            for(i = strlen(str)-1; i >= 0; i--) {
                while(str[i]) {
                    code[idx++] = str[i]%10+'0';
                    str[i] /= 10;
                }
            }
        }
        for(i = 0; i < idx; i++)
            putchar(code[i]);
        puts("");
    }
    return 0;
}
