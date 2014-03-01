#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    char s[20];
    while(scanf("%s", s) == 1) {
        if(!strcmp(s, "0"))
            break;
        int len = strlen(s);
        int i, base = 2;
        for(i = 0; i < len; i++) {
            s[i] -= '0';
            if(s[i] > base)
                base = s[i];
        }

        for(base++ ; ; base++) {
            long long a = 1, tmp = 0;
            for(i = len-1; i >= 0; i--)
                tmp += s[i]*a, a *= (long long)base;
            a = (long long)sqrt(tmp);
            if(a*a == tmp) {
                printf("%d\n", base);
                break;
            }
        }
    }
    return 0;
}
