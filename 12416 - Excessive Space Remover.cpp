#include <stdio.h>
char s[1000000];
int main() {
    while(gets(s)) {
        int cnt = 0, max = 0, i;
        for(i = 0; s[i]; i++) {
            if(s[i] == ' ')
                cnt++;
            else {
                if(cnt > max)
                    max = cnt;
                cnt = 0;
            }
        }
        cnt = 0;
        while(max != 1) {
            cnt++;
            max = max/2 + (max-max/2*2);
        }
        printf("%d\n", cnt);
    }
    return 0;
}
