#include <stdio.h>
#include <string.h>
int main() {
    int n;
    char line[205];
    scanf("%d", &n);
    getchar();
    while(n--) {
        gets(line);
        int i, M = 0, F = 0, rM = 0, rF = 0;
        int len = strlen(line), it = 0;
        for(i = 0; i < len; i++) {
            if(line[i] != ' ') {
                if(line[i] == 'M')  M++;
                else    F++;
                if(line[i+1] == 'M')  rM++;
                else    rF++;
                i++;
                it++;
            }
        }
        if((M == rF  || F == rM) && it > 1)
            puts("LOOP");
        else
            puts("NO LOOP");
    }
    return 0;
}
