#include <stdio.h>
#include <string.h>
char key[6][7] = {
    "_W_W_W",
    "____W_",
    "__W___",
    "_W__W_",
    "_____W",
    "___W__"
};
int main() {
    char s[1000], buf[6][6], buf2[6][6];
    int i, j, k, r;
    while(gets(s)) {
        for(i = 0; s[i]; i += 36) {
            for(j = 0; j < 36; j++)
                buf[j/6][j%6] = s[i+j];
            for(r = 0; r < 4; r++) {
                for(j = 0; j < 6; j++) {
                    for(k = 0; k < 6; k++) {
                        if(key[j][k] == 'W')
                            putchar(buf[j][k]);
                    }
                }
                puts("");
                for(j = 0; j < 6; j++, puts(""))
                    for(k = 0; k < 6; k++)
                        putchar(buf[j][k]);
                int idx = 0;
                for(j = 0; j < 6; j++) {
                    for(k = 5; k >= 0; k--)
                        buf2[idx/6][idx%6] = buf[k][j], idx++;
                }
                for(j = 0; j < 6; j++) {
                    for(k = 0; k < 6; k++) {
                        buf[j][k] = buf2[j][k];
                    }
                }
            }
        }
        memset(s, 0, sizeof(s));
    }
    return 0;
}
