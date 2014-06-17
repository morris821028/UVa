#include <stdio.h>

int main() {
    int n, tmp;
    char cmd[128];
    while(scanf("%d", &n) == 1 && n) {
        int dice[6] = {1,2,3,4,5,6};
        while(n--) {
            scanf("%s", cmd);
            if(cmd[0] == 'n') {
                tmp = dice[1], dice[1] = dice[0];
                dice[0] = dice[4], dice[4] = dice[5];
                dice[5] = tmp;
            } else if(cmd[0] == 's') {
                tmp = dice[1], dice[1] = dice[5];
                dice[5] = dice[4], dice[4] = dice[0];
                dice[0] = tmp;
            } else if(cmd[0] == 'e') {
                tmp = dice[3], dice[3] = dice[0];
                dice[0] = dice[2], dice[2] = dice[5];
                dice[5] = tmp;
            } else {
                tmp = dice[3], dice[3] = dice[5];
                dice[5] = dice[2], dice[2] = dice[0];
                dice[0] = tmp;
            }
        }
        printf("%d\n", dice[0]);
    }
    return 0;
}
