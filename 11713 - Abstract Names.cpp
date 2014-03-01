#include <stdio.h>
#include <string.h>
int main() {
    char s1[100], s2[100];
    int t, i;
    int vowel[256]  = {};
    vowel['a'] = 1, vowel['e'] = 1, vowel['i'] = 1;
    vowel['o'] = 1, vowel['u'] = 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s", s1, s2);
        if(strlen(s1) != strlen(s2)) {
            puts("No");
            continue;
        }
        int flag = 0;
        for(i = 0; s1[i] && !flag; i++) {
            if(vowel[s1[i]] || vowel[s2[i]]) {
                if(vowel[s1[i]] != vowel[s2[i]])
                    flag = 1;
            } else {
                if(s1[i] != s2[i])
                    flag = 1;
            }
        }
        puts(flag ? "No" : "Yes");
    }
    return 0;
}
