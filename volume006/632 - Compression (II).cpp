#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s[2048];
int a[2048], len;
bool cmp(int a, int b) {
    int i;
    for(i = 0; i < len; i++)
        if(s[(a+i)%len] != s[(b+i)%len])
            return s[(a+i)%len] < s[(b+i)%len];
    return false;
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &len);
        int idx = 0;
        while(getchar() != '\n');
        while(gets(s+idx)) {
            idx += strlen(s+idx);
            if(idx == len)
                break;
        }
        for(i = 0; i < len; i++)
            a[i] = i;
        sort(a, a+len, cmp);
        int S1 = 0;
        for(i = 0; i < len; i++) {
            if(a[i] == 1)
                S1 = i;
        }
        printf("%d\n", S1);
        for(i = 0; i < len; i++) {
            if(i%50 == 0 && i)   puts("");
            printf("%c", s[(a[i]+len-1)%len]);

        }
        puts("");
        if(t)
            puts("");
    }
    return 0;
}
/*
5

1
a
5
aaaaa
12
abcabcabcabc
55
12345678901234567890123456789012345678901234567890
12345
50
12345678901234567890123456789012345678901234567890
*/
