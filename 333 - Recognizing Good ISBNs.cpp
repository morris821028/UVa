#include <stdio.h>

int main() {
    char s[105];
    while(gets(s)) {
        char *p = s;
        int d = 0, flag = 0, i, j, sum = 0, ten;
        while(*p == ' ')    p++;
        for(i = 0; p[i]; i++) {
            if(p[i] >= '0' && p[i] <= '9') {
                d++;
                if(d <= 9)
                    sum += (11-d)*(p[i]-'0');
                else
                    ten = p[i]-'0';
            } else if(p[i] != ' ' && p[i] != '-') {
                if(d == 9 && p[i] == 'X') {
                    d++;
                    ten = 10;
                    continue;
                }
                flag = 1;
            }
        }
        i--;
        while(i >= 0 && p[i] == ' ')
            p[i] = '\0', i--;
        printf("%s is ", p);
        sum += ten;
        if(d != 10 || flag || sum%11) {
            puts("incorrect.");
            continue;
        } else
            puts("correct.");
    }
    return 0;
}
