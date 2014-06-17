#include <stdio.h>

int main() {
    char QWERTY[] = "1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";
    char DVOARK[] = "123qjlmfp/[]456.orsuyb;=\\789aehtdck-0zx,inwvg'";
    char M1[] = "!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?";
    char M2[] = "!@#QJLMFP?{}$%^>ORSUYB:+|&*(AEHTDCK_)ZX<INWVG\"";
    char cmd[1024];
    int i, j;
    while(gets(cmd)) {
        for(i = 0; cmd[i]; i++) {
            int flag = 0;
            for(j = 0; QWERTY[j]; j++)
                if(QWERTY[j] == cmd[i])
                    putchar(DVOARK[j]), flag = 1;
            for(j = 0; M1[j]; j++)
                if(M1[j] == cmd[i])
                    putchar(M2[j]), flag = 1;
            if(!flag)   putchar(cmd[i]);
        }
        puts("");
    }
    return 0;
}
