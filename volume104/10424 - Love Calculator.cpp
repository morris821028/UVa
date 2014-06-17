#include <stdio.h>

int main() {
    char s[100];
    while(gets(s)) {
        int a = 0, b = 0, i;
        for(i = 0; s[i]; i++) {
            if(s[i] >= 'a' && s[i] <= 'z')
                a += s[i]-'a'+1;
            if(s[i] >= 'A' && s[i] <= 'Z')
                a += s[i]-'A'+1;
        }
        while(a >= 10) {
            int tmp = 0;
            while(a > 0)
                tmp += a%10, a /= 10;
            a = tmp;
        }
        for(gets(s), i = 0; s[i]; i++) {
            if(s[i] >= 'a' && s[i] <= 'z')
                b += s[i]-'a'+1;
            if(s[i] >= 'A' && s[i] <= 'Z')
                b += s[i]-'A'+1;
        }
        while(b >= 10) {
            int tmp = 0;
            while(b > 0)
                tmp += b%10, b /= 10;
            b = tmp;
        }
        if(a > b){
            int tmp;
            tmp = a, a = b, b = tmp;
        }
        printf("%.2lf %%\n", (double)a*100/b);
    }
    return 0;
}
