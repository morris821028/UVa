#include <stdio.h>
#include <string.h>
long long toDec(char s[], long long base, int len) {
    long long Dec = 0, B = 1;
    int i;
    for(i = len-1; i >= 0; i--) {
        if(s[i] >= '0' && s[i] <= '9')
            Dec += (s[i]-'0')*B;
        else
            Dec += (s[i]-'A'+10)*B;
        B *= base;
    }
    return Dec;
}
int main() {
    char s1[50], s2[50];
    while(scanf("%s %s", s1, s2) == 2) {
        int l1 = strlen(s1), l2 = strlen(s2);
        int b1 = 1, b2 = 1, i;
        for(i = 0; i < l1; i++) {
            if(s1[i] >= '0' && s1[i] <= '9')
                b1 = b1 > s1[i]-'0' ? b1 : s1[i]-'0';
            else
                b1 = b1 > s1[i]-'A'+10 ? b1 : s1[i]-'A'+10;
        }
        for(i = 0; i < l2; i++) {
            if(s2[i] >= '0' && s2[i] <='9')
                b2 = b2 > s2[i]-'0' ? b2 : s2[i]-'0';
            else
                b2 = b2 > s2[i]-'A'+10 ? b2 : s2[i]-'A'+10;
        }
        b1++, b2++;
        for(; b1 <= 36; b1++) {
            for(i = b2; i <= 36; i++) {
                if(toDec(s1, b1, l1) == toDec(s2, i, l2)) {
                    printf("%s (base %d) = %s (base %d)\n", s1, b1, s2, i);
                    goto Break;
                }
            }
        }
        printf("%s is not equal to %s in any base 2..36\n", s1, s2);
        Break:
        i == 0;
    }
    return 0;
}
