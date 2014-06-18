#include <stdio.h>
#include <string.h>
int main() {
    int t, cases = 0;
    char s[105];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int len = strlen(s);
        unsigned long long res = 0, bin = 1;
        int i, j;
        for(i = len-1; i >= 0; i--) {
            if(s[i] == 'A') j = 0;
            else if(s[i] == 'C') j = 1;
            else if(s[i] == 'G') j = 2;
            else j = 3;
            res += bin * j;
            bin *= 4;
        }
        printf("Case %d: (%d:%llu)\n", ++cases, len, res);
    }
    return 0;
}
