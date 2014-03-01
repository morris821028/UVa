#include <stdio.h>

int main() {
    scanf("%*d");
    char cmd[30];
    int n, I[105], i, j;
    while(scanf("%d ", &n) == 1) {
        int x = 0;
        for(i = 0; i < n; i++) {
            gets(cmd);
            if(cmd[0] == 'L')
                I[i] = -1, x--;
            else if(cmd[0] == 'R')
                I[i] = 1, x++;
            else {
                sscanf(cmd+8, "%d", &j);
                I[i] = I[j-1], x += I[i];
            }
        }
        printf("%d\n", x);
    }
    return 0;
}
