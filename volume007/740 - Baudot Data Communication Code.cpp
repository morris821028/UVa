#include <stdio.h>

int main() {
    char DOWN[35], UP[35];
    char DCH[35] = {}, UCH[35] = {};
    char msg[1024];
    int i, j;
    gets(DOWN);
    gets(UP);
    for(i = 0, j = 0; DOWN[i]; i++) {
        if(DOWN[i] == ' ')
            DCH[i] = j++;
    }
    for(i = 0, j = 0; UP[i]; i++) {
        if(UP[i] == ' ')
            UCH[i] = j++;
    }
    while(gets(msg)) {
        int state = 1, n;
        for(i = 0; msg[i]; i += 5) {
            n = 0;
            for(j = 0; j < 5; j++)
                n = (n<<1) + msg[i+j]-'0';
            if(DOWN[n] == ' ' && DCH[n]) {
                state = DCH[n];
                continue;
            }
            if(UP[n] == ' ' && UCH[n]) {
                state = UCH[n];
                continue;
            }
            if(state == 1)
                putchar(DOWN[n]);
            else
                putchar(UP[n]);
        }
        puts("");
    }
    return 0;
}
