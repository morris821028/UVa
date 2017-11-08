#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXS (1<<16)
int main() {
    static char s[MAXS], cmd[MAXS];
    scanf("%s", s);
    int n = (int) strlen(s);
    while (scanf("%s", cmd) == 1) {
        if (cmd[0] == 'p') {
            s[n] = '\0';
            puts(s);
        } else if (cmd[0] == 's') {
            char del[2] = {cmd[1], '\0'};
            char *A = strtok(cmd+2, del);
            char *B = strtok(NULL, del);
            char *pos = strstr(s, A);
            if (pos == NULL)
                continue;
            int na = (int) strlen(A);
            int nb = (int) strlen(B);
            memmove(pos+nb, pos+na, ((s+n)-(pos+na))*sizeof(char));
            memcpy(pos, B, nb*sizeof(char));
            n += nb - na;
        }
    }
    return 0;
}

