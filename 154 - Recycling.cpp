#include <stdio.h>
int g[105][5];
int ch2int(char c) {
    if(c == 'r')    return 0;
    if(c == 'o')    return 1;
    if(c == 'y')    return 2;
    if(c == 'g')    return 3;
    if(c == 'b')    return 4;
    return -1;
}
int main() {
    char buf[105];
    int i, j, k, n = 0, m;
    while(gets(buf) && buf[0] != '#') {
        if(buf[0] == 'e') {
            int mn = 0xfffff, ans, tmp;
            for(i = 0; i < n; i++) {
                tmp = 0;
                for(j = 0; j < n; j++) {
                    for(k = 0; k < 5; k++) {
                        if(g[i][k] != g[j][k])
                            tmp++;
                    }
                }
                if(tmp < mn)
                    mn = tmp, ans = i+1;
            }
            printf("%d\n", ans);
            n = 0;
        } else {
            for(i = 0; i < 5; i++) {
                g[n][ch2int(buf[i*4])] = buf[i*4+2];
            }
            n++;
        }
    }
    return 0;
}
