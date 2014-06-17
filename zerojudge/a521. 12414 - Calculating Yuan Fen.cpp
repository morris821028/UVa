#include <stdio.h>
int main() {
    char s[100], buf[100];
    while(gets(s)) {
        int ST = 1;
        int i, j, ok = 1;
        while(ST <= 10000 && ok) {
            char tmp[100] = {};
            int tt = 0;
            for(i = 0; s[i]; i++) {
                int num = s[i]-'A'+ST;
                sprintf(tmp+tt, "%d", num);
                while(tmp[tt] != '\0')
                    tt++;
            }
            for(i = 0; i < tt; i++)
                tmp[i] -= '0';
            while(tt) {
                for(i = 0; i < tt-1; i++) {
                    tmp[i] = tmp[i]+tmp[i+1];
                    if(tmp[i] >= 10)    tmp[i] -= 10;
                }
                tt--;
                if(tt == 2 && tmp[0] == 1 && tmp[1] == 0 && tmp[2] == 0) {
                    printf("%d\n", ST);
                    ok = 0;
                }
            }
            ST++;
        }
        if(ok)
            puts(":(");
    }
    return 0;
}
