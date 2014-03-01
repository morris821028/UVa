#include <stdio.h>
#include <math.h>
int main() {
    //puts("Program 6 by team X");
    char s[105];
    int i;
    while(scanf("%s", s) == 1) {
        double n2 = 0.5, frac = 1;
        int exponent = 0, flag = 1;
        for(i = 8; s[i]; i++) {
            if(s[i] == '1')
                frac += n2;
            flag &= s[i] == '0';
            n2 /= 2;
        }
        if(s[0] == '1') frac = -frac;
        for(i = 1; i <= 7; i++)
            exponent = (exponent<<1)|(s[i]-'0');
        frac *= pow(2, exponent-63);
        if(flag)   {
            puts(" 0.000000e+000");
            continue;
        }
        if(frac < 0)    putchar('-'), frac = -frac;
        else            putchar(' ');
        printf("%.6e\n", frac);
    }
    //puts("End of program 6 by team X");
    return 0;
}
