#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    int t;
    char cmd[32767];
    scanf("%d", &t);
    gets(cmd);
    while(t--) {
        gets(cmd);
        int len = strlen(cmd), sq = sqrt(len);
        if(sq*sq != len)
            puts("INVALID");
        else {
            int i, j;
            for(i = 0; i < sq; i++)
                for(j = 0; j < sq; j++)
                    putchar(cmd[j*sq+i]);
            puts("");
        }
    }
    return 0;
}
/*
3
WECGEWHYAAIORTNU
DAVINCICODE
DTFRIAOEGLRSI TS
*/
