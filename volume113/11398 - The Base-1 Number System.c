#include <stdio.h>
#include <string.h>

int main() {
    char str[35];
    while(scanf("%s", str) == 1) {
        if(!strcmp(str, "~"))
            break;
        int flag = 0, len;
        unsigned int ans = 0;
        do {
            len = strlen(str);
            if(len == 1)
                flag = 1;
            else if(len == 2)
                flag = 0;
            else {
                for(len -= 2; len > 0; len--)
                    ans = (ans << 1) | flag;
            }
        } while(scanf("%s", str) == 1 && strcmp(str, "#"));
        printf("%u\n", ans);
    }
}
