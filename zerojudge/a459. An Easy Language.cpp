#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int Brain[240] = {}, Ptr = 0;
    char s[20];
    int cmd[1001], idx = 0, i;
    while(scanf("%s", s) == 1) {
        if(!strcmp(s, "(>OwO)>u~(/OwO)/nya~")) {
            cmd[idx] = 0;
        } else if(!strcmp(s, "(>OwO)>u~!(/OwO)/nya~!")) {
            cmd[idx] = 1;
        } else if(!strcmp(s, "(>OwO)>u~!!(/OwO)/nya~!!")) {
            cmd[idx] = 2;
        } else if(!strcmp(s, "(>OwO)>u~!!!(/OwO)/nya~!!!")) {
            cmd[idx] = 3;
        } else if(!strcmp(s, "CHAOS")) {
            scanf("%s", s);
            cmd[idx] = 4;
        } else if(!strcmp(s, "I")) {
            scanf("%s %s", s, s);
            cmd[idx] = 5;
        } else if(!strcmp(s, "Let's\\(OwO)/nya~")) {
            cmd[idx] = 6;
        }
        idx++;
    }
    int tmp;
    for(i = 0; i < idx; i++) {
        switch(cmd[i]) {
            case 0:Ptr++;
                break;
            case 1:Brain[Ptr]++;
                break;
            case 2:Ptr--;
                break;
            case 3:Brain[Ptr]--;
                break;
            case 4:
                if(Brain[Ptr] == 0) {
                    tmp = 1;
                    i++;
                    while(i < idx) {
                        if(cmd[i] == 4)
                            tmp++;
                        if(cmd[i] == 5)
                            tmp--;
                        if(tmp == 0)
                            break;
                        i++;
                    }
                }
                break;
            case 5:
                tmp = 1;
                i--;
                while(i >= 0) {
                    if(cmd[i] == 5)
                        tmp++;
                    if(cmd[i] == 4)
                        tmp--;
                    i--;
                    if(tmp == 0)
                        break;
                }
                break;
            case 6:
                putchar(Brain[Ptr]);
                break;
        }
    }
    return 0;
}
