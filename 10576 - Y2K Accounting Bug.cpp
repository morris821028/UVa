#include <stdio.h>

int main() {
    int s, d;
    while(scanf("%d %d", &s, &d) == 2) {
        int y_surplus = -1, year, i, j;
        for(year = (1<<12)-1; year >= 0; year--) {
            int tot = 0, flag = 1;
            for(i = 0; i < 12; i++) {
                if((year>>i)&1)
                    tot += s;
                else
                    tot -= d;
                if(i < 8) {
                    int tmp = 0;
                    for(j = i; j < i+5; j++)
                        if((year>>j)&1)
                            tmp += s;
                        else
                            tmp -= d;
                    if(tmp >= 0)    flag = 0;
                }
            }
            if(flag && y_surplus < tot)
                y_surplus = tot;
        }
        if(y_surplus < 0)   puts("Deficit");
        else
            printf("%d\n", y_surplus);
    }
    return 0;
}
