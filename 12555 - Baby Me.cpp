#include <stdio.h>
#include <wchar.h>

int main() {
    int t, cases = 0;
    char line[256];
    scanf("%d ", &t);
    while(t--) {
        gets(line);
        int num[10] = {}, sum = 0, i, j = 0, g = 0;
        for(i = 0; line[i] != '\0'; i++) {
            if(line[i] <= '9' && line[i] >= '0')
                num[j] = num[j]*10 + line[i]-'0', g = 1;
            else {
                if(g)
                    j++;
                g = 0;
            }
        }
        printf("Case %d: ", ++cases);
        if(j == 1)  sum += num[0]*50;
        else        sum += num[0]*50+num[1]*5;
        if(sum%100 == 0)
            printf("%d\n", sum/100);
        else if(sum%10 == 0)
            printf("%d.%d\n", sum/100, sum%100/10);
        else
            printf("%d.%d%d\n", sum/100, sum%100/10, sum%10);
    }
    return 0;
}
//¤ç 164 231
//¨â 63
