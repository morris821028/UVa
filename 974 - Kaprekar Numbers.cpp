#include <stdio.h>

int main() {
    int i, j, x, y, tmp;
    char buf[30];
    int ans[50], at = 0;
    for(i = 4; i <= 40000; i++) {
        j = i*i;
        sprintf(buf, "%d", j);
        for(j = 0; buf[j+1]; j++) {
            tmp = buf[j+1];
            buf[j+1] = '\0';
            sscanf(buf, "%d", &x);
            buf[j+1] = tmp;
            sscanf(buf+j+1, "%d", &y);
            if(x && y && x+y == i) {
                ans[at++] = i;
                break;
            }
        }
    }
    int cases = 0;
    scanf("%d", &tmp);
    while(tmp--) {
        scanf("%d %d", &x, &y);
        printf("case #%d\n", ++cases);
        for(i = 0, j = 0; i < at; i++)
            if(ans[i] >= x && ans[i] <= y)
                printf("%d\n", ans[i]), j = 1;
        if(!j)
            puts("no kaprekar numbers");
        if(tmp) puts("");
    }
    return 0;
}
