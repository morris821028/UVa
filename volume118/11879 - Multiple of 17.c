#include <stdio.h>

int main() {
    char str[102];
    while(gets(str)) {
        if(str[0] == '0' && str[1] == '\0')
            break;
        int tmp = 0, i;
        for(i = 0; str[i]; i++) {
            tmp = tmp*10 + str[i]-'0';
            tmp %= 17;
        }
        printf("%d\n", tmp == 0);
    }
    return 0;
}
