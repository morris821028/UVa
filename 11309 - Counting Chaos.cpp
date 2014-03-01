#include <stdio.h>
#include <string.h>

int main() {
    int t, x, y, n;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d:%d", &x, &y);
        int time = x*60 + y;
        char str[10];
        do {
            time++;
            if(time >= 1440)    time = 0;
            x = time/60, y = time%60;
            sprintf(str, "%02d%02d", x, y);
            sscanf(str, "%d", &n);
            sprintf(str, "%d", n);
            int flag = 0;
            for(i = 0, j = strlen(str)-1; i < j; i++, j--)
                if(str[i] != str[j])
                    flag = 1;
            if(!flag) {
                sprintf(str, "%02d:%02d", x, y);
                puts(str);
                break;
            }
        } while(true);
    }
    return 0;
}
