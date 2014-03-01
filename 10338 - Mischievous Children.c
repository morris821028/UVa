#include <stdio.h>
#include <string.h>

int main() {
    int t, Case = 0, i;
    char str[20];
    long long f[22] = {1, 1};
    for(i = 2; i <= 20; i++)
        f[i] = f[i-1]*i;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", str);
        int letter[26] = {}, len = strlen(str);
        for(i = 0; str[i]; i++)
            letter[str[i]-'A']++;
        long long ans = f[len];
        for(i = 0; i < 26; i++)
            ans /= f[letter[i]];
        printf("Data set %d: %lld\n", ++Case, ans);
    }
    return 0;
}
