#include <stdio.h>
#include <math.h>
#include <string.h>
short bin[160], mbin[320], obin[320];
int check(int st) {
    int i, j;
    memset(mbin, 0, sizeof(mbin));
    for(i = st; i < 160; i++) {
        if(bin[i])
        for(j = st; j < 160; j++)
            mbin[i+j] += bin[i]&bin[j];
    }
    for(i = 0; i < 320; i++) {
        if(mbin[i] >= 2) {
            mbin[i+1] += mbin[i]>>1;
            mbin[i] &= 1;
        }
    }
    /*for(i = 319; i >= 0; i--)
        printf("%d", mbin[i]);
    puts("");
    for(i = 319; i >= 0; i--)
        printf("%d", obin[i]);
    puts("");*/
    for(i = 319; i >= 0; i--)
        if(mbin[i] > obin[i])
            return 0;
        else if(mbin[i] < obin[i])
            return 1;
    return 1;
}
int main() {
    scanf("%*d");
    int n, i, j;
    char s[50];
    while(scanf("%d %s", &n, s) == 2) {
        int sq = sqrt(n);
        memset(bin, 0, sizeof(bin));
        memset(obin, 0, sizeof(obin));
        for(i = 10; i >= 0; i--)
            bin[150-(10-i)] = (sq>>i)&1;
        for(i = 25; i >= 0; i--)
            obin[305-(25-i)] = (n>>i)&1;
        /*for(i = 150; i >= 140; i--)
            printf("%d", bin[i]);
        puts("");*/
        for(i = 139; i >= 0; i--) {
            bin[i] = 1;
            if(check(i)) {}
            else    bin[i] = 0;
        }
        for(i = 139; i >= 0; i--) {
            for(j = 0; s[j]; j++)
                if(s[j]-'0' != bin[i-j])
                    break;
            if(s[j] == '\0') {
                printf("%d\n", 139-i);
                break;
            }
        }
        /*printf(".");
        for(i = 139; i >= 0; i--)
            printf("%d", bin[i]);
        puts("");*/
    }
    return 0;
}
