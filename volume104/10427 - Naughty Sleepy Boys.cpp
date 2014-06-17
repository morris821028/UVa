#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        int len, tmp = 9, sum = 0;
        for(len = 1; ; len++) {
            sum += tmp*len;
            if(sum >= n)
                break;
            tmp = tmp*10;
        }
        sum -= tmp*len;
        len--, tmp = tmp/9;
        int diff = (n-sum-1)/(len+1);
        int num = tmp+diff;
        n -= sum+diff*(len+1);
        char str[50];
        sprintf(str, "%d", num);
        printf("%c\n", str[n-1]);
    }
    return 0;
}
