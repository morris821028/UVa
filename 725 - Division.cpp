#include <stdio.h>

int main() {
    int n, i, j, first = 1;
    while(scanf("%d", &n) == 1 && n) {
        if(!first)
            puts("");
        first = 0;
        int flag = 0;
        for(i = 1234; i <= 99999; i++) {
            if(i*n > 99999)
                break;
            char used[10] = {}, str[10], flag1 = 0;
            sprintf(str, "%05d", i);
            for(j = 0; str[j]; j++)
                used[str[j]-'0']++;
            sprintf(str, "%05d", i*n);
            for(j = 0; str[j]; j++)
                used[str[j]-'0']++;
            for(j = 0; j < 10; j++)
                if(used[j] != 1)
                    flag1 = 1;
            if(!flag1) {
                flag = 1;
                printf("%05d / %05d = %d\n", i*n, i, n);
            }
        }
        if(!flag)
            printf("There are no solutions for %d.\n", n);
    }
    return 0;
}
