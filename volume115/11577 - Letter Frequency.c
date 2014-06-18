#include <stdio.h>

int main() {
    int t;
    char str[999];
    scanf("%d", &t);
    getchar();
    while(t--) {
        gets(str);
        int cnt[26] = {}, i;
        for(i = 0; str[i]; i++) {
            if(str[i] >= 'a' && str[i] <= 'z')
                cnt[str[i]-'a']++;
            if(str[i] >= 'A' && str[i] <= 'Z')
                cnt[str[i]-'A']++;
        }
        int max = 0;
        for(i = 0; i < 26; i++)
            max = max > cnt[i] ? max : cnt[i];
        for(i = 0; i < 26; i++)
            if(cnt[i] == max)
                printf("%c", i+'a');
        puts("");
    }
    return 0;
}
