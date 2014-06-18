#include <stdio.h>
#include <string.h>
char s[1000005];
int main() {
    while(scanf("%s", s) == 1) {
        if(!strcmp(s, "END"))
            break;
        int x = strlen(s), idx = 1, last;
        while(1) {
            if(x == 1 && s[0] == '1')
                break;
            sprintf(s, "%d", x);
            last = x, x = strlen(s);
            idx++;
            if(last == x)
                break;
        }
        printf("%d\n", idx);
    }
    return 0;
}
