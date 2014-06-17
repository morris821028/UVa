#include <stdio.h>

int main() {
    char num[1005];
    int i, j, x, y, n;
    scanf("%*d");
    while(scanf("%s", num) == 1) {
        scanf("%d", &n);
        int flag = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            y = 0;
            if(!flag)
            for(j = 0; num[j]; j++)
                y = y*10 + num[j]-'0', y %= x;
            if(y)   flag = 1;
        }
        printf("%s - ", num);
        if(flag)
            puts("Simple.");
        else
            puts("Wonderful.");
    }
    return 0;
}
