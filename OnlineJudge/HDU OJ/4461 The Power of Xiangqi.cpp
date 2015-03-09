#include <stdio.h>

int main() {
    int t;
    char s[10];
    scanf("%d", &t);
    while(t--) {
        int n, sum1 = 0, sum2 = 0;
        int flag1 = 0, flag2 = 0;
        scanf("%d", &n);
        while(n--) {
            scanf("%s", s);
            if(s[0] == 'A')     sum1 += 16;
            else if(s[0] == 'B')sum1 += 7, flag1 = 1;
            else if(s[0] == 'C')sum1 += 8, flag2 = 1;
            else if(s[0] == 'D')sum1 += 1;
            else if(s[0] == 'E')sum1 += 1;
            else if(s[0] == 'A')sum1 += 2;
            else                sum1 += 3;
        }
        if(flag1 == 0 || flag2 == 0)
            sum1--;
        flag1 = 0, flag2 = 0;
        scanf("%d", &n);
        while(n--) {
            scanf("%s", s);
            if(s[0] == 'A')     sum2 += 16;
            else if(s[0] == 'B')sum2 += 7, flag1 = 1;
            else if(s[0] == 'C')sum2 += 8, flag2 = 1;
            else if(s[0] == 'D')sum2 += 1;
            else if(s[0] == 'E')sum2 += 1;
            else if(s[0] == 'A')sum2 += 2;
            else                sum2 += 3;
        }
        if(flag1 == 0 || flag2 == 0)
            sum2--;
        if(sum1 == sum2)
            puts("tie");
        else if(sum1 < sum2)
            puts("black");
        else
            puts("red");
    }
    return 0;
}
