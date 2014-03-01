#include <stdio.h>
int stk[1048576], sum[1048576];
int main() {
    int val;
    char c;
    while(scanf("%d%c", &val, &c) == 2) {
        int idx = -1, flag = 0;
        stk[++idx] = val, sum[idx] = 0;
        if(val > 0) flag = 1;
        while(c != '\n' && scanf("%d%c", &val, &c) == 2) {
            if(idx >= 0) {
                if(val < 0) {
                    sum[idx] += -val;
                    stk[++idx] = val, sum[idx] = 0;
                } else {
                    if(stk[idx] == -val) {
                        if(sum[idx] >= val)
                            flag = 1;
                        idx--;
                    } else
                        flag = 1;
                }
            } else {
                if(val > 0) flag = 1;
                stk[++idx] = val, sum[idx] = 0;
            }
        }
        if(idx >= 0)    flag = 1;
        if(flag)    puts(":-( Try again.");
        else        puts(":-) Matrioshka!");
    }
    return 0;
}
