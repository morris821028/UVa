#include <stdio.h>

int main() {
    char a[105], b[105];
    int t, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s", a, b);
        printf("%s %s\n", a, b);
        while(1) {
            int zero = 1, overflow = 0;
            for(i = 0; i < 31; i++) {
                int ai = a[i]-'0', bi = b[i]-'0';
                a[i] = (ai != bi) + '0';
                if(i)   b[i-1] = (ai && bi)+'0';
                else    overflow = (ai && bi);
                zero &= !(ai && bi);
            }
            b[30] = '0';
            if(overflow) {
                printf("%s overflow\n", a);
                break;
            }
            printf("%s %s\n", a, b);
            if(zero)    break;
        }
        if(t)   puts("");
    }
    return 0;
}
