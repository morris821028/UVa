#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    char str[1005];
    while(scanf("%s", &str) == 1) {
        if(!strcmp(str, "0"))
            break;
        int len = strlen(str);
        int num = str[0]-'0', i;
        if(len > 1 && len%2 == 0) num = num*10 + str[1]-'0';
        len = (len-1)/2;
        printf("%d", (int)sqrt(num));
        for(i = 0; i < len; i++)
            putchar('0');
        puts("");
    }
    return 0;
}
