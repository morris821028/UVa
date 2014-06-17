#include <stdio.h>
#include <string.h>
int main() {
    char s[100], g[20][100];
    int i, j, k, t;
    gets(s);
    sscanf(s, "%d", &t);
    while(t--) {
        int n = 0;
        while(gets(g[n]) && g[n][0])
            n++;
        int len = strlen(g[0])-1;
        for(j = 1; j < len; j++) {
            for(k = 32; k < 128; k++) {
                for(i = 1; i <= 8; i++) {
                    if(g[i][j] == '\\') {
                        if(k/(1<<(i-1))%2 == 0)
                            break;
                    } else {
                        if(k/(1<<(i-1))%2)
                            break;
                    }
                }
                if(i == 9)  printf("%c", k);
            }
        }
        puts("");
    }
    /*while(gets(s)) {
        for(i = 0; i < 8; i++) {
            for(j = 0; s[j]; j++)
                if(s[j]/(1<<i)%2 == 1)
                    printf("\\");
                else
                    printf("/");
            puts("");
        }
    }*/
    return 0;
}
