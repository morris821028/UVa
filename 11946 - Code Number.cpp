#include <stdio.h>

int main() {
    int t, i;
    char s[100], a[10] = {'O','I','Z','E','A','S','G','T','B','P'};
    scanf("%d ", &t);
    while(t--) {
        while(gets(s)) {
            if(s[0] == '\0')
                break;
            for(i = 0; s[i]; i++) {
                if(s[i] >= '0' && s[i] <= '9')
                    s[i] = a[s[i]-'0'];
            }
            puts(s);
        }
        if(t)
            puts("");
    }
    return 0;
}
