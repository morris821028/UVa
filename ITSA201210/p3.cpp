#include <stdio.h>

int main() {
    char s[1000];
    int i;
    while(gets(s)) {
        int cnt[26] = {};
        for(i = 0; s[i]; i++) {
            if(s[i] >= 'A' && s[i] <= 'Z')
                cnt[s[i]-'A']++;
            else
            if(s[i] >= 'a' && s[i] <= 'z')
                cnt[s[i]-'a']++;
        }
        for(i = 0; i < 26; i++) {
            if(cnt[i])
                printf("%c %d\n", i+'a', cnt[i]);
        }
    }
    return 0;
}
