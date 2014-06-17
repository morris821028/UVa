#include <stdio.h>

int main() {
    int a, b;
    char s[20];
    while(scanf("%d %d %s", &a, &b, s) == 3) {
        int i, flag = 0;
        long long dec = 0, base = 1;
        for(i = 0; s[i]; i++) {
            dec *= a;
            if(s[i] >= '0' && s[i] <= '9') {
                if(s[i]-'0' >= a) {
                    flag = 1;
                } else {
                    dec += s[i]-'0';
                }
            } else {
                if(s[i]-'A'+10 >= a) {
                    flag = 1;
                } else {
                    dec += (s[i]-'A'+10);
                }
            }
        }
        if(flag) {
            printf("%s is an illegal base %d number\n", s, a);
        } else {
            long long c[50] = {}, ct = -1;
            while(dec) {
                c[++ct] = dec%b;
                dec /= b;
            }
            if(ct < 0) ct = 0;
            printf("%s base %d = ", s, a);
            while(ct >= 0) {
                printf("%c", c[ct] <= 9 ? c[ct]+'0' : c[ct]-10+'A');
                ct--;
            }
            printf(" base %d\n", b);
        }
    }
    return 0;
}
