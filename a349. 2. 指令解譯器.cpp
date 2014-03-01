#include <stdio.h>
int main() {
    char cmd[8];
    int mem[8] = {}, reg[4] = {};
    int i, n, D, S, s1, s2;
    for(i = 0; i < 8; i++)
        scanf("%d", &mem[i]);
    scanf("%d", &n);
    while(n--) {
        scanf("%s", cmd);
        if(cmd[0] == 'L')
            scanf("%d %d", &D, &S), reg[D] = mem[S];
        else if(cmd[0] == 'S')
            scanf("%d %d", &D, &S), mem[D] = reg[S];
        else if(cmd[0] == 'A')
            scanf("%d %d %d", &D, &s1, &s2), reg[D] = reg[s1] + reg[s2];
        else
            scanf("%d %d", &D, &S), reg[D] = reg[S];
    }
    printf("%d\n%d\n", reg[0], mem[0]);
    return 0;
}
