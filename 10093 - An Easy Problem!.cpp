#include <stdio.h>
#include <string.h>
int main() {
    char s[100005];
    int i, j;
    while(scanf("%s", s) == 1) {
        char *p = s;
        if(*p == '+')
            p++;
        else if(*p == '-')
            p++;
        int mn = 1, err = 0, len;
        len = strlen(p);
        for(i = 0; i < len; i++) {
            if(p[i] >= '0' && p[i] <= '9') {
                p[i] -= '0';
            } else if(p[i] >= 'A' && p[i] <= 'Z') {
                p[i] = p[i]-'A'+10;
            } else if(p[i] >= 'a' && p[i] <= 'z') {
                p[i] = p[i]-'a'+36;
            } else
                err = 1;
            if(p[i] > mn)
                mn = p[i];
        }
        mn++;
        for(i = mn; i <= 62; i++) {
            int tmp = 0, k = i-1;
            for(j = 0; j < len; j++) {
                tmp = tmp*i + p[j];
                tmp %= k;
            }
            if(tmp == 0)  break;
        }
        if(i == 63 || err == 1)
            puts("such number is impossible!");
        else
            printf("%d\n", i);
    }
    return 0;
}
