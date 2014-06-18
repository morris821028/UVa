#include <stdio.h>

int main() {
    char cmd[50];
    int a, b, c, ans = 0;
    while(gets(cmd)) {
        if(sscanf(cmd, "%d+%d=%d", &a, &b, &c) == 3) {
            if(a+b == c)
                ans++;
        }
        if(sscanf(cmd, "%d-%d=%d", &a, &b, &c) == 3) {
            if(a-b == c)
                ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
