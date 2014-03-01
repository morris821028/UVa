#include <cstdio>
#include <cstring>
int main() {
    char s[1000];
    int i, j, first = 0;
    while(gets(s)) {
        if(first)   puts("");
        first = 1;
        int num[100], ope[100];
        int nt = 0, ot = 0, len = strlen(s);
        char *p;
        for(i = 0; i < len; i++) {
            while(s[i] == ' ')  i++;
            int tmp = 0;
            if(s[i] == '-') {
                i++;
                while(s[i] && s[i] >= '0' && s[i] <= '9')
                    tmp = tmp*10 + s[i]-'0', i++;
                num[nt++] = -tmp;
            } else if(s[i] == '+') {
                i++;
                while(s[i] && s[i] >= '0' && s[i] <= '9')
                    tmp = tmp*10 + s[i]-'0', i++;
                num[nt++] = tmp;
            } else {
                int tmp = 0;
                while(s[i] && s[i] >= '0' && s[i] <= '9')
                    tmp = tmp*10 + s[i]-'0', i++;
                num[nt++] = tmp;
            }
            while(s[i] == ' ') i++;
            if(s[i] == '=') {
                i++;
                while(s[i] == ' ') i++;
                p = s+i;
                break;
            }
            ope[ot++] = s[i];
        }
        ope[nt-1] = '=';
        while(nt) {
            for(i = 0; i < nt; i++) {
                if(i)   putchar(' ');
                printf("%d %c", num[i], ope[i]);
            }
            putchar(' ');
            puts(p);
            int ok = 1;
            for(i = 0; i < ot; i++) {
                if(ope[i] == '*') {
                    num[i] = num[i]*num[i+1];
                    for(i++; i <= ot; i++)
                        num[i] = num[i+1], ope[i-1] = ope[i];
                    ok = 0;
                    break;
                }
                if(ope[i] == '/') {
                    num[i] = num[i]/num[i+1];
                    for(i++; i <= ot; i++)
                        num[i] = num[i+1], ope[i-1] = ope[i];
                    ok = 0;
                    break;
                }
            }
            if(ok) {
                if(ope[0] == '+')
                    num[0] = num[0]+num[1];
                if(ope[0] == '-')
                    num[0] = num[0]-num[1];
                for(i = 1; i <= ot; i++)
                    num[i] = num[i+1], ope[i-1] = ope[i];
            }
            ot--, nt--;
        }
    }
    return 0;
}
